//dp + 高斯消元
//learn from qsc
//cdoj 1330 柱爷与远古法阵
//******************以下调试有错 对于long double需要lf/Lf输出 对于double可以f/lf输出 否则完全不对
/*
程序无法通过测试？？
#include<bits/stdc++.h>
using namespace std;
const int maxn = 305;
const long double eps = 1e-14;
int n,m;
int f[maxn];
long double a[maxn][maxn];
int x,y;

//读入 输出优化
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
    //传送
    for(int i=1;i<=m;i++)
        f[read()] = read();
    cout<<"------------------------"<<endl;
    //建立矩阵
    for(int i=1;i<n;i++){
        a[i][i] = 6;
        if(f[i]!=i)//传送门
            a[i][f[i]]=-6;
        else{//没有传送门
            a[i][n+1]=6;
            printf("----%f\n",a[i][n+1]);
            for(int j=1;j<=6;j++){
                if(i+j<=n)
                    a[i][j+i]-=1.0;
                else
                    a[i][i]-=1.0;//越界 需要改变方程系数
            }
            printf("----%f\n",a[i][n+1]);
        }
    }
    //最后一行单独处理
    a[n][n] = 1.0;
    a[n][n+1] = 0;

    for(int i=1;i<=n;i++){
        printf("%d\n",a[i][n+1]);
    }
    cout<<"-------------------------"<<endl;
    //gaussian elimination processing o(n^3)
    for(int i=1;i<=n;i++){//考虑所有主元列
        int p = i;
        for(int j=i+1;j<=n;j++){
            if(fabs(a[j][i]>eps))
                p=j;//始终获取最后行
        }
        if(fabs(a[p][i])>eps){
            for(int j=i;j<=n+1;j++){
                //置换元素
                swap(a[i][j],a[p][j]);
            }
            //消元
            for(int j=i+1;j<=n;j++){
                if(fabs(a[j][i]>eps)){
                    long double k = a[j][i]/a[i][i];
                    for(int z=i;z<=n+1;z++)
                        a[j][z]-=a[i][z]*k;
                }
            }
        }
    }
    //已经变成了下三角矩阵 现在变成对角矩阵不需要 只需要回带求解
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--){
            if(fabs(a[i][j]>eps))//用已知求未知
                a[i][n+1]-=a[i][j]*a[j][n+1];//对于第n行没有影响
        }
        //特别判断
        if(abs(a[i][i])<=eps&&abs(a[i][n+1]>eps)){
            printf("%d\n",-1);
            return 0;
        }
        a[i][n+1]/=a[i][i];//归一化 同时求解 矩阵不需要改变 因为只是为了求解
    }
    for(int i=1;i<=n;i++){
        printf("%f\n",a[i][n+1]);
    }
    cout<<"-------------------------"<<endl;
    printf("%.12lf\n",(double)a[1][n+1]);//long double 转型 怎么输出longdouble??
    return 0;
}
*/
