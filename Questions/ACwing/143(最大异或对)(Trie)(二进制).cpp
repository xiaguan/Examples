#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010, M = 3100010;

int n;
int a[N], son[M][2], idx;

void insert(int x){
    int p = 0;
    for(int i = 30;i>=0;i--){
        int &s = son[p][x >> i & 1];
        if(!s) s = ++idx;
        p = s;
    }
}

int query(int x){
    int p =0,res =0 ;
    for(int i = 30;i>=0;i--){
        int s = x >>i &1;
        if(son[p][!s]){
           res += 1 << i;
            p = son[p][!s];
        }else p = son[p][s];
    }
    return res;
}


int main(){
    int n;
    cin>>n;
    for(int i = 0;i<n;i++){
        scanf("%d",&a[i]);
        insert(a[i]);
    }

    int res= 0;
    for(int i = 0;i<n;i++) {res = max(res,query(a[i]));}

    cout << res;
}