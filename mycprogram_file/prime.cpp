/*
ʹ�����ȶ���ά��
ÿ��ѡ���ڼ��������ӵ���ߵ���С�ı� ����֤����ȷ��

*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<functional>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 111;

struct edge{
    int to;
    ll cost;
    edge(){}
    edge(int x,ll y):to(x),cost(y){}
    bool operator<(const edge& o) const{//���ڱȽϺ��� �������س�const�������� operator<(const)const ���Բ�������
        return o.cost < cost;
    }
};

vector<edge> head[maxn];
priority_queue<edge> Q;
bool vis[maxn];

void init(int m){
    memset(vis,0,sizeof(vis));
    while(!Q.empty()) Q.pop();
    for(int i=1;i<=m;i++)
        head[i].clear();
}

ll prim(){
    ll res = 0;
    vis[1] = 1;
    for(int i=0;i<head[1].size();i++){
        Q.push(head[1][i]);
    }
    edge e;
    while(!Q.empty()){
        //����һ�����д���
        e = Q.top();
        Q.pop();
        if(vis[e.to])
            continue;
        vis[e.to] = 1;
        res += e.cost;
        for(int i=0;i<head[e.to].size();i++)
            Q.push(head[e.to][i]);
    }
    return res;
}
int n,m;
int main(){
    while(scanf("%d%d",&n,&m)==2){
            //С��
        if(n==0)
            break;
        init(m);
        int x,y;
        ll z;
        ll res = 0;
        for(int i=0;i<n;i++){
            scanf("%d%d%lld",&x,&y,&z);//С�� ���1��ʼ �ӵ�
            head[x].push_back(edge(y,z));
            head[y].push_back(edge(x,z));
        }
        res = prim();
        for(int i=1;i<=m;i++)
            if(!vis[i])
                res = -1;

        if(res==-1)
            printf("?\n");
        else
            printf("%lld\n",res);
    }
    return 0;
}