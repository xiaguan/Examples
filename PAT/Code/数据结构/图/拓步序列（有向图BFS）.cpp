#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010,M = 2*N;
//图,不要忘记初始化
int h[N],e[N],ne[N],idx;
//队列,不要忘记初始化
int q[N],hh,tt;
//入度
int d[N];

int n,m;

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void topsort(){
    for(int i = 1;i<=n;i++){
        if(d[i]==0){
            q[++tt] = i;
        }
    }

    while(hh<=tt){
        int t = q[hh++];

        for(int i = h[t];i!=-1;i = ne[i]){
            int j = e[i];
            d[j]--;
            if(d[j]==0) q[++tt] = j;
        }
    }
}
int main(){
    //图初始化
    memset(h,-1,sizeof(h));
    //队列初始化
    hh = 0,tt=-1;
    cin >> n >> m;
    int a,b;
    for(int i= 0;i<m;i++){
        scanf("%d %d",&a,&b);
        add(a,b);
        d[b]++;
    }
    topsort();
    if(tt == n-1){
        for(int i = 0;i<n;i++){
            cout << q[i]<<" ";
        }
        cout <<endl;
    }else{
        cout <<"-1"<<endl;
    }
}