/*
使用并查集
只需要对边进行排序+判断
unionset通常从1开始初始化 0可能会导致未知错误
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 111;
//只需要维护边集合 不需要维护领接表

struct edge{
    int from,to;
    long long cost;
    edge(){}
    edge(int x,int y,ll z):from(x),to(y),cost(z){}
}E[maxn*maxn];

bool cmp(const edge& a,const edge& b){
    return a.cost < b.cost;
}

int father[maxn];
int find(int x){
    if(father[x] == x)
        return x;
    return father[x] = find(father[x]);
}
bool judge(int x,int y){
    return find(x)==find(y);
}
void unionset(int x,int y){
    int xx=find(x),yy=find(y);
    if(xx==yy)
        return;
    father[xx] = yy;    
}
void init(int n){
    for(int i=1;i<=n;i++)
        father[i] = i;
}

int n,m;
ll kruskal(int n){
    ll res = 0;
    sort(E,E+n,cmp);
    for(int i=0;i<n;i++){
        if(judge(E[i].from,E[i].to))
            continue;
        res += E[i].cost;
        unionset(E[i].from,E[i].to);
    }
    return res;
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        //小心
        if(n==0)
            break;
        init(n);
        ll res = 0;
        for(int i=0;i<n;i++){
            scanf("%d%d%lld",&E[i].from,&E[i].to,&E[i].cost);
        }
        res = kruskal(n);

        for(int i=1;i<=m;i++){
            if(!judge(i,1))
                res = -1;
        }
        if(res==-1)
            printf("?\n");
        else
            printf("%lld\n",res);
    }
    return 0;
}