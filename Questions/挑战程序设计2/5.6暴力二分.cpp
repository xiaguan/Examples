#include <iostream>
using namespace std;
const int MAX = 1e5;

int n,k;
long long T[MAX];

int check(const long long& p){
    int i = 0;
    for(int j =0;j<k;j++){
        long long s = 0;
        while(s+T[i]<=p){
            s += T[i];
            i++;
            if(i==n) return n;
        }
    }
    return i;
}

long long solve(){
    long long left = 0;
    long long right = 1e10;
    long long mid=right;
    while(left<right){
        int v = check(mid);
        if(v>=n) right = mid;
        else left = mid+1;
        mid = left/long(2)+right/(long)2;
    }
    return right;
}

int main(){
    cin>>n>>k;
    for(int i = 0;i<n;i++) cin>>T[i];
    long long ans = solve();
    cout << ans <<endl;
    return 0;
}