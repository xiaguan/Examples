#include <cstdio>
using namespace std;
const int N = 100;


// white表示未经访问的点 ，gray表示访问中的点，black表示访问结束的点
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

int n,M[N][N];
int color[N]{WHITE},d[N],f[N],tt;

void dfs_visit(int u){
    color[u] = GRAY;
    d[u] = ++tt;
    for(int v = 0;v<n;v++){
        //访问邻接矩阵
        if(M[u][v]==0) continue;
        if(color[v] == WHITE) {
            dfs_visit(v);
        }
    }
    color[u] = BLACK;
    f[u] = ++tt;
}


void dfs(){

    tt = 0;

    // 主要遍历函数是dfs_visit(u)
    for(int u = 0;u<n;u++){
        if(color [u] == WHITE) dfs_visit(u);
    }
    for(int u = 0;u<n;u++){
        printf("%d %d %d\n",u+1,d[u],f[u]);
    }
}

int main(){
    int u,v,k;

    // 数据的读取，和邻接矩阵的建立
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d %d",&u,&k);
        u--;
        for(int j = 0;j<k;j++){
            scanf("%d",&v);
            v--;
            M[u][v] =1;
        }
    }
    dfs();
}