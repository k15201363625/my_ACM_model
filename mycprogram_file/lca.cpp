//���ַ���
//���ߣ�tarjan ���� ����   /   st_rmq+dfs��
//tarjan O(n+q)
//���� O(nlogn+qlogn)
//st_rmq+dfs�� O(nlogn+q)
//���������㷨����ҪnlognԤ����
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
//����ֻ��Ҫһ�� ����ʹ��tarjan�ҵ������ �����˳� ����

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
        //ÿ��һ���ӽڵ�ȫ����� ��ϲ���ͬһ�� ��������֮��Ĳ���
        join(now,v);
    }
    //ÿ����ǰ�ڵ������������ ����ڵ�ǰ�ڵ㱾����в�ѯ����ĵó����� ��֤�����ڵĹ�����ѯ��ȫ����ȷ
    //����ֻ��Ҫ������Ψһ�Ĳ�ѯ�Ĺ�ϵ�Ϳ��� ����Ҫ����������ز�ѯ ��ʱexit�Ϳ���
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
            // add_edge(b,a);//���� ���ҷ�������ȷ ���Բ������˫��� ������Ҫ����ind
        }
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;i++)
            if(ind[i]==0){
                tarjan(i);
                break;//Ԥ���ж�����ڵ����
            }
    }
    
    return 0;
}
//tarjan ʧ�� δ֪ԭ��

//dfs + lca
//����ac
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
//������������³�ʼ��������Ҫ
void init(int n){
    flag = false;
    for(int i=1;i<=n;i++)
        ind[i] = 0,vis[i]=0,head[i]=0,depth[i]=0;
    for(int i=1;i<=mm;i++)
        nxt[i] = 0;
    mm = 0;

}
//�����㷨 dfsͳ����� ���Ҽ�¼���ӹ�ϵ ͬʱ�õ�fa��
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
void init_fa(){//��ñ�����fa��
    dfs(root,0);
    for(int j=0;1<<(j+1)<n;j++){
        for(int i=1;i<=n;i++){
            if(fa[i][j]==0) fa[i][j+1]=0;
            else fa[i][j+1] = fa[fa[i][j]][j];
        }
    }
}
//������ʵ�ֶ��ֲ���
int lca(int u,int v){
    if(depth[u]>depth[v])
        swap(u,v);
    int tmp = depth[v] - depth[u];
    //������״����˼�� ʹ�ö�������Ԫ �ҵ���ͬ�߶�--skill
    for(int i=0;(1<<i)<=tmp;i++){
        if((1<<i)&tmp)
            v = fa[v][i];
    }
    //������ͬ�߶�
    if(u==v)
        return u;
    //���ߴ�ĳһ�߶ȵ����ȿ�ʼ��ͬϹ��Ѱ����������� ���ڶ����ƹ�ϵ ��Ч�ڶ��ֲ���
    for(int i=int(log2(n*1.0));i>=0;i--){
        //Ѱ�����������
        //�൱�ڶ���Ŀ��߶� ʹ�ôӸ�λ��ʼ�Ķ�������̽���� 
        //���ö����������Թ�����������ֵ����ʽ������ƶ��ֵĶ������Ӷ�����
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
            // add_edge(b,a);//���� ���ҷ�������ȷ ���Բ������˫��� ������Ҫ����ind
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

//dfs��+rmq
/*
�����ͨrmq���� ���������ڵ���Сֵ
lca���ǹ�����dfs��ı��� dep��С�ĵ� ���Կ���ͨ��dfs�õ�dfs��
ͨ��dfs�򹹽�����Ϊ���� ��depΪֵ��rmq�� ��rmq�п��ٵõ�lca
�ѵ㣺
����st��ʾ����tot�����ı�� ͳ��depth ��tot�ڱ� ��ʱ����� ����2*n-1
����st��ͨ��ʹ��2*n-1��Ϊ��С
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
int dfn[N];//ÿ���ڵ���dfs�г��ֵ�ʵʱ�� һ���ڵ���ܳ��ֶ�� ��������ֻ��¼��һ��
//dfn����ֵ��1-2*n-1֮��
int dp[N<<1][25];//��С��ֱ�ӱ��� ��Ϊ���ǻ���tot��
int id[N<<1];
int tot = 0;//��־dfn���
//�õ���� �õ�dfn�� �õ�id��Ӧ��ϵ �������
void dfs(int u,int pre){
    dfn[u] = ++tot;//ֻ��Ҫ�����һ��
    // depth[tot] = depth[pre]+1;
    //�������� ��ͼ ���depth���鷢�������� -- ���صĺ���
    //depth[pre] ���� Ӧ��ʹ��depth[ dfn[pre] ] 
    depth[tot] = depth[dfn[pre]]+1;
    id[tot] = u;
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(v!=pre){
            dfs(v,u);
            //ÿ�α������һ���ӷ�֧ �ص����ڵ�һ��
            id[++tot] = u;
            depth[tot] = depth[dfn[pre]]+1;
        } 
    }
}
// //ʹ��֮ǰ��depth[pre]+1 ���� �����ף�����
// void dfs(int u,int pre,int dep){
//     dfn[u] = ++tot;//ֻ��Ҫ�����һ��
//     depth[tot] = dep;
//     id[tot] = u;
//     for(int i=head[u];i;i=nxt[i]){
//         int v = to[i];
//         if(v!=pre){
//             dfs(v,u,dep+1);
//             //ÿ�α������һ���ӷ�֧ �ص����ڵ�һ��
//             id[++tot] = u;
//             depth[tot] = dep;
//         } 
//     }
// }
//����tot����st 2*n-1 ����Ŀ�겻�������С����ֵ ���������СԪ�ص�����
void init_st(int n){
    int k = int(log2(1.0*n));
    for(int i=1;i<=n;i++) dp[i][0] = i;//С��
    for(int j=1;j<=k;j++)
        for(int i=1;i+(1<<j)-1<=n;i++){
            int a = dp[i][j-1];
            int b = dp[i+(1<<(j-1))][j-1];
            if(depth[a]<depth[b]) dp[i][j] = a;
            else dp[i][j] = b;
        }
}
int rmq(int l,int r){
    int k = int(log2(1.0*r-l+1));//�Զ���ȡ��
    int a = dp[l][k];
    int b = dp[r-(1<<k)+1][k];
    if(depth[a]<depth[b]) return a;
    else return b;
}
int lca(int x,int y){
    int l = dfn[x];
    int r = dfn[y];
    if(l>r) swap(l,r);
    //С�� ���ص�Ӧ���ǵ�ǰdfn��ŵķ���ӳ�� ����ǰ�ڵ�
    return id[rmq(l,r)];
}

void add_edge(int a,int b){
    nxt[++mm] = head[a];
    head[a] = mm;
    to[mm] = b;
    ind[b]++;
}
//������������³�ʼ��������Ҫ
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
            // add_edge(b,a);//���� ���ҷ�������ȷ ���Բ������˫��� ������Ҫ����ind
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