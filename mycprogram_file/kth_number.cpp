//ѧϰ����̳�qsc
//kth number ����hdu 2665 poj2104
//��� �����ѯkСnum
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 1e5+7;
int a[maxn],root[maxn];
int n,m,cnt;
int x,y,k;
vector<int> v;
//���þ�̬�ṹ�洢
struct{
    int l,r;
    int size;
}T[maxn*32];//��ϯ�� ��1��ʼ
//��ɢ����������
int mygetid(int value){
    return lower_bound(v.begin(),v.end(),value) - v.begin() + 1;
}
void update(int l,int r,int&x,int y,int pos){//ע����������
    //����
    T[++cnt] = T[y];
    T[cnt].size++;
    x = cnt;
    if(l==r) return;
    int mid = (l+r)>>1;
    if(mid>=pos)
        update(l,mid,T[x].l,T[y].l,pos);
    else
        update(mid+1,r,T[x].r,T[y].r,pos);

}
int query(int l,int r,int x,int y,int k){
    //����
    if(l==r) return l;
    int mid = (l+r)>>1;
    if(k <= T[T[x].l].size - T[T[y].l].size)
        return query(l,mid,T[x].l,T[y].l,k);
    else
        return query(mid+1,r,T[x].r,T[y].r,k-T[T[x].l].size + T[T[y].l].size);


}
int main(){
    int times = 0;
    scanf("%d",&times);
    for(int i=0;i<times;i++){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            v.push_back(a[i]);
        }
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());//ȥ�ؼ�ɾ�� ʹ��getid��������������
        //for(int i=0;i<n;i++)
        //    printf("%d ",mygetid(a[i]));
        //����Ԫ��
        for(int i=0;i<n;i++){//�� ע���±� ������Ӧ����i+1�Ŷ� ��Ϊ��ѯ��Ĭ��1��Ϊ���
            update(1,n,root[i+1],root[i],mygetid(a[i]));
        }
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",v[query(1,n,root[y],root[x-1],k)-1]);
        }
        v.clear();//�ǵ����v
        cnt=0;//��ʼ�� ���
    }


    return 0;
}
