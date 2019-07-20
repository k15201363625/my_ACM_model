/*
FHQ Treap 无旋treap
引用传递实现 更简单 方便树套树
split  merge关键
split可以按照value rnk进行 这里按照value进行
所以合并按照rnk进行 反之按照value进行
维护： value意义下的二叉搜索树 随机生成的rnk下的小根堆/大根堆
二叉搜索树索具有的基本性质都具有。并且查询第k大 前驱后继的能力都通过split merge实现
*/
//普通平衡树 模板题
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;
const int maxn = 1e6+7;
//读入挂
inline int read(){
    int res = 0;char c = getchar(); bool neg = 0;
    while(!isdigit(c)){
        neg |=(c=='-');//只要有- 永远是-
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
//按照val划分 划分成<=val >val 规则按照二叉树性质划分
inline void split(int r,int& a,int& b,int val){//r不能是引用
    //单独处理
    if(r==0){//不是处理r==1
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
//合并对象满足二叉树性质 并且一边大 一边小 为了满足两种性质 按照rnk规则合并合适
inline void merge(int& r,int a,int b){
    //单独处理
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


//树上二分
inline int get_kth(int rt,int k){//获得第k大的元素
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


//按照value划分就可以
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
    //插入根节点
    add_node(INF);
    root = 1;
    tot = 1;
    //为了不影响统计 即便是即便是INF数字 所以size=0
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
