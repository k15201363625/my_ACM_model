//��С���������mcmf 
//by Ȥѧ�㷨
//��С���������---�������������µ���С������ 
//ÿ��ʹ��spfa�ҵ���С����·�� ����С����·���Ͻ�������һ�����· 
//������sap isap dinic �е�˼�� ���Ǿ��е����Ե�Ѱ������· 
//dinic����bfs�õ��ľ���ԭ��Ĳ�ν��� isap���ھ�����ľ������ ek(sap)�����Բ�����������isap�ĵ������Ż�
//˳�㸴ϰspfa�÷� �Լ��жϸ�Ȩ���ķ��� spfa����Ҫע��--·����Ҫ����������·�������µ����·
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
int mm;//��ʾ�����Ŀ 01 23 45 Ϊһ��
// int que[M];//���ܴ�С���� �о���Ҫn*n����
// int head=1,tail=1;
int cnt[N];//��Ӵ���
int pre[N];//��ǰ��ǰ����
bool vis[N];
int dis[N];//��������ڵ����С����
int maxflow,mincost;
void _add_edge(int a,int b,int c,int d){//��ӵ�ʱ��ֻ��Ҫ˳���������� �����  �Ӷ��γɻ��ͼ -- ����ͼ ����ͼ
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
    _add_edge(b,a,0,-d);//С�� cost�Ǹ��� cap��0
}
void init(){
    memset(head,-1,sizeof(head));//��֤����nxtΪ-1
    mm = 0;
    maxflow = 0;
    mincost = 0;
}
void spfa_init(int n){
    memset(cnt,0,sizeof(cnt));
    memset(vis,false,sizeof(vis));
    memset(pre,-1,sizeof(pre));//���ڴ�0��ʼ ������Ҫ��ʼ����-1
    for(int i=1;i<=n;i++){
        dis[i] = INF;
    }
}
bool spfa(int s,int t,int n){//���¸��� �¸���
    queue<int> que;
    //���ȳ�ʼ��
    spfa_init(n);
    vis[s] = true;
    cnt[s]++;
    que.push(s);
    dis[s] = 0;
    int top;
    while(!que.empty()){
        top = que.front();
        que.pop();
        //����ȱ��
        vis[top] = false;
        for(int i=head[top];~i;i=e[i].nxt){//С�ĳ�ʼ�� ����Ҫ��head��ʼ����-1����
            int v = e[i].to;
            if(dis[v]>dis[top]+e[i].cost && e[i].flow<e[i].cap){
                dis[v] = dis[top]+e[i].cost;
                pre[v] = i;//�����Ƿ��ɳ� ����Ҫ����
                if(!vis[v]){
                    vis[v] = true;
                    cnt[v]++;
                    que.push(v);
                    if(cnt[v]>n){
                        //printf("���ڸ���\n");
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
        //�������
        for(int i=pre[t];~i;i=pre[e[i^1].to])//�õ�����ߵ�v�Ӷ��õ�ǰ�ڵ� ����ǿ ˫�ߴ洢������
            minf = min(minf,e[i].cap - e[i].flow);
        maxflow += minf;
        for(int i=pre[t];~i;i=pre[e[i^1].to]){
            e[i].flow+=minf;
            e[i^1].flow-=minf;
            // e[i^1].cap-=minf;����һֱ��0�Ϳ��� ֻҪ��ע�������� ��Ϊ����cap=0 flow<0��������
        }
        mincost+=dis[t]*minf;
    }
}
int main(){
    int n,m,s,t;
    init();//������
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int aa,bb,cc,dd;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
        add_edges(aa,bb,cc,dd);
    }
    MCMF(s,t,n);
    printf("%d %d\n",maxflow,mincost);
}