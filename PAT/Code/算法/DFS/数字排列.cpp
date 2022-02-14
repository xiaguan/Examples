#include <iostream>
using namespace std;

int n;
const int N = 8;
int q[N];
/*
 * DFS也是递归，要设置递归终止条件
 */
void dfs(int x,int state){
    // 递归终止，输出结果
    if(x==n){
        for(int i = 0;i<n;i++) printf("%d ",q[i]);
        printf("\n");
        return ;
    }
    
    //用int的32位存储信息，state
    //深度就是第一个参数x
    for(int i = 0;i<n;i++){
        if(!(state >> i & 1)){
            q[x] = i+1;
            dfs(x+1,state + (1<<i));
        }
    }
}

int main(){
    cin >> n;

    dfs(0,0);
}