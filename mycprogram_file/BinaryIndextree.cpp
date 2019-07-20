#include<iostream>
using namespace std;
const int maxn = 1e5+7;
/*一维树状数组*/
int a[maxn];
int n;

//得到末尾1所对应的数组
//x作为索引 下标从1开始
int lowbit(int x){
    return x&(-x);
}
//单点修改区间查询
void update(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        a[i]+=v;
    }
}
int getsum(int x){
    int res = 0;
    for(int i=x;i;i-=lowbit(i)){
        res+=a[i];
    }
    return res;
}

int query(int l,int r){
    if(l<1) return -1;
    if(l==1) return getsum(r);
    return getsum(r)-getsum(l-1);
}
//变种 单点查询 区间修改----此时上面的接口外部不能调用 否则语义矛盾 内部调用上面的接口
//对3-6区间+5 相当于3+5 7-5
int query_one_point(int x){
    return getsum(x);
}
void update_block(int l,int r,int v){
    if(l>=1){
        update(l,v);
        if(r<n)
            update(r+1,-v);
    }
}
/*二维树状数组*/
// 每一个树状数组节点中单独存储一个树状数组
//单点更新区间查询
int c[maxn][maxn];
void update(int x,int y,int v){
    for(int i=x;i<=n;i+lowbit(i))
        for(int j=y;j<=n;j+=lowbit(j))
            c[i][j]+=v;
}
int getsum(int x,int y){
    if(x==0||y==0)
        return 0;
    int res = 0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            res+=c[i][j];
    return res;
}
//x1 y1 < x2 y2
int query2dblock(int x1,int y1,int x2,int y2){
    //x1==1 y1==1 会+/- 0不影响
    int res = getsum(x2,y2);
    res -= getsum(x1-1,y2);
    res -= getsum(x2,y1-1);
    res += getsum(x1-1,y1-1);
    return res; 
}
//对于区间更新 单点查询
//类似上面的思想 但是具体细节有所不同
int query_one_ponit2d(int x,int y){
    return getsum(x,y);
}
void update_block2d(int x1,int y1,int x2,int y2,int v){
    update(x1,y1,v);
    update(x1,y2+1,-v);
    update(x2+1,y1,-v);
    update(x2+1,y2+1,v);
}

/*
Note:
以上去检修盖单点查询 具体实现需要小心
首先把所有数值单独存储 之后拿到空的(0)矩阵/数组 开始进行区间更新
查询只需要拿到区间上单点查询的结果+原始保存的数据就可以
如果不分开存储 则会单点查询的同时把前缀的数值一同带上 产生错误
*/
int main(){
    return 0;
}