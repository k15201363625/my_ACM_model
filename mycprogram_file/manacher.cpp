//learn by qsc
//manacher -- hdu 3068
//ע��� max idʲôʱ����� ��β�ַ�������� ������Ҫ����p[p]-1������ȷ��
//�������̿���ʹ��һ��㼼��
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
    str[2*len1+2] = '$';//ǧ��Ҫ��*һ�� ����ͣ������ һֱƥ�� λ�ÿռ���Է���
    for(int i=0;i<len1;i++){
        str[2*i+2] = s[i];
        str[2*i+3] = '#';
    }
    len2 = len1*2+2;
}
void manacher(){
    int id = 0;
    int imax = 0;//��Ҫ���ǳ�ʼ��
    for(int i=1;i<=2*len1+1;i++){
        if(i<imax){
            p[i] = min(p[2*id-i],imax-i+1);
        }else{
            p[i] = 1;
        }
        //ѭ������ **
        for(;str[i-p[i]]==str[i+p[i]];p[i]++);
        //���ø�������
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
