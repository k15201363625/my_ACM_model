//dp + ��˹��Ԫ
//learn from qsc
//cdoj 1330 ��ү��Զ�ŷ���
//******************���µ����д� ����long double��Ҫlf/Lf��� ����double����f/lf��� ������ȫ����
/*
�����޷�ͨ�����ԣ���
#include<bits/stdc++.h>
using namespace std;
const int maxn = 305;
const long double eps = 1e-14;
int n,m;
int f[maxn];
long double a[maxn][maxn];
int x,y;

//���� ����Ż�
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(int x){
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}

int main(){
    n = read();
    m = read();
    for(int i=1;i<=n;i++)
        f[i] = i;
    //����
    for(int i=1;i<=m;i++)
        f[read()] = read();
    cout<<"------------------------"<<endl;
    //��������
    for(int i=1;i<n;i++){
        a[i][i] = 6;
        if(f[i]!=i)//������
            a[i][f[i]]=-6;
        else{//û�д�����
            a[i][n+1]=6;
            printf("----%f\n",a[i][n+1]);
            for(int j=1;j<=6;j++){
                if(i+j<=n)
                    a[i][j+i]-=1.0;
                else
                    a[i][i]-=1.0;//Խ�� ��Ҫ�ı䷽��ϵ��
            }
            printf("----%f\n",a[i][n+1]);
        }
    }
    //���һ�е�������
    a[n][n] = 1.0;
    a[n][n+1] = 0;

    for(int i=1;i<=n;i++){
        printf("%d\n",a[i][n+1]);
    }
    cout<<"-------------------------"<<endl;
    //gaussian elimination processing o(n^3)
    for(int i=1;i<=n;i++){//����������Ԫ��
        int p = i;
        for(int j=i+1;j<=n;j++){
            if(fabs(a[j][i]>eps))
                p=j;//ʼ�ջ�ȡ�����
        }
        if(fabs(a[p][i])>eps){
            for(int j=i;j<=n+1;j++){
                //�û�Ԫ��
                swap(a[i][j],a[p][j]);
            }
            //��Ԫ
            for(int j=i+1;j<=n;j++){
                if(fabs(a[j][i]>eps)){
                    long double k = a[j][i]/a[i][i];
                    for(int z=i;z<=n+1;z++)
                        a[j][z]-=a[i][z]*k;
                }
            }
        }
    }
    //�Ѿ�����������Ǿ��� ���ڱ�ɶԽǾ�����Ҫ ֻ��Ҫ�ش����
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--){
            if(fabs(a[i][j]>eps))//����֪��δ֪
                a[i][n+1]-=a[i][j]*a[j][n+1];//���ڵ�n��û��Ӱ��
        }
        //�ر��ж�
        if(abs(a[i][i])<=eps&&abs(a[i][n+1]>eps)){
            printf("%d\n",-1);
            return 0;
        }
        a[i][n+1]/=a[i][i];//��һ�� ͬʱ��� ������Ҫ�ı� ��Ϊֻ��Ϊ�����
    }
    for(int i=1;i<=n;i++){
        printf("%f\n",a[i][n+1]);
    }
    cout<<"-------------------------"<<endl;
    printf("%.12lf\n",(double)a[1][n+1]);//long double ת�� ��ô���longdouble??
    return 0;
}
*/
