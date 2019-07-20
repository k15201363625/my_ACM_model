//bzoj 2648 最小曼哈顿距离 kdtree模板题
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int DN = 2;
const int inf = 1e9+7;
const int N = 5e5+1;
//assist variables

int n,q;//决定n当前节点
//查询辅助
int cur[DN];//专用于查询 也可叫做qp 保存当前查询的节点
int disn;//disn保存当前最近距离
//排序建树辅助
bool curd;//curd 辅助排序函数 去定当前选择的维度
int root;

struct Node{
    //bool dim; 开始从0开始 所以后面不需要记录 都能推到出来 保存一个全局变量表示当前访问的维度
    int maxn[DN],minn[DN],val[DN];
    int ch[2];
    void init(){
        for(int i=0;i<DN;i++){
            maxn[i] = minn[i] = val[i];
        }
    }
    int dis(int cur[DN]){
        //计算与当前节点所代表的范围距离最小可能差距    
        int res = 0;
        for(int i=0;i<DN;i++){
            res+=max(0,cur[i]-maxn[i]);
            res+=max(0,minn[i]-cur[i]);
        }
        return res;
    }
}KDTree[N<<1];//2空间？？
//assist function
int abs(int&x){//如果使用const则会导致覆盖不清楚 调用无法辨识
    return x>0?x:(-x);
}

int distance(int a[DN],int b[DN]){
    int dis = 0;
    for(int i=0;i<DN;i++){
        dis+=abs(a[i]-b[i]);
    }
    return dis;
}

//为了选取划分点--使用当前维度中位数 需要使用nth函数 以及sort规则
bool operator<(Node x,Node y){
    return x.val[curd]!=y.val[curd] ? x.val[curd]<y.val[curd]:x.val[curd^1]<y.val[curd^1];
}
void updatenode(int rt){
    //始终保证掌握最大区域范围 铜锅子区间更新自己的最大区域范围---而不是扫描 只需要递归过程中更新即可实现
    for(int i=0;i<2;i++){
        if(KDTree[rt].ch[i])
            for(int j=0;j<DN;j++){
                KDTree[rt].maxn[i] = max(KDTree[rt].maxn[i],KDTree[KDTree[rt].ch[i]].maxn[i]);
                KDTree[rt].minn[i] = min(KDTree[rt].minn[i],KDTree[KDTree[rt].ch[i]].minn[i]);
            }
    }
}
//必须设置返回 从而保证能够得到新根节点作为儿子
int buildtree(int l=1,int r=n,bool dim=0){
    //从dim维度开始划分
    //修改当前维度 从而在使用nth中调用sort 能够拿到正确的维度 否则无法正确调用维度 
    //当stl内置的算法 需要以来一些其他信息 ：解决方案 1 全局变量作为信息提供 2 类内部再保存一个信息
    curd = dim;
    int mid = (l+r)>>1;
    //选出中间节点 同事左边的都是小的 右边的都是大的 具有快速排序的性质 内部实现？？
    nth_element(KDTree+1,KDTree+mid,KDTree+n);
    KDTree[mid].init();
    if(l!=mid)
        KDTree[mid].ch[0] = buildtree(l,mid-1,dim^1);
    if(mid!=r)
        KDTree[mid].ch[1] = buildtree(mid+1,r,dim^1);
    updatenode(mid);
    return mid;
}
//直接自顶向下查询 并且进行有鲜花搜索 并且进行剪枝
int query(int rt=root){
    //每次更新想要求解的disn 
    disn = min(disn,distance(KDTree[rt].val,cur));
    //查看子节点情况 决定是否跳转
    int dchild[2] = {0,0};
    for(int i=0;i<2;i++){
        if(KDTree[rt].ch[i])
            dchild[i] = KDTree[KDTree[rt].ch[i]].dis(cur);
        else
            dchild[i] = inf;        
    }
    bool prior = dchild[0] <= dchild[1];
    //先查询小的 从而启发式搜索 并且自动剪枝
    if(dchild[prior^1]<=disn)
        query(KDTree[rt].ch[prior^1]);
    if(dchild[prior]<=disn)
        query(KDTree[rt].ch[prior]);
    //其实不需要返回 disn就是结果 但是为了方便返回
    return disn;

}
//插入节点--想要试用默认参数需要全部都是默认参数
void insert(int rt=root,bool dim=0){//当前节点是n
    //单纯插入就可以不需要递归修改根节点 但是递归插入还是需要的
    //通常进阶版需要判断当前节点数目 使用替罪羊树拍平重建
    bool judge = KDTree[n].val[dim]<KDTree[rt].val[dim];
    if(KDTree[rt].ch[judge^1])
        insert(KDTree[rt].ch[judge^1],dim^1);
    else
        KDTree[rt].ch[judge^1] = n;//n维护当前最新的节点
    //插入完成需要更新节点信息
    updatenode(rt);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&KDTree[i].val[0],&KDTree[i].val[1]);
    }
    buildtree();
    int opt;
    for(int i=1;i<=q;i++){
        scanf("%d",&opt);
        if(opt==1){
            n++;
            scanf("%d%d",&KDTree[n].val[0],&KDTree[n].val[1]);
            KDTree[n].init();
            insert(root,0);
        }else if(opt==2){
            scanf("%d%d",&cur[0],&cur[1]);
            disn = inf;//每次都需要初始化
            query();
            printf("%d\n",disn);
        }
    }

    return 0;
}