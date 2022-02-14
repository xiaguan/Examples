#include <iostream>
#include <cstring>
using namespace std;

const int N = 10;

int n;
bool row[N],col[N],dg[N*2],udg[N*2];
char g[N][N];

void dfs(int line,int left){
    if(line >=n) return ;

    if(line == n-1 && left == 1){
        for(int i = 0;i<n;i++){
            //如果这个点可行
            if(!row[line] && !col[i] && !dg[line+i] && !udg[i-line+n]){
                row[line] = col[i] = dg[line+i] = udg[i-line+n] = true;
                g[line][i] = 'Q';
                for(int i = 0;i<n;i++) puts(g[i]);
                puts("");
                row[line] = col[i] = dg[line+i] = udg[i-line+n] = false;
                g[line][i] = '.';
            }
        }
        return ;
    }

    //遍历每一行的每一列
    for(int i = 0;i<n;i++){
        //如果这个点可行
        if(!row[line] && !col[i] && !dg[line+i] && !udg[i-line+n]){
            row[line] = col[i] = dg[line+i] = udg[i-line+n] = true;
            g[line][i] = 'Q';
            dfs(line+1,left-1);
            row[line] = col[i] = dg[line+i] = udg[i-line+n] = false;
            g[line][i] = '.';
        }
    }
}

int main(){
     cin >> n;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++) g[i][j] ='.';
    }
    dfs(0,n);
    return 0;
}