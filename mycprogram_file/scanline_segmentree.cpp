//��ͬ����ͨ�߶���
//ÿ�θ�����ֵ���ϴ������ڵ� 
//����Ҫquery���� ��Ϊÿ�ζ��ǲ�ѯ�����߶�������Ϣ
//����ÿ��ֻ��Ҫ�鿴���ڵ����Ϣ 
#include<bits/stdc++.h>
using namespace std;
const int N = 111;
double x[N];
struct Edge{
    double l,r,h;
    int flag;
}e[N<<1];
bool cmp(Edge& a,Edge& b){
    return a.h<b.h;
}
struct Node{//ʵ����tl tr���� ÿ�δ�0-k-1���ֿ��Եõ�lr
    int l,r;
    int s;
    double len;//������Ҫ��
}T[N<<3];//�߶����ռ䲻��ͨ���ᵼ��tle ������re
void build(int rt,int l,int r){
    T[rt].l = l;
    T[rt].r = r;
    T[rt].len = 0;
    T[rt].s = 0;
    if(l==r) return;
    int m = (l+r)>>1;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
}
void pushup(int rt){
    //ȥ��
    if(T[rt].s)
        T[rt].len = x[T[rt].r+1] - x[T[rt].l];
    else if(T[rt].l==T[rt].r)
        T[rt].len = 0;
    else
        T[rt].len = T[rt<<1].len + T[rt<<1|1].len;
}
void update(int id,int l,int r,int xx){
    if(T[id].l>=l&&T[id].r<=r){
        T[id].s += xx;
        pushup(id);//��ͬ����ͨ���������
        return;
    }
    int mid = (T[id].l+T[id].r)>>1;
    if(l<=mid) update(id<<1,l,r,xx);
    if(r>mid) update(id<<1|1,l,r,xx);
    pushup(id);
}
//���Բ�ҪEdge& a=kk,b=k;b���Զ�ʶ���һ�����

int main()
{
    int n;int kas = 0;
    while (scanf("%d",&n) == 1&&n)
    {
        int tot = 0;
        for (int i = 0;i < n;++i)
        {
            double x1,x2,y1,y2;
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);//����һ������
            Edge &t1 = e[tot];Edge &t2 = e[1+tot];
            t1.l = t2.l = x1,t1.r = t2.r = x2;
            t1.h = y1;t1.flag = 1;
            t2.h = y2;t2.flag = -1;
            x[tot] = x1;x[tot+1] = x2;
            tot += 2;
        }
        sort(e,e+tot,cmp);//�߰��߶ȴ�С�����������¶���ɨ�裩
        sort(x,x+tot);
        //��ɢ��������
        int k = 1;
        for (int i = 1;i < tot;++i)
        {
            if (x[i] != x[i-1]) //ȥ��
            {
                x[k++] = x[i];
            }
        }
        build(1,0,k-1);//��ɢ�����������[0��k-1]
        double ans = 0.0;
        for (int i = 0;i < tot;++i)
        {
            //��Ϊ�߶���ά�����Ǻ������ǵ��±꣬���Զ�ÿ��������������������Ӧ���±�
            int l = lower_bound(x,x+k,e[i].l) - x;//�ں������������ҵ������ߵ�λ��
            int r = lower_bound(x,x+k,e[i].r) - x - 1;//С��
            update(1,l,r,e[i].flag);//ÿɨ��һ���߾͸��º���ĸ���len 
            //�൱��ȫ����ѯ����
            ans += (e[i+1].h - e[i].h)*T[1].len;//q[1]����������,q[1].k=len�������������Ч����
            //�����������������������Ч���ȳ��������ߵĸ߶Ȳ���������������Ĳ��֣�
        }
        printf("Test case #%d\n",++kas);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}