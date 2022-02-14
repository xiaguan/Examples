#include <iostream>
using namespace std;

const int N = 100;

int n,p[N+1],m[N+1][N+1];

int main(){
    cin >> n;
    for(int i = 1;i<=n;i++){
        // 30 35 35 15
        // 30 25 15 (0,1) (1,2) 构成一个矩阵
        scanf("%d %d",&p[i-1],&p[i]);
    }

    //数组m用下标记录矩阵mi和举证mj相乘的最小成本
    for(int l = 2;l<=n;l++){
        for(int i = 1;i<=n-l+1;i++){
            int j = i+l-1;
            m[i][j] = (1<<21);
            for(int k = i;k<=j-1;k++){
                m[i][j] = min(m[i][j],m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]);
            }
        }
    }
    cout << m[1][n] <<endl;
}
