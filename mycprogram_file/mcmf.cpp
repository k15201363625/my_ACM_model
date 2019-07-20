//最小费用最大流mcmf 
//by 趣学算法
//最小费用最大流---满足最大流情况下的最小费用流 
//每次使用spfa找到最小费用路径 在最小费用路径上进行增广一次最短路 
//类似于sap isap dinic 中的思想 都是具有导向性的寻找增光路 
//dinic基于bfs得到的距离原点的层次进行 isap基于距离汇点的距离进行 ek(sap)导向性不足所以有了isap的导向性优化
//顺便复习spfa用法 以及判断负权环的方法 spfa中需要注意--路径需要满足可憎光的路径条件下的最短路
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 5e4+10;
const int M = 1e6+10;
const int INF = 1e9+7;
int head[N];
struct edge{
    int to,nxt;
    int cap,flow,cost;
}e[M];
int mm;//表示变边数目 01 23 45 为一对
// int que[M];//可能大小不够 感觉需要n*n保险
// int head=1,tail=1;
int cnt[N];//入队次数
int pre[N];//当前点前驱边
bool vis[N];
int dis[N];//到达各个节点的最小距离
int maxflow,mincost;
void _add_edge(int a,int b,int c,int d){//添加的时候只需要顺次添加正向边 反向边  从而形成混合图 -- 正流图 残留图
    e[mm].nxt = head[a];
    head[a] = mm;
    e[mm].to = b;
    e[mm].cap = c;
    e[mm].flow = 0;
    e[mm].cost = d;
    mm++;
}
void add_edges(int a,int b,int c,int d){
    _add_edge(a,b,c,d);
    _add_edge(b,a,0,-d);//小心 cost是负的 cap是0
}
void init(){
    memset(head,-1,sizeof(head));//保证最后的nxt为-1
    mm = 0;
    maxflow = 0;
    mincost = 0;
}
void spfa_init(int n){
    memset(cnt,0,sizeof(cnt));
    memset(vis,false,sizeof(vis));
    memset(pre,-1,sizeof(pre));//由于从0开始 所以需要初始化成-1
    for(int i=1;i<=n;i++){
        dis[i] = INF;
    }
}
bool spfa(int s,int t,int n){//不怕负边 怕负环
    queue<int> que;
    //首先初始化
    spfa_init(n);
    vis[s] = true;
    cnt[s]++;
    que.push(s);
    dis[s] = 0;
    int top;
    while(!que.empty()){
        top = que.front();
        que.pop();
        //不能缺少
        vis[top] = false;
        for(int i=head[top];~i;i=e[i].nxt){//小心初始化 必须要把head初始化成-1才行
            int v = e[i].to;
            if(dis[v]>dis[top]+e[i].cost && e[i].flow<e[i].cap){
                dis[v] = dis[top]+e[i].cost;
                pre[v] = i;//无论是否松弛 都需要处理
                if(!vis[v]){
                    vis[v] = true;
                    cnt[v]++;
                    que.push(v);
                    if(cnt[v]>n){
                        //printf("存在负环\n");
                        return false;
                    }
                }
            }
        }
    }
    if(dis[t]==INF)
        return false;
    return true;
}
void MCMF(int s,int t,int n){
    mincost = 0;
    maxflow = 0;
    while(spfa(s,t,n)){
        int minf = INF;
        //反向查找
        for(int i=pre[t];~i;i=pre[e[i^1].to])//拿到反向边的v从而拿到前节点 技巧强 双边存储的优势
            minf = min(minf,e[i].cap - e[i].flow);
        maxflow += minf;
        for(int i=pre[t];~i;i=pre[e[i^1].to]){
            e[i].flow+=minf;
            e[i^1].flow-=minf;
            // e[i^1].cap-=minf;容量一直是0就可以 只要关注流量就行 因为二者cap=0 flow<0才是正常
        }
        mincost+=dis[t]*minf;
    }
}
int main(){
    int n,m,s,t;
    init();//必须有
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int aa,bb,cc,dd;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
        add_edges(aa,bb,cc,dd);
    }
    MCMF(s,t,n);
    printf("%d %d\n",maxflow,mincost);
}