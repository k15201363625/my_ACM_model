#include<cstdio>
using namespace std;
const int MAXN = 1e5+7;
char res[11];
char * time;
int n;
int a[MAXN];
char* gettime(int x){
    int h = x/3600;
    int m = (x-h*3600)/60;
    int s = x-3600*h-60*m;
    if(h>24)
        h = h % 24;
    if(h<10)
        res[0] = '0';
    else
        res[0] = 48+(h/10);
    res[1] = 48 + (h%10);
    res[2] = ':';

    if(m<10)
        res[3] = '0';
    else
        res[3] = 48 + m/10;
    res[4] = 48 + m%10;
    res[5] = ':';

    if(s<10)
        res[6] = '0';
    else
        res[6] = 48+s/10;
    res[7] = 48 + s%10;
    res[8] = '\0';
    return res;
    
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        time = gettime(a[i]);
        printf("%s\n",time);
    }
    return 0;
}