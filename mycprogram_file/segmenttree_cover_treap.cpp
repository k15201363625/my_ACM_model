// #include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
// #include<cctype>
#include<cmath>
using namespace std;
const int maxn = 5e5+7;
const int INF = 0x7fffffff;
int a[maxn];

// inline int read(){
//     int res = 0;char c = getchar(); bool neg = 0;
//     while(!isdigit(c)){neg|=(c=='-'); c = getchar();}
//     while(isdigit(c)){res = (res<<3)+(res<<1)+(48^(int)c);c=getchar();}
//     return neg?-res:res;  
// }
//����namespace�����Խṹ���ı�ʾ������ȫ������ ͬ����ѧ���뷽����ṹ��
//�����treapд��
namespace treap{
    int val[maxn*50],size[maxn*50],ch[maxn*50][2],rnk[maxn*50],tot;
    int seed = 233;
    inline void update(int rt){
        size[rt] = size[ch[rt][0]]+size[ch[rt][1]]+1;
    }
    inline int newrand(){
        return seed = (seed*482711LL%INF);
    }
    inline int newnode(int v){
        val[++tot] = v;
        size[tot] = 1;
        rnk[tot] = newrand();
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }
    inline void split(int rt,int v,int &x,int &y){
        if(rt==0){
            x=y=0;
            return;
        }
        if(val[rt]<=v){
            x = rt;
            split(ch[rt][1],v,ch[x][1],y);
        }else{
            y = rt;
            split(ch[rt][0],v,x,ch[y][0]);
        }
        update(rt);
    }

    inline int merge(int x,int y){
        if(x==0||y==0)
            return x+y;
        if(rnk[x]<rnk[y]){
            ch[x][1] = merge(ch[x][1],y);
            update(x);
            return x;
        }else{
            ch[y][0] = merge(x,ch[y][0]);
            update(y);
            return y;
        }
    }
    //�����޸�root
    inline void insert_node(int &root,int v){
        int a = 0,b = 0;
        split(root,v,a,b);
        root = merge(merge(a,newnode(v)),b);
    }
    inline void delete_node(int &root,int v){
        int a = 0,b = 0,c = 0;
        split(root,v,a,b);
        split(a,v-1,a,c);
        c = merge(ch[c][0],ch[c][1]);
        root = merge(merge(a,c),b);
    }
    //��ͬ����ͨ������treap Ϊ�˷����������ǵĴ��� ��-1
    inline int get_rnk(int &root,int v){
        int a = 0,b = 0;
        split(root,v-1,a,b);
        int res = size[a] - 1;//��Ϊ��������һ��-INF�ڵ� ���ұ���ҪС��Ԫ�ظ���
        root = merge(a,b);
        return res;
    }
    //���ܴ� ����  ����root ���ڱ���������ָ��������root
    inline int get_kth(int root,int k){
        while(size[ch[root][0]]+1!=k){
            if(size[ch[root][0]+1>k]){
                root = ch[root][0];
            }else{
                k -= size[ch[root][0]] + 1;
                root = ch[root][1];
            }
        }
        return val[root];
    }
    inline int get_pre(int &root,int v){
        int a = 0,b = 0;
        split(root,v-1,a,b);
        int res = get_kth(a,size[a]);
        merge(a,b);
        return res;
    }
    inline int get_scc(int &root,int v){
        int a = 0,b = 0;
        split(root,v,a,b);
        int res = get_kth(b,1);
        root = merge(a,b);
        return res;
    }
}
//segmenttree + treap
int tree[maxn<<2];
//Ϊ�˷��� ����궨��
#define ls(r) (r<<1)
#define rs(r) (r<<1|1)
//sef=gmenttree ���� ԭ����tree[rt]����blockԪ�� ��������������root
void build(int rt,int l,int r){
    //����սڵ���Ϊ��֤
    treap::insert_node(tree[rt],-INF);
    treap::insert_node(tree[rt],INF);
    //ԭ��ֻ��Ҫ�޸�����Ԫ�� ������Ҫ���������
    for(  int i=l;i<=r;i++)
        treap::insert_node(tree[rt],a[i]);
    if(l == r)
        return;
    int mid = (l+r)>>1;
    build(ls(rt),l,mid);
    build(rs(rt),mid+1,r);
    //��ͬ����ͨ�߶��� ���ﲻ��Ҫpushup
} 
//�ѵ�
void change(int rt,int l,int r,int pos,int v,int oldv){
//Ϊ��treap���� ��Ҫ�ṩԭʼvalue ��Ϊ��������
    if(l==r){
        a[l] = v;
        treap::delete_node(tree[rt],oldv);//pldv==a[l]
        treap::insert_node(tree[rt],v);
        return;
    }
    treap::delete_node(tree[rt],oldv);
    treap::insert_node(tree[rt],v);
    int mid = (l+r)>>1;
    if(pos<=mid) 
        change(ls(rt),l,mid,pos,v,oldv);
    else
        change(rs(rt),mid+1,r,pos,v,oldv);
}

//��ͬ����ͨ�� ��Ҫ�ҵ�С��Ԫ�صĸ��� ����ǰ���getrank��Ч
//�����Ҫ+1 ���ܵõ���ʵ��rnk
int get_rank(int rt,int l,int r,int ql,int qr,int v){
    if(ql<=l&&qr>=r)
        return treap::get_rnk(tree[rt],v);
    int res = 0;
    int mid = (l+r)>>1;
    if(ql<=mid)
        res += get_rank(ls(rt),l,mid,ql,qr,v);
    if(qr>mid)
        res += get_rank(rs(rt),mid+1,r,ql,qr,v);
    return res;
}
//���ѵ�
//���ڶ���� ��ѯ�ƶ�����k��Ԫ�� ��ͬ����Ϣ���Ժϲ� 
//Ŀ�꣺����һ���� �����ö�������
//�����ж����� ����ͨ��rnk�ж� ����ʹ��get_rank���� 
int get_kthnum(int ql,int qr,int k,int maxnum,int n){
    //����num ͨ��maxnum������С��������
    int l = 0,r = maxnum;
    int res = 0;
    while(l<=r){
        int mid = (l+r)>>1;
        int rnk = get_rank(1,1,n,ql,qr,mid);
        // if(rnk+1==k)
        //     return res = mid;
        // else if(rnk+1<k)
        //     l = mid+1;
        // else
        //     r = mid-1;
        if(rnk+1<=k){
            //�� ���4�Ƿ��ϵ�Ԫ�� ����û��3 ��ômid=3���� ����������
            //��mid���Ϲ�Ϊ�������� Ŀ��������**���ϵ���ҵ�mid����**
            l = mid + 1;
            res = mid;
        }else{
            r = mid - 1;
        }
    }
    return res;
}

int ans = 0;//ÿ��ʹ��������������ǰ ��Ҫ��������ans

//ǰ��������� ������ֵ���� ͬǰ��getrank���� һ������� һ������ֵ �����׺ϲ�����Ϣ
void get_pre(int rt,int l,int r,int ql,int qr,int v){
    if(ql<=l&&qr>=r){
        ans = max(ans,treap::get_pre(tree[rt],v));
        return;
    }
    int mid = (l+r)>>1;
    if(ql<=mid)
        get_pre(ls(rt),l,mid,ql,qr,v);
    if(qr>mid)
        get_pre(rs(rt),mid+1,r,ql,qr,v);
}
void get_next(int rt,int l,int r,int ql,int qr,int v){
    if(ql<=l&&qr>=r){
        ans = min(ans,treap::get_scc(tree[rt],v));
        return;
    }
    int mid = (l+r)>>1;
    if(ql<=mid) 
        get_next(ls(rt),l,mid,ql,qr,v);
    if(qr>mid)
        get_next(rs(rt),mid+1,r,ql,qr,v);
}



int main(){
    int n = 0,m = 0,maxnum = 0;
    //n = read(),m = read();
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        // a[i] = read();
        scanf("%d",&a[i]);
        maxnum = max(maxnum,a[i]);
    }
    build(1,1,n);
    int opt,ql,qr,k,pos,v;
    for(int i=1;i<=m;i++){
        // opt = read();
        scanf("%d",&opt);
        switch(opt){
            case 1:{
                // ql = read(),qr = read(),v = read();
                scanf("%d %d %d",&ql,&qr,&v);
                printf("%d\n",get_rank(1,1,n,ql,qr,v)+1);
                break;
            }
            case 2:{
                // ql = read(),qr = read(),k = read();
                scanf("%d %d %d",&ql,&qr,&k);
                printf("%d\n",get_kthnum(ql,qr,k,maxnum,n));
                break;
            }
            case 3:{
                // pos = read(),v = read();
                scanf("%d %d",&pos,&v);
                change(1,1,n,pos,v,a[pos]);
                break;
            }
            case 4:{
                // ql = read(),qr =read(),v = read();
                scanf("%d %d %d",&ql,&qr,&v);
                ans = -INF;
                get_pre(1,1,n,ql,qr,v);
                printf("%d\n",ans);
                break;
            }
            default:{
                // ql = read(),qr = read(),v = read();
                scanf("%d %d %d",&ql,&qr,&v);
                ans = INF;
                get_next(1,1,n,ql,qr,v);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
/*
bzoj �ж� �������ȥ
*/