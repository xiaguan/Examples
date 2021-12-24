///
#include <iostream>
#include <stdio.h>
using namespace std;
const int N= 1e4+10;
int cnt[N],n;
int main(){
    scanf("%d",&n);
    int maxn = 0,num;
    for(int i= 1;i<=n;i++) {
        scanf("%d",&num);
        maxn = max(num, maxn);
        cnt[num]++;
    }
    int idx = -1;
    while(cnt[++idx]==0);
    printf("%d",idx);
    cnt[idx]--;
    while(idx<=maxn){
        while(cnt[idx]--) printf(" %d",idx);
        idx++;
    }
    puts("");
    return 0;
}

///
#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 1e4+10,M = 2e6+10;
int n;
int q[M],cnt[N],result[M];
int main(){
    scanf("%d",&n);
    int maxn = 0;
    for(int i= 1;i<=n;i++){
        scanf("%d",&q[i]);
        maxn = max(q[i],maxn);
        cnt[q[i]]++;
    }
    for(int i = 1;i<=maxn;i++){
        cnt[i] = cnt[i] + cnt[i-1];
    }
    for(int i = 1;i<=n;i++){
        result[cnt[q[i]]] = q[i];
        cnt[q[i]]--;
    }
    for(int i = 1;i<n;i++){
        printf("%d ",result[i]);
    }
    printf("%d\n",result[n]);
}
