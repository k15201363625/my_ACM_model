//bzoj 2648 ��С�����پ��� kdtreeģ����
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int DN = 2;
const int inf = 1e9+7;
const int N = 5e5+1;
//assist variables

int n,q;//����n��ǰ�ڵ�
//��ѯ����
int cur[DN];//ר���ڲ�ѯ Ҳ�ɽ���qp ���浱ǰ��ѯ�Ľڵ�
int disn;//disn���浱ǰ�������
//����������
bool curd;//curd ���������� ȥ����ǰѡ���ά��
int root;

struct Node{
    //bool dim; ��ʼ��0��ʼ ���Ժ��治��Ҫ��¼ �����Ƶ����� ����һ��ȫ�ֱ�����ʾ��ǰ���ʵ�ά��
    int maxn[DN],minn[DN],val[DN];
    int ch[2];
    void init(){
        for(int i=0;i<DN;i++){
            maxn[i] = minn[i] = val[i];
        }
    }
    int dis(int cur[DN]){
        //�����뵱ǰ�ڵ�������ķ�Χ������С���ܲ��    
        int res = 0;
        for(int i=0;i<DN;i++){
            res+=max(0,cur[i]-maxn[i]);
            res+=max(0,minn[i]-cur[i]);
        }
        return res;
    }
}KDTree[N<<1];//2�ռ䣿��
//assist function
int abs(int&x){//���ʹ��const��ᵼ�¸��ǲ���� �����޷���ʶ
    return x>0?x:(-x);
}

int distance(int a[DN],int b[DN]){
    int dis = 0;
    for(int i=0;i<DN;i++){
        dis+=abs(a[i]-b[i]);
    }
    return dis;
}

//Ϊ��ѡȡ���ֵ�--ʹ�õ�ǰά����λ�� ��Ҫʹ��nth���� �Լ�sort����
bool operator<(Node x,Node y){
    return x.val[curd]!=y.val[curd] ? x.val[curd]<y.val[curd]:x.val[curd^1]<y.val[curd^1];
}
void updatenode(int rt){
    //ʼ�ձ�֤�����������Χ ͭ������������Լ����������Χ---������ɨ�� ֻ��Ҫ�ݹ�����и��¼���ʵ��
    for(int i=0;i<2;i++){
        if(KDTree[rt].ch[i])
            for(int j=0;j<DN;j++){
                KDTree[rt].maxn[i] = max(KDTree[rt].maxn[i],KDTree[KDTree[rt].ch[i]].maxn[i]);
                KDTree[rt].minn[i] = min(KDTree[rt].minn[i],KDTree[KDTree[rt].ch[i]].minn[i]);
            }
    }
}
//�������÷��� �Ӷ���֤�ܹ��õ��¸��ڵ���Ϊ����
int buildtree(int l=1,int r=n,bool dim=0){
    //��dimά�ȿ�ʼ����
    //�޸ĵ�ǰά�� �Ӷ���ʹ��nth�е���sort �ܹ��õ���ȷ��ά�� �����޷���ȷ����ά�� 
    //��stl���õ��㷨 ��Ҫ����һЩ������Ϣ ��������� 1 ȫ�ֱ�����Ϊ��Ϣ�ṩ 2 ���ڲ��ٱ���һ����Ϣ
    curd = dim;
    int mid = (l+r)>>1;
    //ѡ���м�ڵ� ͬ����ߵĶ���С�� �ұߵĶ��Ǵ�� ���п������������ �ڲ�ʵ�֣���
    nth_element(KDTree+1,KDTree+mid,KDTree+n);
    KDTree[mid].init();
    if(l!=mid)
        KDTree[mid].ch[0] = buildtree(l,mid-1,dim^1);
    if(mid!=r)
        KDTree[mid].ch[1] = buildtree(mid+1,r,dim^1);
    updatenode(mid);
    return mid;
}
//ֱ���Զ����²�ѯ ���ҽ������ʻ����� ���ҽ��м�֦
int query(int rt=root){
    //ÿ�θ�����Ҫ����disn 
    disn = min(disn,distance(KDTree[rt].val,cur));
    //�鿴�ӽڵ���� �����Ƿ���ת
    int dchild[2] = {0,0};
    for(int i=0;i<2;i++){
        if(KDTree[rt].ch[i])
            dchild[i] = KDTree[KDTree[rt].ch[i]].dis(cur);
        else
            dchild[i] = inf;        
    }
    bool prior = dchild[0] <= dchild[1];
    //�Ȳ�ѯС�� �Ӷ�����ʽ���� �����Զ���֦
    if(dchild[prior^1]<=disn)
        query(KDTree[rt].ch[prior^1]);
    if(dchild[prior]<=disn)
        query(KDTree[rt].ch[prior]);
    //��ʵ����Ҫ���� disn���ǽ�� ����Ϊ�˷��㷵��
    return disn;

}
//����ڵ�--��Ҫ����Ĭ�ϲ�����Ҫȫ������Ĭ�ϲ���
void insert(int rt=root,bool dim=0){//��ǰ�ڵ���n
    //��������Ϳ��Բ���Ҫ�ݹ��޸ĸ��ڵ� ���ǵݹ���뻹����Ҫ��
    //ͨ�����װ���Ҫ�жϵ�ǰ�ڵ���Ŀ ʹ������������ƽ�ؽ�
    bool judge = KDTree[n].val[dim]<KDTree[rt].val[dim];
    if(KDTree[rt].ch[judge^1])
        insert(KDTree[rt].ch[judge^1],dim^1);
    else
        KDTree[rt].ch[judge^1] = n;//nά����ǰ���µĽڵ�
    //���������Ҫ���½ڵ���Ϣ
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
            disn = inf;//ÿ�ζ���Ҫ��ʼ��
            query();
            printf("%d\n",disn);
        }
    }

    return 0;
}