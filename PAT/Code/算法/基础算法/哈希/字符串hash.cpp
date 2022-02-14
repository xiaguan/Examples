// 记住hash值要用ull存储
#include <iostream>
#include <string>
using namespace std;

int n,m;
const int N = 1e5+10;
const int P = 131;
typedef unsigned long long NLL;
char str[N];
NLL h[N],p[N];

NLL get(int l,int r){
    NLL result = h[r] - h[l-1]*p[r-l+1];
    return result;
}

int main(){
    scanf("%d %d",&n,&m);
    scanf("%s",str+1);

    p[0] = 1;
    for(int i =1;i<=n;i++){
        h[i] = h[i-1]*P+str[i];
        p[i] = p[i-1]*P;
    }

    int l,r,a,b;
    while(m--){
        scanf("%d %d %d %d",&l,&r,&a,&b);
        if(get(l,r) == get(a,b)){
            puts("Yes");
        }else{
            puts("No");
        }
    }
    return 0;
}