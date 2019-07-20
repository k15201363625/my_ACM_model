//三种方法
//离线：tarjan 在线 倍增   /   st_rmq+dfs序
//tarjan O(n+q)
//倍增 O(nlogn+qlogn)
//st_rmq+dfs序 O(nlogn+q)
//两种在线算法都需要nlogn预处理
//poj
//tarjan
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 1e4+10;
int ind[N];
int fa[N];
bool vis[N];
int head[N],nxt[N],to[N];
int mm;
int a,b;
int n;
bool flag = false;
void add_edge(int a,int b){
    nxt[++mm] = head[a];
    head[a] = mm;
    to[mm] = b;
    ind[b]++;
}
int find(int x){
    if(fa[x]==x)
        return x;
    return fa[x] = find(fa[x]);
}
void join(int a,int b){
    int aa=find(a);
    int bb=find(b);
    if(aa==bb) return;
    fa[aa] = bb;
}
void init(int n){
    for(int i=1;i<=n;i++){
        fa[i] = i;
    }
    flag = false;
    for(int i=1;i<=n;i++)
        ind[i] = 0,vis[i]=0,head[i]=0;
    for(int i=1;i<=mm;i++)
        nxt[i] = 0;
    mm = 0;

}
//由于只需要一个 所以使用tarjan找到就输出 并且退出 更快

void tarjan(int now){
    if(flag)
        return;
    vis[now]=true;
    for(int i=head[now];i;i=nxt[i]){
        int v = to[i];
        if(vis[v])
            continue;
        tarjan(v);
        if(flag)
            return;
        //每当一个子节点全部完成 则合并到同一类 方便子树之间的查找
        join(now,v);
    }
    //每当当前节点子树处理完毕 则对于当前节点本身进行查询结果的得出过程 保证子树内的关联查询能全部正确
    //本题只需要查找与唯一的查询的关系就可以 不需要遍历所有相关查询 及时exit就可以
    if(now==a&&vis[b]){
        printf("%d\n",find(b));
        flag = true;
        return;
    }
    if(now==b&&vis[a]){
        printf("%d\n",find(a));
        flag = true;
        return;
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init(n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            // add_edge(b,a);//是树 并且方向性明确 所以不能添加双向边 并且需要积累ind
        }
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;i++)
            if(ind[i]==0){
                tarjan(i);
                break;//预防有多个根节点符合
            }
    }
    
    return 0;
}
//tarjan 失败 未知原因

//dfs + lca
//神奇ac
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
const int N = 1e4+10;
int ind[N];
bool vis[N];
int head[N],nxt[N],to[N];
int mm;
int a,b;
int n;
bool flag = false;
void add_edge(int a,int b){
    nxt[++mm] = head[a];
    head[a] = mm;
    to[mm] = b;
    ind[b]++;
}
//多组输入情况下初始化极其重要
void init(int n){
    flag = false;
    for(int i=1;i<=n;i++)
        ind[i] = 0,vis[i]=0,head[i]=0,depth[i]=0;
    for(int i=1;i<=mm;i++)
        nxt[i] = 0;
    mm = 0;

}
//核心算法 dfs统计深度 并且记录父子关系 同时得到fa表
int fa[N][25];
int depth[N];
int root;
void dfs(int u,int pre){
    fa[u][0] = pre;
    depth[u] = depth[pre]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(v!=pre)
            dfs(v,u);
    }
}
void init_fa(){//获得倍增的fa表
    dfs(root,0);
    for(int j=0;1<<(j+1)<n;j++){
        for(int i=1;i<=n;i++){
            if(fa[i][j]==0) fa[i][j+1]=0;
            else fa[i][j+1] = fa[fa[i][j]][j];
        }
    }
}
//倍增法实现二分查找
int lca(int u,int v){
    if(depth[u]>depth[v])
        swap(u,v);
    int tmp = depth[v] - depth[u];
    //借助树状数组思想 使用二进制消元 找到相同高度--skill
    for(int i=0;(1<<i)<=tmp;i++){
        if((1<<i)&tmp)
            v = fa[v][i];
    }
    //到达相同高度
    if(u==v)
        return u;
    //二者从某一高度的祖先开始共同瞎讲寻找最近的祖先 由于二进制关系 等效于二分查找
    for(int i=int(log2(n*1.0));i>=0;i--){
        //寻找最近的祖先
        //相当于对于目标高度 使用从高位开始的二进制试探方法 
        //利用二进制数可以构成任意的数字的性质进行类似二分的对数复杂度搜索
        if(fa[u][i]!=fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init(n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            // add_edge(b,a);//是树 并且方向性明确 所以不能添加双向边 并且需要积累ind
        }
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;i++)
            if(ind[i]==0){
                root = i;
                break;
            }
        init_fa();
        int ans = lca(a,b);
        printf("%d\n",ans);
    }
    
    return 0;
}

//dfs序+rmq
/*
类比普通rmq问题 查找区间内的最小值
lca就是哈找在dfs序的表中 dep最小的点 所以可以通过dfs得到dfs序
通过dfs序构建以器为索引 以dep为值得rmq表 在rmq中快速得到lca
难点：
这里st表示基于tot数量的表格 统计depth 而tot在边 点时候更新 共有2*n-1
所以st表通常使用2*n-1作为大小
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N = 1e4+10;
int ind[N];
int head[N],nxt[N],to[N];
int mm;
int a,b;
int n;
bool flag = false;
int root = 0;

int depth[N<<1];
int dfn[N];//每个节点在dfs中出现的实时间 一个节点可能出现多次 但是这里只记录第一次
//dfn的数值在1-2*n-1之间
int dp[N<<1][25];//开小了直接报错 因为这是基于tot的
int id[N<<1];
int tot = 0;//标志dfn起点
//得到深度 得到dfn序 得到id对应关系 方便查找
void dfs(int u,int pre){
    dfn[u] = ++tot;//只需要保存第一次
    // depth[tot] = depth[pre]+1;
    //经过调试 画图 输出depth数组发现了问题 -- 隐藏的很深
    //depth[pre] 不对 应该使用depth[ dfn[pre] ] 
    depth[tot] = depth[dfn[pre]]+1;
    id[tot] = u;
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(v!=pre){
            dfs(v,u);
            //每次遍历完成一个子分支 回到根节点一次
            id[++tot] = u;
            depth[tot] = depth[dfn[pre]]+1;
        } 
    }
}
// //使用之前的depth[pre]+1 报错 不明白？？？
// void dfs(int u,int pre,int dep){
//     dfn[u] = ++tot;//只需要保存第一次
//     depth[tot] = dep;
//     id[tot] = u;
//     for(int i=head[u];i;i=nxt[i]){
//         int v = to[i];
//         if(v!=pre){
//             dfs(v,u,dep+1);
//             //每次遍历完成一个子分支 回到根节点一次
//             id[++tot] = u;
//             depth[tot] = dep;
//         } 
//     }
// }
//基于tot构建st 2*n-1 由于目标不是求解最小的数值 而是求解最小元素的索引
void init_st(int n){
    int k = int(log2(1.0*n));
    for(int i=1;i<=n;i++) dp[i][0] = i;//小心
    for(int j=1;j<=k;j++)
        for(int i=1;i+(1<<j)-1<=n;i++){
            int a = dp[i][j-1];
            int b = dp[i+(1<<(j-1))][j-1];
            if(depth[a]<depth[b]) dp[i][j] = a;
            else dp[i][j] = b;
        }
}
int rmq(int l,int r){
    int k = int(log2(1.0*r-l+1));//自动下取整
    int a = dp[l][k];
    int b = dp[r-(1<<k)+1][k];
    if(depth[a]<depth[b]) return a;
    else return b;
}
int lca(int x,int y){
    int l = dfn[x];
    int r = dfn[y];
    if(l>r) swap(l,r);
    //小心 返回的应该是当前dfn序号的反向映射 即当前节点
    return id[rmq(l,r)];
}

void add_edge(int a,int b){
    nxt[++mm] = head[a];
    head[a] = mm;
    to[mm] = b;
    ind[b]++;
}
//多组输入情况下初始化极其重要
void init(int n){
    flag = false;
    for(int i=1;i<=n;i++)
        ind[i] = 0,head[i]=0;
    for(int i=1;i<=mm;i++)
        nxt[i] = 0;
    memset(depth,0,sizeof(depth));
    mm = 0;
    root = 0;
    tot=0;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init(n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            // add_edge(b,a);//是树 并且方向性明确 所以不能添加双向边 并且需要积累ind
        }
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;i++)
            if(ind[i]==0){
                root = i;
                break;
            }
        // dfs(root,0,1);
        dfs(root,0);
        init_st(2*n-1);
        int ans = lca(a,b);
        printf("%d\n",ans);
        // for(int i=1;i<=n;i++)
        //     cout<<dfn[i]<<" ";
        // cout<<endl;
        // for(int i=1;i<2*n-1;i++)
        //     cout<<depth[i]<<" ";
        // cout<<endl;
        // for(int i=1;i<2*n-1;i++)
        //     cout<<id[i]<<" ";
        // cout<<endl;
    }
    
    return 0;
}
/*
2 10 17 8 28 21 22 1 29 9 12 15 3 5 24 14
1 2 3 2 3 2 1 2 3 4 3 4 3 4 5 4 5 4 3 2 3 4 3 4 3 2 1 2 3 2
8 1 13 1 14 1 8 4 10 2 10 11 10 16 12 16 3 16 10 4 6 7 6 15 6 4 8 5 9 5

2 10 17 8 28 21 22 1 29 9 12 15 3 5 24 14
1 1 2 1 2 1 1 1 2 1 2 2 2 2 1 2 3 2 2 2 2 2 2 2 2 2 1 2 3 2
8 1 13 1 14 1 8 4 10 2 10 11 10 16 12 16 3 16 10 4 6 7 6 15 6 4 8 5 9 5

1
3 1 2 7 4
1 1 1 2 2 2 2 2
2 3 1 5 1 3 4 3

3
3 1 2 7 4
1 2 3 4 3 2 3 2
2 3 1 5 1 3 4 3
*/