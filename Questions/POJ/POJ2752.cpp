#include <iostream>
#include <memory.h>
using namespace std;

const int N = 400010;
int ne[N],ans[N];
char p[N];

int strlens(char q[]){
    int result=1;
    while(q[result]!='\0'){
        result++;
    }
    return result-1;
}

int main(){
    while(~scanf("%s",(char*)(p+1))){
        memset(ne,0,sizeof(ne));
        int n = strlens(p);
        for (int i = 2, j = 0; i <= n; i ++ )
        {
            while (j && p[i] != p[j + 1]) j = ne[j];
            if (p[i] == p[j + 1]) j ++ ;
            ne[i] = j;
        }
        int i = n,L =400010-1 ;
        while(i){
            if(ne[i]) ans[L--] = ne[i];
            i = ne[i];
        }
        for(int i = L+1;i<=400010-1;i++) printf("%d ",ans[i]);
        printf("%d\n",n);
    }
}