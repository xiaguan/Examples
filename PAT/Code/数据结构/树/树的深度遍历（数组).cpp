#include <cstdio>
#include <cstring>
#include <iostream>>
#include <algorithm>

using namespace std;

const int N = 100010,M = 2*N;

int n,ans = N;
int h[N],e[M],ne[M],idx = 0;
bool st[N];

void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

int dfs(int u ){
    st[u] = true;

    int size = 0,sum = 0;
    for(int i = h[u]; i != -1;i = ne[i]){
        int j = e[i];
        if(st[j]) continue;

        int s = dfs(j);
        size = max(size,s);
        sum += s;
    }

    size = max(size,n-sum-1);
    ans = min(ans,size);

    return sum+1;
 }

int main(){
    scanf("%d",&n);
    memset(h,-1,sizeof(h));
    for(int i = 0;i<n-1;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        add(a,b);
        add(b,a);
    }

    dfs(1);
    cout << ans << endl;
    return 0;
}