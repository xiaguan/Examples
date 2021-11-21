#include <iostream>
#include <cstring>
using namespace std;

const int N = 1E4+10,M = 1e6+10;
int ne[N];
char s[N],p[M];

int strlens(char q[]){
    int result=1;
    while(q[result]!='\0'){
        result++;
    }
    return result-1;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int result = 0;
        memset(ne,0,sizeof(ne));
        //memset(s,-1,sizeof(s));
        //memset(p,-1,sizeof(p));
        scanf("%s \n %s",(char*)(s+1),(char*)(p+1));
        int n = strlens(s),m=strlens(p);
        for (int i = 2, j = 0; i <= n; i ++ )
        {
            while (j && p[i] != p[j + 1]) j = ne[j];
            if (p[i] == p[j + 1]) j ++ ;
            ne[i] = j;
        }

        for (int i = 1, j = 0; i <= m; i ++ )
        {
            while (j && p[i] != s[j + 1]) j = ne[j];
            if (p[i] == s[j + 1]) j ++ ;
            if (j == n)
            {
                result++;
                j = ne[j];
            }
        }
        printf("%d\n",result);
    }
}