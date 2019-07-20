#include<iostream>
#include<cstdio>
using namespace std;




int a[10000];
int res[10000];
int main(){
    int aa = 2,bb = 9;
    res[0] = 9;
    a[0] = 8;
    for(int i=0;i<50;i++){
        a[i+1] = a[i]*(bb+i)/(aa+i);
        res[i+1]=res[i]+a[i+1];
    }
    for(int i=0;i<51;i++)
        printf("%d %d\n",a[i],res[i]);
    return 0;
}