/*
ʹ��st�괦��rmq���� ˼·��̬�滮
O��nlogn�� Ԥ���� O��1����ѯ �ռ�O��nlogn�� �����߶�����ѯ����ռ���� 
˼·�Ǳ����㷨����rmq���� ���ϱ������Կ��ٴ���̬lca tarjanֻ�ܴ���̬lca
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
//һ��ע��+1 -1 �����ѵ� �״�
void init_st_rmq(){
    for(int i=1;i<=n;i++)
        st[i][0] = a[i];
    for(int j=1;(1<<j)<=n;j++)//��С���䵽��������и��� dp
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    //Ԥ����help
    for(int i=1;i<=n;i++){
        //ֱ�ӱ������� ����ʹ�ö������� ���Ӷ�nlogn
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
    //������
    init_st_rmq();
    //������
    return 0;
}
