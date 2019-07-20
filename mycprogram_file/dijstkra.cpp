/*
dijstkra 算法 
不同于广度优先搜索 基于优先队列维护 进行更新 
每次使用最短的进行更新
入过到达终点可以提前退出 因为这是必然是最短的
spfa到达也不能退出 因为还可能再次被更新
*/
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<functional>

using namespace std;
const int INF = 1e9;
const int maxn = 205;
vector<pair<int,int> > E[maxn];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;

int n,m;
int d[maxn];
void init(){
    for(int i=0;i<maxn;i++) E[i].clear();
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

        d[s] = 0;
        Q.push(make_pair(d[s],s));
        int now;
        while(!Q.empty()){
            now = Q.top().second;
            if(now==t)//只要走到终点就已经到了最短路
                break;
            Q.pop();
            int v;
            for(int i=0;i<E[now].size();i++){
                v = E[now][i].first;
                if(d[v]>d[now]+E[now][i].second){
                    d[v] = d[now]+E[now][i].second;
                    Q.push(make_pair(d[v],v));
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

