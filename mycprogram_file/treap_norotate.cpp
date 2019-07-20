/*
FHQ Treap ����treap
���ô���ʵ�� ���� ����������
split  merge�ؼ�
split���԰���value rnk���� ���ﰴ��value����
���Ժϲ�����rnk���� ��֮����value����
ά���� value�����µĶ��������� ������ɵ�rnk�µ�С����/�����
���������������еĻ������ʶ����С����Ҳ�ѯ��k�� ǰ����̵�������ͨ��split mergeʵ��
*/
//��ͨƽ���� ģ����
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;
const int maxn = 1e6+7;
//�����
inline int read(){
    int res = 0;char c = getchar(); bool neg = 0;
    while(!isdigit(c)){
        neg |=(c=='-');//ֻҪ��- ��Զ��-
        c = getchar();
    }    
    while(isdigit(c)){
        res = (res<<3) + (res<<1) + (48^int(c));
        c = getchar();
    }
    return neg ? -res:res;
}


struct node{
    int size,val,rnk,lc,rc;
}treap[maxn];
int root = 0;
int tot = 0;
int seed = 233;
inline int newrand(){
    return seed = int(seed * 482711ll % INF);
}

inline void update(int root){
    treap[root].size = treap[treap[root].lc].size + treap[treap[root].rc].size + 1;
}

inline int add_node(int val){
    treap[++tot].val = val;
    treap[tot].lc = 0;
    treap[tot].rc = 0;
    treap[tot].rnk = newrand();
    treap[tot].size = 1;
    return tot;
}
//����val���� ���ֳ�<=val >val �����ն��������ʻ���
inline void split(int r,int& a,int& b,int val){//r����������
    //��������
    if(r==0){//���Ǵ���r==1
        a=b=0;
        return;
    }
    if(treap[r].val<=val){
        a = r;
        split(treap[r].rc,treap[a].rc,b,val);
    }else{
        b = r;
        split(treap[r].lc,a,treap[b].lc,val);
    }
    update(r);
}
//�ϲ������������������ ����һ�ߴ� һ��С Ϊ�������������� ����rnk����ϲ�����
inline void merge(int& r,int a,int b){
    //��������
    if(a==0||b==0){
        r = a+b;
        return;
    }
    if(treap[a].rnk<treap[b].rnk){
        r = a;
        merge(treap[r].rc,treap[a].rc,b);
    }else{
        r = b;
        merge(treap[r].lc,a,treap[b].lc);
    }
    update(r);
}

inline void insert_node(int &root,int val){
    int newnode = add_node(val);
    int a = 0,b = 0;
    split(root,a,b,val);
    merge(a,a,newnode);
    merge(root,a,b);
}
inline void delete_node(int &root,int val){
    int a = 0,b = 0,c = 0;
    split(root,a,b,val);
    split(a,a,c,val-1);
    merge(c,treap[c].lc,treap[c].rc);
    merge(a,a,c);
    merge(root,a,b);
}


//���϶���
inline int get_kth(int rt,int k){//��õ�k���Ԫ��
    while(treap[treap[rt].lc].size+1!=k){
        if(treap[treap[rt].lc].size>=k){
            rt = treap[rt].lc;
        }else{
            k -= treap[treap[rt].lc].size + 1;
            rt = treap[rt].rc;
        }
    }
    return treap[rt].val;
}


//����value���־Ϳ���
inline int get_rnk(int &root,int value){
    int a = 0,b = 0;
    split(root,a,b,value-1);
    int res = treap[a].size + 1; 
    merge(root,a,b);
    return res;
}
inline int get_pre(int &root,int value){
    int a = 0,b = 0;
    split(root,a,b,value-1);
    int res = get_kth(a,treap[a].size);
    merge(root,a,b);
    return res;
}
int get_scc(int &root,int value){
    int a = 0,b = 0;
    split(root,a,b,value);
    int res = get_kth(b,1);
    merge(root,a,b);
    return res;
}

int n;
int main(){
    n = read();
    //������ڵ�
    add_node(INF);
    root = 1;
    tot = 1;
    //Ϊ�˲�Ӱ��ͳ�� �����Ǽ�����INF���� ����size=0
    treap[root].size = 0;
    int op,val;
    for(int i=0;i<n;i++){
        op=read();
        val=read();
        if (op == 1) {
            insert_node(root, val);
        } else if (op == 2) {
            delete_node(root, val);
        } else if (op == 3) {
            printf("%d\n", get_rnk(root, val));
        } else if (op == 4) {
            printf("%d\n", get_kth(root, val));
        } else if (op == 5) {
            printf("%d\n", get_pre(root, val));
        } else {
            printf("%d\n", get_scc(root, val));
        }

    }
    return 0;
}
