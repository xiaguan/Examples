
// 分两个版本，一个是我看完视频写的，另外一份是y总的代码


//我的

#include <iostream>
using namespace std;

int n,m;

const int N = 1e5+10;
int p[N];   // 父结点

// 递归实现
int find_root(int a){
    if(p[a] == a) return a;
    if(p[a]==0){
        // 还没有初始化
        p[a] = a;   //设置为根结点
        return a;
    }

    p[a] = find_root(p[a]);
    return p[a];
}
int main(){
    cin >> n >> m;   // 有n个数，m个操作;
    for(int i = 0;i<m;i++){
        char op[2];
        int a, b;
        scanf("%s %d %d",op,&a,&b);
        if(op[0] == 'M'){
            // 合并操作
            p[find_root(b)] = find_root(a);
        }else {
            // 查询操作
            if(find_root(a) == find_root(b)){
                cout <<"Yes\n";
            }else{
                cout <<"No\n";
            }
        }
    }
    return 0;
}

// y总的

#include <iostream>

using namespace std;

const int N = 100010;

int p[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    //提前设置根结点
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    while (m -- )
    {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'M') p[find(a)] = find(b);
        else
        {
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
