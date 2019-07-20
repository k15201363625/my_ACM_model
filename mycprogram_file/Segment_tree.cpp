//cdoj 1057
//learn from qsc
//segment tree--static structure
//block update and query + lazy
#include<bits/stdc++.h>
using namespace std;
const int maxn = 155+7;
struct node{
    int l,r;
    long long sum,lazy;
    void update(long long v){//long long С��
        sum+=1ll*(r-l+1)*v;
        lazy+=v;
    }
}tree[maxn*4];
int n,q;
int a[maxn];
void push_up(int x){
    tree[x].sum = tree[x<<1].sum + tree[x<<1|1].sum;
}
void push_down(int x){
    //lazy���С��
    int lazyval = tree[x].lazy;
    if(lazyval!=0){
        tree[x<<1].update(lazyval);
        tree[x<<1|1].update(lazyval);
        tree[x].lazy=0;//���
    }
}

void build(int x,int l,int r){
    tree[x].l = l,tree[x].r = r,tree[x].sum=0,tree[x].lazy=0;
    if(l==r){
        tree[x].sum = a[l-1];
        return;
    }
    int mid = (l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    push_up(x);
}
//����������²�ѯ ����Ĳ���lr��ʾĿ������ ����lr����ı�
//ԭ��ͨ������lr �Լ�mid������Χ ����С�Ĳ�Ҫͬ����mid,mid+1��Ϊ���� ����ʼ����lr
//��ͬ�߶���д������ ���tree��lrҲ��Ϊ���� ����Ҫ�ı�tree��lr����
void update(int x,int l,int r,long long v){
    int ll = tree[x].l,rr = tree[x].r;
    if(ll>=l&&rr<=r)
        tree[x].update(v);
    else{
        push_down(x);
        int mid = (ll+rr)>>1;
        if(mid>=l)
            update(x<<1,l,r,v);
        if(mid<r)
            update(x<<1|1,l,r,v);
    }
}
long long query(int x,int l,int r){
    int ll = tree[x].l,rr = tree[x].r;
    if(ll>=l&&rr<=r)
        return tree[x].sum;
    else{
        push_down(x);
        long long ans = 0;
        int mid = (ll+rr)>>1;
        if(mid>=l)
            ans+=query(x<<1,l,r);
        if(mid<r)
            ans+=query(x<<1|1,l,r);
        return ans;
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    scanf("%d",&q);
    int l,r,v;
    for(int i=0;i<q;i++){
        scanf("%d%d%d",&l,&r,&v);
        update(1,l,r,v);
        printf("%lld\n",query(1,l,r));
    }
    return 0;
}
