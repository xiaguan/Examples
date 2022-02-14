#include <iostream>
#include <stack>
using namespace std;

/* 深度优先搜索：
*  1.将最初访问的顶点压入栈
*  2. 只要栈中仍有顶点，就循环进行以下操作
*    1. 访问栈顶元素（上一个访问的点）
*    2. 访问栈顶元素的下一个可以访问的点。如果不存在，则将栈顶元素弹出。重复循环。
*   另外开辟状态数组，来检测每个点的状态。
*/

const int N = 100;

// white表示未经访问的点 ，gray表示访问中的点，black表示访问结束的点
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

int n,M[N][N]{0};
int color[N]{WHITE},d[N],f[N],tt=0;
int nt[N]{0};

int next(int u){
    for(int v = nt[u];v<n;v++){
        nt[u] = v+1;
        if(M[u][v]) return v;
    }
    return -1;
}


void dfs_visit(int u){
    //创建栈，并把当前元素入栈
   stack<int> s;
   s.push(u);

   //标记为访问中
   color[u] = GRAY;
   d[u] = ++tt;

   while(!s.empty()){
       
       //变量的命名很重要，要学会如何命名变量，我这样命名效果就很差，有一个写名称的Bug,就Debug了很长时间
       
       int idx = s.top();  // 取出栈顶元素
       int v = next(idx);  // 下一个可以访问的点，我感觉这里不用写成函数。。。
       if(v!=-1){
           // v == -1 是没有可以访问点的标志
           if(color[v] == WHITE){ //如果v可以访问
               color[v] = GRAY;
               d[v] = ++tt;
               s.push(v);   // 入栈
           }
       }else {
           s.pop();
           color[idx] = BLACK;
           f[idx] = ++tt;
       }
   }
}

void dfs(){
    tt = 0;
     for(int i = 0;i<n;i++){
         if(color[i] == WHITE) dfs_visit(i);
     }

     for(int i = 0;i<n;i++){
         cout <<i+1 <<" "<<d[i]<<" "<<f[i]<<'\n';
     }
}


int main(){
    cin>>n;
    int u,k,v;
    for(int i = 0;i<n;i++){
        cin >> u >> k;u--;
        for(int j = 0;j<k;j++){
            cin >> v;
            v--;
            M[u][v] = 1;
        }
    }
    dfs();
}