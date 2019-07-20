/*
快速最短路算法 spfa
贝尔曼福德算法优化 使用优先队列
基于bfs 遍历每一条边 使用每一条边更新目标
*/
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
const int INF = 1e9;
const int maxn = 205;
vector<pair<int,int> > E[maxn];

int n,m;
int d[maxn],inq[maxn];
void init(){
    for(int i=0;i<maxn;i++) E[i].clear();
    for(int i=0;i<maxn;i++) inq[i] = 0;
    for(int i=0;i<maxn;i++) d[i] = INF;
}

int main(){
    while(cin>>n>>m){
        init();
        int x,y,z;
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&x,&y,&z);
            E[x].push_back(make_pair(y,z));
            E[y].push_back(make_pair(x,z));
        }
        int s,t;
        scanf("%d%d",&s,&t);
        queue<int> Q;
        Q.push(s);
        d[s] = 0; inq[s] = 1;
        int now;
        while(!Q.empty()){
            now = Q.front();
            Q.pop();
            inq[now] = 0;
            int v;
            for(int i=0;i<E[now].size();i++){
                v = E[now][i].first;
                if(d[v]>d[now]+E[now][i].second){
                    d[v] = d[now]+E[now][i].second;
                    if(inq[v]==1)
                        continue;
                    inq[v] = 1;
                    Q.push(v);
                }

            }
        }
        if(d[t]==INF)
            printf("-1\n");
        else
            printf("%d\n",d[t]);
    }
    return 0;
}
