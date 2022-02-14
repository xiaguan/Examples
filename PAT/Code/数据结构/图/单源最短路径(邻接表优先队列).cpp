#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX = 10000;
const int ER = (1<<22);
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

int n;

// 这是vector数组，而不是单个vector
vector<pair<int,int>> adj[MAX];  //pair的前一个是顶点，第二个是权值

void dijkstra(){
    //入读列的数值都是负数，这样才能取到最小值
    // 但其实在初始化队列的时候，使用less代替grater（没有实操过）
    // pair的比较规则：先比较第一个元素，第一个相等比较第二个。
    priority_queue<pair<int,int>> PQ;
    int color[MAX];  //状态数组
    int d[MAX];    //保存距离的数组

    //初始化
    for(int i = 0;i<n;i++){
        d[i] = ER;
        color[i] = WHITE;
    }

    // 设置0为起点
    d[0] = 0;
    PQ.push(make_pair(0,0));
    color[0] = GRAY;

    while(!PQ.empty()){
        auto f = PQ.top(); PQ.pop();   //这里的pair前一个是权值，后一个是顶点，这样写代码至少我读的时候被绕了
        // 后面想想也确实，第一个因该是权值，这样才符合优先队列
        int u = f.second;  // 取出d[u]最小的顶点

        color[u] = BLACK;   // 这题里面，color是没有用的

        // d[u]可能已经更新，而优先级队列中的d[u]可能还在停留
        // 更新意味着同一个顶点v,权值更小的那一对piar被处理过了，没必要再处理一遍
        if(d[u] < f.first * (-1)) continue;

        for(int j = 0;j<adj[u].size();j++){
            // 邻接表不用判断两个点是否连通的问题
            int v = adj[u][j].first;
            if(d[v] > d[u] + adj[u][j].second){
                d[v] = d[u] + adj[u][j].second;
                // priority_queue 默认优先比较较大值，因此要乘以-1
                PQ.push(make_pair(d[v]*(-1),v));
                color[v] = GRAY;
            }
        }
    }

    for(int i = 0;i<n;i++){
        cout <<i<<" "<<(d[i]==ER?-1:d[i]) <<endl;
    }
}

int main(){
    int k,u,v,c;
    cin >> n;
    for(int i = 0;i<n;i++){
        cin >> u >> k;
        for(int j = 0;j<k;j++){
            cin >> v >> c;
            //有时间要复习一下C++ primer上的emplace
            adj[u].emplace_back(v,c);
        }
    }
    dijkstra();
    return 0;
}