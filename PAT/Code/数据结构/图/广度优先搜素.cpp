
#include <iostream>
#include <queue>
using namespace std;

/*
 * 广度优先搜索,依赖以下几个变量
 * color[n]   表示下标i的访问状态
 * M[n][n]     邻接矩阵
 * Queue      访问队列
 * d[n]        记录距离
 */

const int N = 100;
const int ER = (1<<21);

int n,M[N][N];
int d[N];

void bfs(int s){
    for(int i = 0;i<n;i++) d[i] = ER;
    queue<int> q;  //创建访问队列
    q.push(s);   //入队列
    d[s] = 0;
    int u;
    /*
     * 具体解析看书我觉得要好一点
     */
    while(!q.empty()){
        u= q.front();q.pop();  //取出栈顶，并弹出
        for(int v = 0;v<n;v++){
            if(M[u][v]==0) continue;
            if(d[v] != ER) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }

    for(int i = 0;i<n;i++){
        cout << i+1<<" "<<(d[i]==ER?-1:d[i])<<endl;
    }
}

int main(){
    cin>> n;
    int u,v,k;
    for(int i = 0;i<n;i++){
        cin >> u >> k;u--;
        for(int j = 0;j<k;j++){
            cin >> v;
            v--;
            M[u][v] = 1;
        }
    }
    bfs(0);
    return 0;
}
