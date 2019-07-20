//不同于普通线段树
//每次更新数值会上传到根节点 
//不需要query函数 因为每次都是查询整个线段树的信息
//所以每次只需要查看根节点的信息 
#include<bits/stdc++.h>
using namespace std;
const int N = 111;
double x[N];
struct Edge{
    double l,r,h;
    int flag;
}e[N<<1];
bool cmp(Edge& a,Edge& b){
    return a.h<b.h;
}
struct Node{//实际上tl tr无用 每次从0-k-1二分可以得到lr
    int l,r;
    int s;
    double len;//真正需要的
}T[N<<3];//线段树空间不够通常会导致tle 而不是re
void build(int rt,int l,int r){
    T[rt].l = l;
    T[rt].r = r;
    T[rt].len = 0;
    T[rt].s = 0;
    if(l==r) return;
    int m = (l+r)>>1;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
}
void pushup(int rt){
    //去重
    if(T[rt].s)
        T[rt].len = x[T[rt].r+1] - x[T[rt].l];
    else if(T[rt].l==T[rt].r)
        T[rt].len = 0;
    else
        T[rt].len = T[rt<<1].len + T[rt<<1|1].len;
}
void update(int id,int l,int r,int xx){
    if(T[id].l>=l&&T[id].r<=r){
        T[id].s += xx;
        pushup(id);//不同于普通的区间更新
        return;
    }
    int mid = (T[id].l+T[id].r)>>1;
    if(l<=mid) update(id<<1,l,r,xx);
    if(r>mid) update(id<<1|1,l,r,xx);
    pushup(id);
}
//绝对不要Edge& a=kk,b=k;b会自动识别成一般变量

int main()
{
    int n;int kas = 0;
    while (scanf("%d",&n) == 1&&n)
    {
        int tot = 0;
        for (int i = 0;i < n;++i)
        {
            double x1,x2,y1,y2;
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);//输入一个矩形
            Edge &t1 = e[tot];Edge &t2 = e[1+tot];
            t1.l = t2.l = x1,t1.r = t2.r = x2;
            t1.h = y1;t1.flag = 1;
            t2.h = y2;t2.flag = -1;
            x[tot] = x1;x[tot+1] = x2;
            tot += 2;
        }
        sort(e,e+tot,cmp);//边按高度从小到大排序（自下而上扫描）
        sort(x,x+tot);
        //离散化横坐标
        int k = 1;
        for (int i = 1;i < tot;++i)
        {
            if (x[i] != x[i-1]) //去重
            {
                x[k++] = x[i];
            }
        }
        build(1,0,k-1);//离散化后的区间是[0，k-1]
        double ans = 0.0;
        for (int i = 0;i < tot;++i)
        {
            //因为线段树维护的是横坐标们的下标，所以对每条边求出其两个横坐标对应的下标
            int l = lower_bound(x,x+k,e[i].l) - x;//在横坐标数组里找到这条边的位置
            int r = lower_bound(x,x+k,e[i].r) - x - 1;//小心
            update(1,l,r,e[i].flag);//每扫到一条边就更新横向的覆盖len 
            //相当于全树查询函数
            ans += (e[i+1].h - e[i].h)*T[1].len;//q[1]是整个区间,q[1].k=len是整个区间的有效长度
            //计算面积就是用区间横向的有效长度乘以两条边的高度差（面积是两条边里面的部分）
        }
        printf("Test case #%d\n",++kas);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}