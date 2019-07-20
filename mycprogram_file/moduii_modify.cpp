//数颜色 
//可以修改的莫队算法 持久化莫队算法 模板
//通过增加一个时间维度 对于r进行分块 对于r与t关系如同l与r关系
//分块大小n^2/3 时间复杂度n^5/3
//莫对核心 算法分析都需要分块分析 但是实现的时候其实只需要在排序的时候进行跟快限制就可以 其他的地方暴力解决就可以
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 5e4+10;
const int MAXN = 1e6+10;
int B = 1;//快的大小
int cnt[MAXN];
int ans[N];
int n,m;
int res=0;
char opt[3];//如果使用字符 需要使用getchar吃掉多余的换行符号 但是如果使用输入字符串可以避免这个问题
int color[N];
int qcnt=0,ccnt=0;//记录修改数目 查询数目
int l,r;
int now;//记录当前时间戳
struct Change{
    int p,col;
}c[N];
struct Query{
    int l,r,t,id;
    bool operator<(const Query& o) const{
        return l/B==o.l/B?(r/B==o.r/B?t<o.t:r<o.r):l<o.l;
    }
}q[N];
void add(int x){
    if(cnt[x]++==0){
        res++;
    }
}

void del(int x){
    if(--cnt[x]==0){//小心
        res--;
    }
}
//关键函数
void modify(int x,int tim){//x表示所要修改的当前的区间 tim表示时间--当前时间 也就是需要修改的时间点
    if(c[tim].p>=q[x].l&&c[tim].p<=q[x].r){
        //在区间内部 不仅需要修改 还需要更新答案
        del(color[c[tim].p]);
        add(c[tim].col);
    }
    //统一修改信息
    //由于本次升序 下一个快必然是回退到起点 再次开始升序 一共(n/b)^2块数目 所以为了方便回退 使用swap修改 并且
    swap(color[c[tim].p],c[tim].col);//关键技巧 方便的实现前进 回滚
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&color[i]);
    }
    B = pow(n,0.66666);

    for(int i=1;i<=m;i++){
        // scanf("%c",&opt);
        scanf("%s",&opt);
        if(opt[0]=='Q'){
            qcnt++;
            scanf("%d%d",&q[qcnt].l,&q[qcnt].r);
            q[qcnt].id=qcnt;
            q[qcnt].t = ccnt;
        }
        if(opt[0]=='R'){
            ccnt++;
            scanf("%d%d",&c[ccnt].p,&c[ccnt].col);
        }
    }
    l=1,r=0;//其实只需要r<l就可以在查询的时候自动r滑动/l滑动计算当前区域数值 但是害怕数据量很小 所以给lr初始化小的数值
    sort(q+1,q+qcnt+1);
    for(int i=1;i<=qcnt;i++){
        while(l<q[i].l){
            del(color[l++]);
        }
        while(l>q[i].l){
            add(color[--l]);
        }
        while(r>q[i].r){
            del(color[r--]);
        }
        while(r<q[i].r){
            add(color[++r]);
        }
        while(now<q[i].t){
            modify(i,++now);//小心不要错了now++
        }
        while(now>q[i].t){
            modify(i,now--);
        }
        ans[q[i].id] = res;
    }
    for(int i=1;i<=qcnt;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
