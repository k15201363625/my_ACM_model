/*
dijstkra �㷨 
��ͬ�ڹ���������� �������ȶ���ά�� ���и��� 
ÿ��ʹ����̵Ľ��и���
��������յ������ǰ�˳� ��Ϊ���Ǳ�Ȼ����̵�
spfa����Ҳ�����˳� ��Ϊ�������ٴα�����
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
            if(now==t)//ֻҪ�ߵ��յ���Ѿ��������·
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

