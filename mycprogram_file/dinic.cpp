//未知报错不懂

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 1e4+5;
const ll INF = 0x3f3f3f3f;
//getchar可以替代
// inline char nc()
// {
//     static char buf[MAXN],*p1=buf,*p2=buf;
//     return p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXN,stdin),p1==p2)?EOF:*p1++;
// }

inline int read(){
    char c = getchar();int res=0;bool f = 0;
    while(c<'0'||c>'9'){
        if(c=='-') f = 1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        res = (res<<3)+(res<<1)+(c-'0');
        c = getchar();
    }
    return f?(-res):res;
}

int S,T;
struct edge{
    int t,nxt;
    ll cap;
}edges[maxn*10];

int head[maxn],cur[maxn],dis[maxn];
int q[maxn+10],l,r;
int cnt = 0;

void init(){
    cnt = 0;//从0开始存 方便^访问
    memset(head,-1,sizeof(head));//-1有效 全1 memset 只能用于-1/0
}
void add_edge(int x,int y,int z){
    edges[cnt].t = y;
    edges[cnt].cap = z;
    edges[cnt].nxt = head[x];
    head[x] = cnt++; 
}
//分层
bool bfs(){
    l = 0,r = 0;
    memset(dis,-1,sizeof(dis));
    q[r++] = S; 
    dis[S] = 0;
    int h,t;
    while(l<r){
        h = q[l++];
        for(int i=head[h];i!=-1;i=edges[i].nxt){
            t = edges[i].t;
            if(dis[t]==-1&&edges[i].cap>0){
                dis[t] = dis[h] + 1;
                q[r++] = t;
                if(t==T)
                    break;
            }
        }
    }
    return dis[T] != -1;
}
//寻找增广
ll dfs(int now,ll nowcap){
    if(now==T||nowcap==0)//实际上最多==0
        return nowcap;
    ll res = 0,flow;
    int t;
    //当前弧优化
    for(int &i = cur[now];i!=-1;i=edges[i].nxt){
        t = edges[i].t;
        if(dis[t]==dis[now]+1 && (flow=dfs(t,min(nowcap-res,edges[i].cap)))>0){
            edges[i].cap -= flow;
            edges[i^1].cap += flow;
            res += flow;
            //当前点优化--针对对于当前点子孙的dfs过程
            if(res==nowcap)//实际上只能最多==
                return nowcap;
        }
    }
    //炸点优化(一开始nowcap>0)--针对其他点到当前点时的dfs优化
    if(!res)
        dis[now] = -1;
    return res;
}
int n,m;//点边个数
ll dinic(){
    ll ans = 0;
    while(bfs()){
        //memcpy(cur,head,sizeof(head));
        for(int i=1;i<=n;i++)//head/cur从一下标开始
            cur[i] = head[i];
        ans += dfs(S,INF);
    }
    return ans;
}

int main(){
    // #ifdef WIN32
    //     freopen("test.in",'r',stdin);
    // #endif
    n = read(),m = read(),S = read(),T = read();
    //m = read(),n=read(),S=1,T=n;
    init();//初始化当前head edges不需要会自动覆盖
    for(int i=1;i<=m;i++){
        int x,y,z;
        x = read(),y = read(), z = read();
        add_edge(x,y,z);
        add_edge(y,x,z);
    }
    ll res = dinic();
    printf("%lld\n",res);

    return 0;
}