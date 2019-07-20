#include<iostream>
using namespace std;
const int maxn = 1e5+7;
/*һά��״����*/
int a[maxn];
int n;

//�õ�ĩβ1����Ӧ������
//x��Ϊ���� �±��1��ʼ
int lowbit(int x){
    return x&(-x);
}
//�����޸������ѯ
void update(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        a[i]+=v;
    }
}
int getsum(int x){
    int res = 0;
    for(int i=x;i;i-=lowbit(i)){
        res+=a[i];
    }
    return res;
}

int query(int l,int r){
    if(l<1) return -1;
    if(l==1) return getsum(r);
    return getsum(r)-getsum(l-1);
}
//���� �����ѯ �����޸�----��ʱ����Ľӿ��ⲿ���ܵ��� ��������ì�� �ڲ���������Ľӿ�
//��3-6����+5 �൱��3+5 7-5
int query_one_point(int x){
    return getsum(x);
}
void update_block(int l,int r,int v){
    if(l>=1){
        update(l,v);
        if(r<n)
            update(r+1,-v);
    }
}
/*��ά��״����*/
// ÿһ����״����ڵ��е����洢һ����״����
//������������ѯ
int c[maxn][maxn];
void update(int x,int y,int v){
    for(int i=x;i<=n;i+lowbit(i))
        for(int j=y;j<=n;j+=lowbit(j))
            c[i][j]+=v;
}
int getsum(int x,int y){
    if(x==0||y==0)
        return 0;
    int res = 0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            res+=c[i][j];
    return res;
}
//x1 y1 < x2 y2
int query2dblock(int x1,int y1,int x2,int y2){
    //x1==1 y1==1 ��+/- 0��Ӱ��
    int res = getsum(x2,y2);
    res -= getsum(x1-1,y2);
    res -= getsum(x2,y1-1);
    res += getsum(x1-1,y1-1);
    return res; 
}
//����������� �����ѯ
//���������˼�� ���Ǿ���ϸ��������ͬ
int query_one_ponit2d(int x,int y){
    return getsum(x,y);
}
void update_block2d(int x1,int y1,int x2,int y2,int v){
    update(x1,y1,v);
    update(x1,y2+1,-v);
    update(x2+1,y1,-v);
    update(x2+1,y2+1,v);
}

/*
Note:
����ȥ���޸ǵ����ѯ ����ʵ����ҪС��
���Ȱ�������ֵ�����洢 ֮���õ��յ�(0)����/���� ��ʼ�����������
��ѯֻ��Ҫ�õ������ϵ����ѯ�Ľ��+ԭʼ��������ݾͿ���
������ֿ��洢 ��ᵥ���ѯ��ͬʱ��ǰ׺����ֵһͬ���� ��������
*/
int main(){
    return 0;
}