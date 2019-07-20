// #include<bits/stdc++.h>
#include<algorithm>
#include<cstdio>
#include<iostream>

using namespace std;
const int INF = 1e9;
const int maxn = 205;
int n,m;
int mp[maxn][maxn];

void init(int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(i==j)
                mp[i][j]=0;
            else
                mp[i][j]=INF;
}
//mp[k][i][j] = min(mp[k-1][i][k]+mp[k-1][k][j],mp[k-1][i][j])
//mp[k][i][k] = mp[k-1][i][k]   mp[k][k][j] = mp[k-1][k][j]
//¿ÉÒÔÑ¹Ëõ×´Ì¬

void floyd(int n){
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mp[i][j] = min(mp[i][j],mp[i][k]+mp[k][j]);
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        init(n);
        int x,y,z;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&z);
            mp[x][y] = min(z,mp[x][y]);
            mp[y][x] = min(z,mp[y][x]);
        }
        int s,t;
        scanf("%d%d",&s,&t);
        floyd(n);
        if(mp[s][t]==INF) 
            printf("-1\n");
        else
            printf("%d\n",mp[s][t]);
        
    }
    return 0;
}