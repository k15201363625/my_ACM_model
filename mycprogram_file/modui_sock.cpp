//Ī���㷨ģ���� 
//Сz������ ���������
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 5e5+10;
int B = 1;
int color[MAXN];
int cnt[MAXN],ans[MAXN][2];//ans������ cnt����������ĳ����ɫ��Ӧ�ĳ��ִ���
int len,son,mom;//�м���� ����ʹ��

inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
//���غ�������д��const const ���һ��const�ز����� 
struct Query{
    int l,r,id;
    bool operator < (const Query& other) const {
        return (l/B==other.l/B)?r<(other.r):(l<other.l);
    }

}q[MAXN];
void del(int x){//�����Ӧ������ɫ
    cnt[x]--;
    son-=cnt[x];
    len--;
    mom-=len;
}
void add(int x){
    son+=cnt[x];
    cnt[x]++;
    mom+=len;
    len++;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    B = int(n/sqrt(m));
    for(int i=1;i<=n;i++){
        scanf("%d",&color[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id = i;
    }
    int l=1,r=0;
    sort(q+1,q+m+1);
    for(int i=1;i<=m;i++){
        //��֦�ж� 
        if(q[i].l==q[i].r){
            ans[q[i].id][0] = 0;
            ans[q[i].id][1] = 1;
            continue;
        }

        while(l<q[i].l){
            del(color[l++]);
        }
        while(l>q[i].l){
            add(color[--l]);
        }
        while(r<q[i].r){
            add(color[++r]);
        }
        while(r>q[i].r){
            del(color[r--]);
        }
        //���½�����¼result
        int g = gcd(son,mom);
        ans[q[i].id][0] = son/g;
        ans[q[i].id][1] = mom/g;
    }
    for(int i=1;i<=m;i++){
        printf("%d\/%d\n",ans[i][0],ans[i][1]);
    }

    return 0;
}