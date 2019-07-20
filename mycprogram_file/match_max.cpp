/*
最大匹配数：最大匹配的匹配边的数目
最小点覆盖数：选取最少的点，使任意一条边至少有一个端点被选择
最大独立数：选取最多的点，使任意所选两点均不相连
最小路径覆盖数：对于一个 DAG（有向无环图），选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。

定理1：最大匹配数 = 最小点覆盖数（这是 Konig 定理）
定理2：最大匹配数 = 最大独立数
定理3：最小路径覆盖数 = 顶点数 - 最大匹配数

匈牙利树一般由 BFS 构造（类似于 BFS 树）
但是匈牙利树要求所有叶子节点均为匹配点
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 1010;
const int MAXM = 5050;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
bool vis[MAXN];//避免当次dfs重复搜索
bool linker[MAXN];
int un,vn;
//需要把左边的点排成一列
bool dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(!vis[v]){
            vis[v] = true;
            //dfs调用的其实都是u这边的节点
            if(!linker[v]||dfs(linker[v])){//表明对面集合的节点是否被连接过
                linker[v] = u;
                linker[u] = v;//便于剪枝
                return true;
            }
        }
    }
    return false;
}
int hungary(){
    int res = 0;
    memset(linker,0,sizeof(linker));
    for(int u=1;u<=un;u++){
        //遍历所有u集合点
        if(!linker[u]){
            memset(vis,false,sizeof(vis));//由于已有前面节点新建的链接 所以之前的vis需要充重置 
            if(dfs(u)) res++;
        }
            
    }
    return res;
}
int main(){
    return 0;
}