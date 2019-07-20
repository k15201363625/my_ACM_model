// 什么是巴什博弈：只有一堆n个物品，两个人轮流从这堆物品中取物， 规定每次至
// 少取一个，最多取m个。最后取光者得胜。
/*
巴什博奕
只有一堆n个物品，两个人轮流从中取物，规定每次最少取一个，最多取m个，最后取光者为胜 
若 n%(m+1)==0 后手必胜 
否则先手必胜，若n>m，第一次取n%(m+1)个，若n<=m，则第一次可取n~m间任意个
*/
/*
威佐夫博弈
有两堆各若干的物品，两人轮流从其中一堆取至少一件物品，至多不限，或从两堆中同时取相同件物品，规定最后取完者胜利。
*/
#include<bits/stdc++.h>
using namespace std;
bool weizuofu(int n1,int n2){
    if(n1>n2)
        swap(n1,n2);
    int temp = floor((n2-n1)*(1+sqrt(5.0))/2.0);
    if(temp == n1) return true;//后手
    else return false;
}
// 尼姆博弈：
// 有任意堆物品，每堆物品的个数是任意的，双方轮流从中取物品，每一次只能从一堆物品中取部分或全部物品，最少取一件，取到最后一件物品的人获胜。 
// 结论：把每堆物品数全部异或起来，如果得到的值为0，那么先手必败，否则先手必胜。
void nim(int n){
      int temp=0,ans;
      for(int i=0;i<n;i++){
          cin>>ans;
          temp^=ans;
      }
      if(temp==0)  cout<<"后手必胜"<<endl;
      else cout<<"先手必胜"<<endl;
}
/*
斐波那契博弈：
有一堆物品，两人轮流取物品，先手最少取一个，至多无上限，但不能把物品取完，之后每次取的物品数不能超过上一次取的物品数的二倍且至少为一件，取走最后一件物品的人获胜。 
结论： 先手胜当且仅当n不是斐波那契数（n为物品总数）
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
公平组合博弈：
（1）两人参与。 
（2）游戏局面的状态集合是有限。 
（3）对于同一个局面，两个游戏者的可操作集合完全相同 
（4）游戏者轮流进行游戏。 
（5）当无法进行操作时游戏结束，此时不能进行操作的一方算输。 
（6）无论游戏如何进行，总可以在有限步数之内结束。

SG函数：
g(x)=mex{g(y)|y是x的后继} 
mex：对集合运算，表示不属于该集合的最小非负整数，如mex{0,1,2,3}=4,mex{2,3,5}=0 
SG定理：g(G)=g(G1)⊕g(G2)⊕g(G3)…… 一个游戏的SG值为其子游戏SG值的异或和 
结论：g(G)=0时，先手必输，反之，先手必胜

解题模型： 
1.把原游戏分解成多个独立的子游戏，则原游戏的SG函数值是它的所有子游戏的SG函数值的异或。 
即sg(G)=sg(G1)^sg(G2)^…^sg(Gn)。 
2.分别考虑没一个子游戏，计算其SG值。 
SG值的计算方法：（重点） 
1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1); 
2.可选步数为任意步，SG(x) = x; 
3.可选步数为一系列不连续的数，用模板计算。
*/
//打表
const int N=10005;
int f[N],SG[N],S[N];                 //N要足够大，包含所有情况
void  getSG(int n,int m)        //n表示所求SG长度，m表示f数组长度
{
    int i,j;
    sort(f,f+m);
    memset(SG,0,sizeof(SG));
    //因为SG[0]始终等于0，所以i从1开始
    for(i = 1; i <= n; i++)
    {
        //每一次都要将上一状态 的 后继集合 重置
        memset(S,0,sizeof(S));
        for(j = 0; f[j] <= i && j<m; j++)
            S[SG[i-f[j]]] = 1;  //将后继状态的SG函数值进行标记
        for(j = 0;; j++) if(!S[j])
        {   //查询当前后继状态SG值中最小的非零值
            SG[i] = j;
            break;
        }
    }
}
//搜索
const int N=10000;
vector<int>e[N];         //邻接表

int sg[N];                       //sg全部初始化为-1
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
            return sg[x]=i;            //记忆化搜索
    }
}