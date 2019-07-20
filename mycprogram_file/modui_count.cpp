//Ī���㷨ģ����Ŀ СB��ѯ�� bzoj 3781
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 5e5+10;
int B = 1;
int n,m,k;
long long cnt[N];
long long ans[N];
int a[N];
long long res = 0;
struct Query{
    int l,r,id;
    bool operator<(const Query& o) const{
        return l/B==o.l/B ? r<o.r : l<o.l;
    }
}q[N];
void add(int x){
    cnt[x]++;
    res+=cnt[x]*2-1;
}

void del(int x){
    cnt[x]--;
    res-=cnt[x]*2+1;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    B = int(n/sqrt(m));//��׼�����ĸ��ӶȽ��
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id = i;
    }
    sort(q+1,q+m+1);
    int l = 1,r = 0;//һ��ʼ��Ҫһ��Ԫ�ض�û��
    for(int i=1;i<=n;i++){
        
        while(l<q[i].l){
            del(a[l++]);
        }
        while(l>q[i].l){
            add(a[--l]);
        }
        while(r>q[i].r){
            del(a[r--]);
        }
        while(r<q[i].r){
            add(a[++r]);
        }
        ans[q[i].id] = res;
    }
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}