//scoi2005 王室联邦 
//通过dfs 树上分块 保证每一块的大小在B-3B 之间
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1010;
//双向边存储 空间不足2n会w掉3个点
int stk[N<<1];
int head[N],nxt[N<<1],to[N<<1];
int tot,top;//tot记录当前划分的省份数量 top记录当前栈顶
int belong[N];
int center[N];
int B=1;
int mm;
//在dfs中进行分块 
//遍历完成一颗子树之后，只要栈中元素大于B就出栈 作为一个整体   当前节点dfs结束加入stack  最后dfs结束剩余的元素加入最后一个整体 总体保证[B-3B)
void dfs(int u,int fa){//记录父节点 方便找到center
    int t = top;
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];//得到当前指向
        if(v==fa)
            continue;
        dfs(v,u);
        //遍历完成一个子树 就要判断当前栈 才能保证符合要求 复杂度证明基于子树大小分析
        if(top-t>=B){
            tot++;
            // cout<<"now tot"<<tot<<endl;
            while(top!=t){
                belong[stk[top--]]=tot;
                // cout<<stk[top+1]<<" "<<belong[stk[top+1]]<<endl;
            }
            center[tot] = u;
            // cout<<"now u"<<u<<endl;
        }
    }
    //遍历过程结束 对于已遍历节点加入堆栈
    stk[++top] = u;//栈从1开始存储
}
//收尾工作
void solve(){
    dfs(1,0);
    // printf("------------%d %d------------\n",top,stk[top]);
    while(top>=1){
        belong[stk[top--]] = tot;
    }
}
//加边 使用存图的领接表形式存储 也可以使用左儿子右兄弟方式存储
//小心题目要求是双向边
void add_edge(int a,int b){
    nxt[++mm] = head[a];//从1开始存储
    head[a] = mm;
    to[mm] = b;
}


int main(){
    int n;
    int a,b;
    scanf("%d%d",&n,&B);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b);
        add_edge(b,a);
    }
    // for(int i=1;i<=n;i++){
    //     printf("%d-",head[i]);
    // }
    // cout<<"-------------------------------"<<endl;
    // cout<<mm<<endl;
    // for(int i=1;i<=mm;i++){
    //     printf("=%d %d=",nxt[i],to[i]);
    // }
    // cout<<"-------------------------------"<<endl;

    solve();
    printf("%d\n",tot);
    //、我傻啦
    for(int i=1;i<n;i++){
        printf("%d ",belong[i]);
    }
    printf("%d\n",belong[n]);

    for(int i=1;i<tot;i++){
        printf("%d ",center[i]);
    }
    printf("%d\n",center[tot]);
    return 0;
}