// 差分是前缀和的逆运算
// 精华：bl+c/ br+1-c
// 后面有例题： acw 2041
// 打比赛，能不用vector就不要用

#include <iostream>
using namespace std;

const int N = 1e5+10;
int q[N],s[N];

int n,m;

void insert(int l, int r, int c){
    q[l] += c;
    q[r+1] -= c;
}

int main(){
    cin >> n >> m;
    for(int i = 1;i<=n;i++) {
        scanf("%d ",&s[i]);
        //这一步理解很久
        insert(i,i,s[i]);
    }

    int l,r,c;
    while(m--){
        scanf("%d%d%d",&l,&r,&c);
        insert(l,r,c);
    }
    for(int i = 1;i<=n;i++){
        q[i] += q[i-1];
        printf("%d ",q[i]);
    }
    return 0;
}

//例题

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n,m;
int q[1000003];

int main(){
    cin >> n>>m;
    int a,b;
    while(m--){
        scanf("%d %d",&a,&b);
        q[a]++;
        q[b+1]--;
    }
    for(int i = 1;i<=n;i++){
        q[i] += q[i-1];
    }

    // 第k个数
    nth_element(q + 1, q + n / 2 + 1, q + n + 1);
    cout << q[n/2+1] << endl;
    return 0;
}