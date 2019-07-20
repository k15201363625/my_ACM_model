/*
���ƥ���������ƥ���ƥ��ߵ���Ŀ
��С�㸲������ѡȡ���ٵĵ㣬ʹ����һ����������һ���˵㱻ѡ��
����������ѡȡ���ĵ㣬ʹ������ѡ�����������
��С·��������������һ�� DAG�������޻�ͼ����ѡȡ������·����ʹ��ÿ�����������ҽ�����һ��·����·��������Ϊ 0���������㣩��

����1�����ƥ���� = ��С�㸲���������� Konig ����
����2�����ƥ���� = ��������
����3����С·�������� = ������ - ���ƥ����

��������һ���� BFS ���죨������ BFS ����
������������Ҫ������Ҷ�ӽڵ��Ϊƥ���
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
bool vis[MAXN];//���⵱��dfs�ظ�����
bool linker[MAXN];
int un,vn;
//��Ҫ����ߵĵ��ų�һ��
bool dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(!vis[v]){
            vis[v] = true;
            //dfs���õ���ʵ����u��ߵĽڵ�
            if(!linker[v]||dfs(linker[v])){//�������漯�ϵĽڵ��Ƿ����ӹ�
                linker[v] = u;
                linker[u] = v;//���ڼ�֦
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
        //��������u���ϵ�
        if(!linker[u]){
            memset(vis,false,sizeof(vis));//��������ǰ��ڵ��½������� ����֮ǰ��vis��Ҫ������ 
            if(dfs(u)) res++;
        }
            
    }
    return res;
}
int main(){
    return 0;
}