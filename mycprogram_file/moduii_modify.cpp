//����ɫ 
//�����޸ĵ�Ī���㷨 �־û�Ī���㷨 ģ��
//ͨ������һ��ʱ��ά�� ����r���зֿ� ����r��t��ϵ��ͬl��r��ϵ
//�ֿ��Сn^2/3 ʱ�临�Ӷ�n^5/3
//Ī�Ժ��� �㷨��������Ҫ�ֿ���� ����ʵ�ֵ�ʱ����ʵֻ��Ҫ�������ʱ����и������ƾͿ��� �����ĵط���������Ϳ���
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 5e4+10;
const int MAXN = 1e6+10;
int B = 1;//��Ĵ�С
int cnt[MAXN];
int ans[N];
int n,m;
int res=0;
char opt[3];//���ʹ���ַ� ��Ҫʹ��getchar�Ե�����Ļ��з��� �������ʹ�������ַ������Ա����������
int color[N];
int qcnt=0,ccnt=0;//��¼�޸���Ŀ ��ѯ��Ŀ
int l,r;
int now;//��¼��ǰʱ���
struct Change{
    int p,col;
}c[N];
struct Query{
    int l,r,t,id;
    bool operator<(const Query& o) const{
        return l/B==o.l/B?(r/B==o.r/B?t<o.t:r<o.r):l<o.l;
    }
}q[N];
void add(int x){
    if(cnt[x]++==0){
        res++;
    }
}

void del(int x){
    if(--cnt[x]==0){//С��
        res--;
    }
}
//�ؼ�����
void modify(int x,int tim){//x��ʾ��Ҫ�޸ĵĵ�ǰ������ tim��ʾʱ��--��ǰʱ�� Ҳ������Ҫ�޸ĵ�ʱ���
    if(c[tim].p>=q[x].l&&c[tim].p<=q[x].r){
        //�������ڲ� ������Ҫ�޸� ����Ҫ���´�
        del(color[c[tim].p]);
        add(c[tim].col);
    }
    //ͳһ�޸���Ϣ
    //���ڱ������� ��һ�����Ȼ�ǻ��˵���� �ٴο�ʼ���� һ��(n/b)^2����Ŀ ����Ϊ�˷������ ʹ��swap�޸� ����
    swap(color[c[tim].p],c[tim].col);//�ؼ����� �����ʵ��ǰ�� �ع�
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&color[i]);
    }
    B = pow(n,0.66666);

    for(int i=1;i<=m;i++){
        // scanf("%c",&opt);
        scanf("%s",&opt);
        if(opt[0]=='Q'){
            qcnt++;
            scanf("%d%d",&q[qcnt].l,&q[qcnt].r);
            q[qcnt].id=qcnt;
            q[qcnt].t = ccnt;
        }
        if(opt[0]=='R'){
            ccnt++;
            scanf("%d%d",&c[ccnt].p,&c[ccnt].col);
        }
    }
    l=1,r=0;//��ʵֻ��Ҫr<l�Ϳ����ڲ�ѯ��ʱ���Զ�r����/l�������㵱ǰ������ֵ ���Ǻ�����������С ���Ը�lr��ʼ��С����ֵ
    sort(q+1,q+qcnt+1);
    for(int i=1;i<=qcnt;i++){
        while(l<q[i].l){
            del(color[l++]);
        }
        while(l>q[i].l){
            add(color[--l]);
        }
        while(r>q[i].r){
            del(color[r--]);
        }
        while(r<q[i].r){
            add(color[++r]);
        }
        while(now<q[i].t){
            modify(i,++now);//С�Ĳ�Ҫ����now++
        }
        while(now>q[i].t){
            modify(i,now--);
        }
        ans[q[i].id] = res;
    }
    for(int i=1;i<=qcnt;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
