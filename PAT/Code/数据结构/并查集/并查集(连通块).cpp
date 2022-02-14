// 我的代码

#include <iostream>
using namespace std;
const int N = 1e5+10;

int n,p[N],cnt[N];

int find_root(int a){
    if(p[a] == a) {
        return a;
    }
    if(p[a]==0){
        // 还没有初始化
        p[a] = a;   //设置为根结点
        cnt[a]++;
        return a;
    }

    p[a] = find_root(p[a]);
    return p[a];
}

int main(){
    int m;
    cin >> n>>m;
    for(int i = 0;i<m;i++){
        char op[3];
        scanf("%s",op);
        if(op[0]=='C'){
            // 连通
            int a,b;
            scanf("%d %d",&a,&b);
             a = find_root(a);
             b = find_root(b);
             if(a!=b){
                 p[b] = a;
                 cnt[a] += cnt[b];
             }
        }else if(op[1] =='1'){
            // 查询两个数
            int a,b;
            scanf("%d %d",&a,&b);
            if(find_root(a) == find_root(b)){
                cout <<"Yes\n";
            }else{
                cout <<"No\n";
            }
        }else{
            // 查询一个数的连通数
            int b;
            scanf("%d",&b);
            cout << cnt[find_root(b)] <<endl;
        }
    }
}

// y总代码

#include <iostream>
using namespace std;

const int N = 1e5;
int p[N],cnt[N];
int find(int x){
    if(p[x]!=x){p[x] = find(p[x]);}
    return p[x];
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    
    for(int i =1 ;i<=n;i++){
        p[i]=i;cnt[i]++;
    }
    while(m--){
        char op[2];
        scanf("%s",op);
        if(op[0]=='C'){
            int a,b;
            scanf("%d%d",&a,&b);
            
            a=find(a),b=find(b);
            
            if(a!=b){
                p[find(a)] = find(b);
                cnt[b] += cnt[a];
            }
        }else if(op[1]=='1'){
            int a,b;
            scanf("%d%d",&a,&b);
            if(find(a)==find(b)) puts("Yes");
            else puts("No");
        }else{
            int a;
            scanf("%d",&a);
            printf("%d\n",cnt[find(a)]);
        }
    }
    return 0;
}
