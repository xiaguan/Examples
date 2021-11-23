#include <iostream>
using namespace std;

const int N = 10010;
int son[N][26],cnt[N],idx;
char message[N];

void insert(const char word[]){
    int p = 0;
    for (int i = 0; word[i]; i ++ )
    {
        int u = word[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++ ;
}

int query(const char word[]){
    int p = 0;
    for(int i = 0;word[i];i++){
        int u = word[i]-'a';
        if(!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main(){
    int n ;
    cin>>n;
    for(;n;n--){
        char c;
        scanf("%s %s",&c,message);
        cout<<"c is "<<c<<'#'<<message;
        if(c=='I') insert(message);
        if(c=='Q') printf("%d\n",query(message));
        cout<<"n is "<<n<<endl;
    }
    return 0;
}