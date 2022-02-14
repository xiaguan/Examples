#include <iostream>
#include <string>
using namespace std;

static const int N = 1001;

int c[N+1][N+1];

int lcs(const string& x,const string & y){
    int max_long = 0;

    // abcde
    // abddd
    int m = x.size();
    int n = y.size();

    for(int i = 0;i<=m;i++) c[i][0] = 0;
    for(int j =0;j<=n;j++) c[0][j] = 0;

    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            auto a= i+1,b = j+1;
            if(x[i] == y[j]){
                c[a][b] = c[a-1][b-1]+1;
            }else{
                c[a][b] = max(c[a-1][b],c[a][b-1]);
            }
            max_long = max(max_long,c[a][b]);
        }
    }
    return max_long;
}

int main(){
    int q;
    cin >> q;
    string a,b;
    for(int i = 0;i<q;i++)
    {
        cin >> a >> b;
        cout << lcs(a,b)<<"\n";
    }
    return 0;
}