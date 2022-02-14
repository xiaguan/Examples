#include <iostream>
using namespace std;

/*
 * 单源最短路径
 */

const int N = 100;
const int ER = (1<<24);
int n,M[N][N];
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

void dijkstra(){
    int minv;
    int d[N],color[N];

    for(int i = 0;i<n;i++){
        d[i] = ER;
        color[i] = WHITE;
    }

    d[0] = 0;
    color[0] = GRAY;
    
    // 这个算法和之前的最小生成树非常地相似，稍微改一下就可以了
    while(true){
        minv = ER;
        int u = -1;
        for(int i = 0;i<n;i++){
            if(minv > d[i] && color[i] != BLACK){
                minv = d[i];
                u = i;
            }
        }

        if(u==-1) break;
        color[u] = BLACK;
        for(int v = 0;v<n;v++){
            if(color[v] != BLACK && M[u][v] != ER)  //该点可以访问
            {
                // 主要区别在这里
                if(d[v] > d[u] + M[u][v]){
                    d[v] = d[u]+M[u][v];  // 更新最小距离
                    color[v] = GRAY;
                }
            }
        }
    }
    for(int i = 0;i<n;i++){
        cout <<i<<" "<<(d[i]==ER?-1:d[i]) <<endl;
    }
}

int main(){
    cin >> n;

    //初始化M
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
        M[i][j] = ER;
        }
    }

    int u,k,v,c;
    for(int i = 0;i<n;i++){
        cin >> u >>k;
        for(int j = 0;j<k;j++){
            cin >> v >> c;
            M[u][v] = c;
        }
    }

    dijkstra();
    return 0;
}