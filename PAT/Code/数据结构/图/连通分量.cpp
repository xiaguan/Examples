#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/* 邻接表的优点：只需与边数成正比的内存空间
 * 缺点：设一顶点u的相邻点数量为n，那么在调查顶点u与v的关系时，需要消耗o(n)来搜索。
 * 难以有效删除边
 */

const int MAX = 100000;
const int NIL = -1;

vector<vector<int>> ships(MAX);
int color[MAX];

/*
 *  求一个图的连通分量（Connected Components）的问题。对于一个连通性未知的图G，其极大连通子图即为G的连通分量
 *  本题之核心关键是：朋友关系是双向的，并且可以传递
 *  color[i]  所代表的值其实是，i所属的图的连通分量
 */

int n,m;


void dfs(int r,int c){
    stack<int> s;
    s.push(r);
    color[r] = c;
    while(!s.empty()){
        int u = s.top();s.pop();
        for(int& v : ships[u]){
            if(color[v] == NIL){
                color[v] = c;
                s.push(v);
            }
        }
    }
}


void assignColor(){
    int id = 1;
    for(int i = 0;i<n;i++){
        color[i] = NIL;
    }
    for(int u = 0;u<n;u++){
        if(color[u] == NIL) dfs(u,id++);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0 ;i<m;i++)
    {
        int l,r;
        cin >> l >> r;
        //输入朋友关系
        // 朋友关系时相互的，所以两边都要加（哎）
        ships[l].push_back(r);
        ships[r].push_back(l);
    }

    //处理颜色
    assignColor();

    int q;
    cin >> q;
    for(int i = 0;i<q;i++){
        int l,r;
        cin >> l >> r;
        if(color[l] == color[r]){
            cout <<"yes\n";
        }else{
            cout <<"no\n";
        }
    }
    return 0;
}