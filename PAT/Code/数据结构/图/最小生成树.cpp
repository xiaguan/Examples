/*
 * 普里姆算法
 * 设图G=(V,E)所有顶点的集合为V，MST中顶点的集合为T
 * 1. 从G中选取任意顶点作为MST的根，将其添加至T。
 * 2. 循环执行下述处理直至T = V；
 * ---->在连接T内顶点与V-T内顶点的边中选取权值最小的边，将其作为MST的边，并将MST的边添加至T
 */

#include <iostream>
using namespace std;
const int MAX = 100;
const int ER = (1<<21);
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

int n,M[MAX][MAX];  // M是邻接矩阵

int prim(){
    int u,minv;

    // color记录状态，d记录最小权值，p[n]保存MST中顶点v的父节点
    int d[MAX],p[MAX],color[MAX];

    for(int i = 0 ;i<n;i++){
        d[i] = ER;   //权值设为最大
        p[i] = -1;   // 父节点设为-1，错误值
        color[i] = WHITE;   //状态设为就绪
    }

    d[0] = 0;

    //----------------------实现-----------------------------
    while(1){
        minv = ER;
        u = -1;    //当前值设为-1
        for(int i = 0;i<n;i++){
            //第一次循环进入，u = 0,minv = 0
            //寻找根
            if( minv > d[i] && color[i] != BLACK){
                u = i;
                minv = d[i];
            }
        }

        cout << u << endl;

        //结束标志
        if(u==-1) break;

        color[u] = BLACK;

        for(int v = 0;v<n;v++){
            //这个for循环就是选取最小的可以访问的边
            if(color[v] != BLACK && M[u][v] != ER){  //确保v可以访问，并且和u连通
                if(d[v] > M[u][v]){  //更新最小边
                    d[v] = M[u][v];
                    p[v] = u;  // 保存上一个结点，同时将该点加入到结果中
                   color[v] = GRAY;  //这个grey可以说是一点用没有,标准化？
                }
            }
        }
    }
    int sum = 0;
    for(int i = 0;i<n;i++){
        if(p[i] != -1) sum += M[i][p[i]];
    }
    return sum;
}


int my_prim(){
    int u,minv;
    int d[MAX],p[MAX];
    bool color[MAX];   //true表示没有访问过

    for(int i = 0;i<n;i++){
        d[i] = ER;
        p[i] = -1;
        color[i] = true;
    }

    d[0] = 0;
    while(true){
        minv = ER;
        u = -1;
        //第一步：寻找根
        for(int i = 0;i<n;i++){
            if(minv > d[i] && color[i]){
                u = i;
                minv = d[i];
            }
        }
        if(u==-1) break;

        color[u] = false;

        //更新最小边
        for(int v = 0;v<n;v++){
            if(color[v] && M[u][v] != ER){
                if(d[v] > M[u][v]){
                    d[v] = M[u][v];
                    p[v] = u;
                }
            }
        }
    }

    int sum  = 0;
    for(int i = 0;i<n;i++){
        if(p[i] != -1) sum += M[i][p[i]];
    }
    return sum;
}

int main(){
    cin >> n;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            int e;
            cin >> e;
            if(e==-1){
                M[i][j] = ER;
            }else M[i][j] = e;
        }
    }
    cout << my_prim() <<endl;
}

