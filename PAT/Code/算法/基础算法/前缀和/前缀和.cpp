// 简单来说就是 sn = sn-1+an
// 作用 ： 数组范围操作（这里也不太好说，自行体会一下）
// 注意: s0 = 0;

#include <iostream>
using namespace std;

const int N = 1e5+10;
int q[N];
int s[N];

int main(){
    int n,m;
    cin >>n>>m;
    for(int i = 0;i<n;i++){
        scanf("%d",&q[i]);
    }

    for(int i = 1;i<=n;i++){
        s[i] = s[i-1]+q[i-1];
    }

    int l,r;
    for(int i = 0;i<m;i++){
        scanf("%d %d",&l,&r);
        printf("%d\n",s[r]-s[l-1]);
    };
    return 0;
}
