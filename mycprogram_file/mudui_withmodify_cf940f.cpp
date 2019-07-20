//cf940f Machine Learning 
//��������ɫ ͳ���������ڸ�Ԫ�س��ֵĴ�����������û���ֵ���С������
//�������ݱȽϴ�Χ ʹ����ɢ�� ����ӳ����ֵ ���Ҳ���Ҫ����ӳ�� 
//���͵Ĵ��޸�Ī���㷨 ���ӶȴﵽN*N^(5/3) ����1e5���Խ���
/*
�ܽ᣺ ������ɢ������Ϥ ���³��ֺܶ���� 
�ֿ���� ���ڿ�Ĵ�С�ĸ��� init���� sort(q+1,q+n+1)���� ����c����ɢ������ res�����������׳���
������ɢ����Ҫ ����n+c����Ŀ������������Ŀ ������Ҫ���������ռ� 2*N
*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e5+1000;
int n,m;
int cnt[N<<1],sum[N<<1],res[N<<1];//�ֱ����ڴ�� ���ֳ��ֵĴ��� ���ֶ�Ӧ�������ܺ� ���յĽ��
int B = 1;
int a[N<<1],temp[N<<1];//С�� temp cnt sum��Ҫ�������װ����
int queryn,changen,tempn;
struct Query{
    int id,l,r,t;
    //ע�������ж�
    bool operator <(const Query& o) const{
        return l/B==o.l/B?(r/B==o.r/B ? t<o.t:r<o.r):l<o.l;
    }
}q[N];
struct Change{
    int p,val;
}c[N];
void add(int x){//������ֵ
    sum[cnt[x]]--;
    cnt[x]++;
    sum[cnt[x]]++;
}
void sub(int x){
    sum[cnt[x]]--;
    cnt[x]--;
    sum[cnt[x]]++;
}
void chnum(int x,int tim){
    //�޸�ĳһ��������Ӧ����ֵ ������ǲ�ѯ����ı��
    if(q[x].l<=c[tim].p&&q[x].r>=c[tim].p){
        sub(a[c[tim].p]);
        add(c[tim].val);
    }
    //�����Ϳ����� ��һ�����ڵ����Ա�Ȼ���� �������Ա�֤��ȷ����
    swap(a[c[tim].p],c[tim].val);
}
void init(){
    memset(cnt,0,sizeof(cnt));
    memset(sum,0,sizeof(sum));
    memset(res,0,sizeof(res));
    queryn = changen = tempn= 0;
}
int main(){
    //��һ��wa�� ��Ϊ�� ��ɢ����Ҫ���ǵ�c����ֵ cδ�ػ���a�г��ֹ� ������ɢ����Ҫȫ��ͳ��
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        B = pow(n,0.66666);

        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]),temp[++tempn] = a[i];
        int opt,aa,bb;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&opt,&aa,&bb);
            if(opt==1){
                q[++queryn].l = aa;
                q[queryn].r = bb;
                q[queryn].id = queryn;//����֮�����ҵõ�ԭʼ��λ��
                q[queryn].t = changen;
            }else if(opt==2){
                c[++changen].p = aa;
                c[changen].val = bb;
                temp[++tempn] = bb;
            }
        }
        sort(q+1,q+queryn+1);

        //������ɢ�� ���ڲ���Ҫԭʼ���� ����ֻ��Ҫ����һ����������򿽱�����Ϳ��� a����µ�id
        //memcpy(temp,a,sizeof(a));
        sort(temp+1,temp+tempn+1);
        ////unique�᷵�ص�һ��Ԫ�غ�����Ԫ�ص�ָ�� ������Ҫɾ����Ҫ���eraseʹ�� ɾ�������ʣ��Ԫ��
        tempn = unique(temp+1,temp+tempn+1)-temp;//����Ҫ��-1/+1
        for(int i=1;i<=n;i++)
            a[i] = lower_bound(temp+1,temp+tempn+1,a[i])-temp;
        //c�ر�С�� ��Ϊ������ֵ���ֶ���Ҫ��Ӧ��ɢ������ 
        for(int i=1;i<=changen;i++)
            c[i].val = lower_bound(temp+1,temp+tempn+1,c[i].val)-temp;//��ȥ��ʼ�±������� ��Ϊ���ص���int*
        //�ز����� �ؼ�
        sort(q+1,q+queryn+1);
        int l=1,r=0,tt=0;
        //��ʽ����
        for(int i=1;i<=queryn;i++){
            while(l<q[i].l){
                sub(a[l++]);
            }
            while(l>q[i].l){
                add(a[--l]);
            }
            while(r>q[i].r){
                sub(a[r--]);
            }
            while(r<q[i].r){
                add(a[++r]);
            }
            //Ӧ��������仯  ��ȥӦ��ʱ��仯
            while(tt<q[i].t){
                chnum(i,++tt);
            }
            while(tt>q[i].t){
                chnum(i,tt--);
            }
            //��¼ÿһ��ѯ�ʵĽ�� ֻ��Ҫ����sum����
            int ans = 1;
            while(sum[ans]!=0){
                ans++;
            }
            res[q[i].id] = ans;
        }
        for(int i=1;i<=queryn;i++){
            printf("%d\n",res[i]);//����ֻ��Ҫres[i] ��Ϊ�Ѿ��Ǵ��������ȷ��˳��
        }

    }
    return 0;
}