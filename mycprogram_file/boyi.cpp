// ʲô�ǰ�ʲ���ģ�ֻ��һ��n����Ʒ�������������������Ʒ��ȡ� �涨ÿ����
// ��ȡһ�������ȡm�������ȡ���ߵ�ʤ��
/*
��ʲ����
ֻ��һ��n����Ʒ����������������ȡ��涨ÿ������ȡһ�������ȡm�������ȡ����Ϊʤ 
�� n%(m+1)==0 ���ֱ�ʤ 
�������ֱ�ʤ����n>m����һ��ȡn%(m+1)������n<=m�����һ�ο�ȡn~m�������
*/
/*
��������
�����Ѹ����ɵ���Ʒ����������������һ��ȡ����һ����Ʒ�����಻�ޣ����������ͬʱȡ��ͬ����Ʒ���涨���ȡ����ʤ����
*/
#include<bits/stdc++.h>
using namespace std;
bool weizuofu(int n1,int n2){
    if(n1>n2)
        swap(n1,n2);
    int temp = floor((n2-n1)*(1+sqrt(5.0))/2.0);
    if(temp == n1) return true;//����
    else return false;
}
// ��ķ���ģ�
// ���������Ʒ��ÿ����Ʒ�ĸ���������ģ�˫����������ȡ��Ʒ��ÿһ��ֻ�ܴ�һ����Ʒ��ȡ���ֻ�ȫ����Ʒ������ȡһ����ȡ�����һ����Ʒ���˻�ʤ�� 
// ���ۣ���ÿ����Ʒ��ȫ���������������õ���ֵΪ0����ô���ֱذܣ��������ֱ�ʤ��
void nim(int n){
      int temp=0,ans;
      for(int i=0;i<n;i++){
          cin>>ans;
          temp^=ans;
      }
      if(temp==0)  cout<<"���ֱ�ʤ"<<endl;
      else cout<<"���ֱ�ʤ"<<endl;
}
/*
쳲��������ģ�
��һ����Ʒ����������ȡ��Ʒ����������ȡһ�������������ޣ������ܰ���Ʒȡ�֮꣬��ÿ��ȡ����Ʒ�����ܳ�����һ��ȡ����Ʒ���Ķ���������Ϊһ����ȡ�����һ����Ʒ���˻�ʤ�� 
���ۣ� ����ʤ���ҽ���n����쳲���������nΪ��Ʒ������
*/
const int N = 55;    
int f[N];   
void Init()  
{  
    f[0] = f[1] = 1;  
    for(int i=2;i<N;i++)  
        f[i] = f[i-1] + f[i-2];  
}    
int main()  
{  
    Init();  
    int n;  
    while(cin>>n)  
    {  
        if(n == 0) break;  
        bool flag = 0;  
        for(int i=0;i<N;i++)  
        {  
            if(f[i] == n)  
            {  
                flag = 1;  
                break;  
            }  
        }  
        if(flag) puts("Second win");  
        else     puts("First win");  
    }  
    return 0;  
}
/*
��ƽ��ϲ��ģ�
��1�����˲��롣 
��2����Ϸ�����״̬���������ޡ� 
��3������ͬһ�����棬������Ϸ�ߵĿɲ���������ȫ��ͬ 
��4����Ϸ������������Ϸ�� 
��5�����޷����в���ʱ��Ϸ��������ʱ���ܽ��в�����һ�����䡣 
��6��������Ϸ��ν��У��ܿ��������޲���֮�ڽ�����

SG������
g(x)=mex{g(y)|y��x�ĺ��} 
mex���Լ������㣬��ʾ�����ڸü��ϵ���С�Ǹ���������mex{0,1,2,3}=4,mex{2,3,5}=0 
SG������g(G)=g(G1)��g(G2)��g(G3)���� һ����Ϸ��SGֵΪ������ϷSGֵ������ 
���ۣ�g(G)=0ʱ�����ֱ��䣬��֮�����ֱ�ʤ

����ģ�ͣ� 
1.��ԭ��Ϸ�ֽ�ɶ������������Ϸ����ԭ��Ϸ��SG����ֵ��������������Ϸ��SG����ֵ����� 
��sg(G)=sg(G1)^sg(G2)^��^sg(Gn)�� 
2.�ֱ���ûһ������Ϸ��������SGֵ�� 
SGֵ�ļ��㷽�������ص㣩 
1.��ѡ����Ϊ1~m������������ֱ��ȡģ���ɣ�SG(x) = x % (m+1); 
2.��ѡ����Ϊ���ⲽ��SG(x) = x; 
3.��ѡ����Ϊһϵ�в�������������ģ����㡣
*/
//���
const int N=10005;
int f[N],SG[N],S[N];                 //NҪ�㹻�󣬰����������
void  getSG(int n,int m)        //n��ʾ����SG���ȣ�m��ʾf���鳤��
{
    int i,j;
    sort(f,f+m);
    memset(SG,0,sizeof(SG));
    //��ΪSG[0]ʼ�յ���0������i��1��ʼ
    for(i = 1; i <= n; i++)
    {
        //ÿһ�ζ�Ҫ����һ״̬ �� ��̼��� ����
        memset(S,0,sizeof(S));
        for(j = 0; f[j] <= i && j<m; j++)
            S[SG[i-f[j]]] = 1;  //�����״̬��SG����ֵ���б��
        for(j = 0;; j++) if(!S[j])
        {   //��ѯ��ǰ���״̬SGֵ����С�ķ���ֵ
            SG[i] = j;
            break;
        }
    }
}
//����
const int N=10000;
vector<int>e[N];         //�ڽӱ�

int sg[N];                       //sgȫ����ʼ��Ϊ-1
int getsg(int x)
{
    if(sg[x]!=-1)
        return sg[x];
    int mex[N];
    memset(mex,0,sizeof(mex));
    for(int i=0;i<e[x].size();i++)
        mex[getsg(e[x][i])]=1;
    for(int i=0;;i++)
    {
        if(!mex[i])
            return sg[x]=i;            //���仯����
    }
}