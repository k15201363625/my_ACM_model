//scoi2005 �������� 
//ͨ��dfs ���Ϸֿ� ��֤ÿһ��Ĵ�С��B-3B ֮��
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1010;
//˫��ߴ洢 �ռ䲻��2n��w��3����
int stk[N<<1];
int head[N],nxt[N<<1],to[N<<1];
int tot,top;//tot��¼��ǰ���ֵ�ʡ������ top��¼��ǰջ��
int belong[N];
int center[N];
int B=1;
int mm;
//��dfs�н��зֿ� 
//�������һ������֮��ֻҪջ��Ԫ�ش���B�ͳ�ջ ��Ϊһ������   ��ǰ�ڵ�dfs��������stack  ���dfs����ʣ���Ԫ�ؼ������һ������ ���屣֤[B-3B)
void dfs(int u,int fa){//��¼���ڵ� �����ҵ�center
    int t = top;
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];//�õ���ǰָ��
        if(v==fa)
            continue;
        dfs(v,u);
        //�������һ������ ��Ҫ�жϵ�ǰջ ���ܱ�֤����Ҫ�� ���Ӷ�֤������������С����
        if(top-t>=B){
            tot++;
            // cout<<"now tot"<<tot<<endl;
            while(top!=t){
                belong[stk[top--]]=tot;
                // cout<<stk[top+1]<<" "<<belong[stk[top+1]]<<endl;
            }
            center[tot] = u;
            // cout<<"now u"<<u<<endl;
        }
    }
    //�������̽��� �����ѱ����ڵ�����ջ
    stk[++top] = u;//ջ��1��ʼ�洢
}
//��β����
void solve(){
    dfs(1,0);
    // printf("------------%d %d------------\n",top,stk[top]);
    while(top>=1){
        belong[stk[top--]] = tot;
    }
}
//�ӱ� ʹ�ô�ͼ����ӱ���ʽ�洢 Ҳ����ʹ����������ֵܷ�ʽ�洢
//С����ĿҪ����˫���
void add_edge(int a,int b){
    nxt[++mm] = head[a];//��1��ʼ�洢
    head[a] = mm;
    to[mm] = b;
}


int main(){
    int n;
    int a,b;
    scanf("%d%d",&n,&B);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b);
        add_edge(b,a);
    }
    // for(int i=1;i<=n;i++){
    //     printf("%d-",head[i]);
    // }
    // cout<<"-------------------------------"<<endl;
    // cout<<mm<<endl;
    // for(int i=1;i<=mm;i++){
    //     printf("=%d %d=",nxt[i],to[i]);
    // }
    // cout<<"-------------------------------"<<endl;

    solve();
    printf("%d\n",tot);
    //����ɵ��
    for(int i=1;i<n;i++){
        printf("%d ",belong[i]);
    }
    printf("%d\n",belong[n]);

    for(int i=1;i<tot;i++){
        printf("%d ",center[i]);
    }
    printf("%d\n",center[tot]);
    return 0;
}