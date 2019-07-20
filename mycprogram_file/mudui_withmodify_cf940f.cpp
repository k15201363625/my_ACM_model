//cf940f Machine Learning 
//类似数颜色 统计在区间内各元素出现的次数的数组中没出现的最小正数字
//由于数据比较大范围 使用离散化 重新映射数值 并且不需要反向映射 
//典型的待修改莫队算法 复杂度达到N*N^(5/3) 对于1e5可以接受
/*
总结： 由于离散化不熟悉 导致出现很多错误 
分块操作 对于快的大小的更新 init过程 sort(q+1,q+n+1)过程 碎玉c的离散化过程 res索引处理都容易出错
由于离散化需要 并且n+c的数目才是真正的数目 所以需要更大的数组空间 2*N
*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e5+1000;
int n,m;
int cnt[N<<1],sum[N<<1],res[N<<1];//分别用于存放 数字出现的次数 出现对应次数的总和 最终的结果
int B = 1;
int a[N<<1],temp[N<<1];//小心 temp cnt sum需要更大才能装得下
int queryn,changen,tempn;
struct Query{
    int id,l,r,t;
    //注意排序判断
    bool operator <(const Query& o) const{
        return l/B==o.l/B?(r/B==o.r/B ? t<o.t:r<o.r):l<o.l;
    }
}q[N];
struct Change{
    int p,val;
}c[N];
void add(int x){//传入数值
    sum[cnt[x]]--;
    cnt[x]++;
    sum[cnt[x]]++;
}
void sub(int x){
    sum[cnt[x]]--;
    cnt[x]--;
    sum[cnt[x]]++;
}
void chnum(int x,int tim){
    //修改某一区间所对应的数值 传入的是查询区间的编号
    if(q[x].l<=c[tim].p&&q[x].r>=c[tim].p){
        sub(a[c[tim].p]);
        add(c[tim].val);
    }
    //交换就可以了 下一次由于单调性必然回退 交换可以保证正确回退
    swap(a[c[tim].p],c[tim].val);
}
void init(){
    memset(cnt,0,sizeof(cnt));
    memset(sum,0,sizeof(sum));
    memset(res,0,sizeof(res));
    queryn = changen = tempn= 0;
}
int main(){
    //第一次wa了 因为： 离散化需要考虑到c的数值 c未必会在a中出现过 所以离散化需要全部统计
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        B = pow(n,0.66666);

        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]),temp[++tempn] = a[i];
        int opt,aa,bb;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&opt,&aa,&bb);
            if(opt==1){
                q[++queryn].l = aa;
                q[queryn].r = bb;
                q[queryn].id = queryn;//排序之后还能找得到原始的位置
                q[queryn].t = changen;
            }else if(opt==2){
                c[++changen].p = aa;
                c[changen].val = bb;
                temp[++tempn] = bb;
            }
        }
        sort(q+1,q+queryn+1);

        //数据离散化 由于不需要原始数据 所以只需要借助一个额外的排序拷贝数组就可以 a存放新的id
        //memcpy(temp,a,sizeof(a));
        sort(temp+1,temp+tempn+1);
        ////unique会返回单一化元素后的最后元素的指针 真正想要删除需要配合erase使用 删除后面的剩余元素
        tempn = unique(temp+1,temp+tempn+1)-temp;//不需要再-1/+1
        for(int i=1;i<=n;i++)
            a[i] = lower_bound(temp+1,temp+tempn+1,a[i])-temp;
        //c特别小心 因为是用数值部分都需要相应离散化处理 
        for(int i=1;i<=changen;i++)
            c[i].val = lower_bound(temp+1,temp+tempn+1,c[i].val)-temp;//减去起始下表不可以少 因为返回的是int*
        //必不可少 关键
        sort(q+1,q+queryn+1);
        int l=1,r=0,tt=0;
        //正式处理
        for(int i=1;i<=queryn;i++){
            while(l<q[i].l){
                sub(a[l++]);
            }
            while(l>q[i].l){
                add(a[--l]);
            }
            while(r>q[i].r){
                sub(a[r--]);
            }
            while(r<q[i].r){
                add(a[++r]);
            }
            //应对万区间变化  再去应对时间变化
            while(tt<q[i].t){
                chnum(i,++tt);
            }
            while(tt>q[i].t){
                chnum(i,tt--);
            }
            //记录每一次询问的结果 只需要查找sum数组
            int ans = 1;
            while(sum[ans]!=0){
                ans++;
            }
            res[q[i].id] = ans;
        }
        for(int i=1;i<=queryn;i++){
            printf("%d\n",res[i]);//这里只需要res[i] 因为已经是处理过的正确的顺序
        }

    }
    return 0;
}