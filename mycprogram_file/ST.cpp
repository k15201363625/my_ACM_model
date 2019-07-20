/*
使用st标处理rmq问题 思路动态规划
O（nlogn） 预处理 O（1）查询 空间O（nlogn） 比起线段树查询更快空间更大 
思路是倍增算法处理rmq问题 树上倍增可以快速处理动态lca tarjan只能处理静态lca
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 1e6+7;
const int maxm = 25;
int st[maxn][maxm];
int help[maxn];
int a[maxn];
int n;
//一下注意+1 -1 处理难点 易错
void init_st_rmq(){
    for(int i=1;i<=n;i++)
        st[i][0] = a[i];
    for(int j=1;(1<<j)<=n;j++)//从小区间到大区间进行更新 dp
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    //预处理help
    for(int i=1;i<=n;i++){
        //直接暴力搜索 可以使用二分搜索 复杂度nlogn
        int k=0;
        while((1<<(k+1))<=i){
            k++;
        }
        help[i] = k;
    }
}
int query_st_rmq(int l,int r){
    int k = help[r-l+1];
    return min(st[l][k],st[r-(1<<k)+1][r]);
}

int main(){
    //。。。
    init_st_rmq();
    //。。。
    return 0;
}
