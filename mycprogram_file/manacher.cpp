//learn by qsc
//manacher -- hdu 3068
//注意点 max id什么时候更新 收尾字符必须填充 最终需要对于p[p]-1才是正确的
//暴力过程可以使用一点点技巧
//#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 3e5;
char s[maxn],str[maxn];
int p[maxn];
int len1,len2;
int ans;
void init(){
    str[0] = '*';
    str[1] = '#';
    str[2*len1+2] = '$';//千万不要与*一样 否则停不下啦 一直匹配 位置空间可以访问
    for(int i=0;i<len1;i++){
        str[2*i+2] = s[i];
        str[2*i+3] = '#';
    }
    len2 = len1*2+2;
}
void manacher(){
    int id = 0;
    int imax = 0;//不要忘记初始化
    for(int i=1;i<=2*len1+1;i++){
        if(i<imax){
            p[i] = min(p[2*id-i],imax-i+1);
        }else{
            p[i] = 1;
        }
        //循环外面 **
        for(;str[i-p[i]]==str[i+p[i]];p[i]++);
        //设置更新条件
        if(p[i]+ i - 1 > imax){
            id = i;
            imax = i + p[i] - 1;
        }

    }
}
int main(){
    while(scanf("%s",s)!=EOF){
        len1 = strlen(s);
        init();
        manacher();
        ans = 0;
        for(int i=1;i<=len1*2+1;i++)
            ans = max(ans,p[i]);
        printf("%d\n",ans-1);
    }
    return 0;
}
