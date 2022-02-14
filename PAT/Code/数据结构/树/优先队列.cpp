#include <iostream>
using namespace std;
const int N = 1e5;
int q[N+1],cnt[N+1],hp[N+1];
int sz=0,k=0;

void heap_swap(int a,int b){
    swap(cnt[hp[a]],cnt[hp[b]]);
    swap(hp[a],hp[b]);
    swap(q[a],q[b]);
}

//小根堆模板
void down(int idx){
    int l = 2*idx;
    int r= 2*idx+1;
    int small;

    if(l<=sz && q[l]<q[idx]){
        small = l;
    }else small = idx;
    if(r<=sz && q[r] < q[small]){
        small = r;
    }

    if(small!=idx){
        heap_swap(idx,small);
        down(small);
    }
}

void up(int idx){
    while(idx/2 && q[idx/2] > q[idx]){
        heap_swap(idx,idx/2);
        idx /= 2;
    }
}

int main(){
    int n;
    cin >> n;
    for(int i = 0;i<n;i++){
        char op[3];

        scanf("%s",op);
        if(op[0]=='I'){
            // 插入
            sz++;k++;
            cin >> q[sz];
            cnt[k] = sz;
            hp[sz] = k;
            up(sz);
        }else if (op[0]=='P'){
            cout << q[1] <<endl;
        }else if(op[1]=='M'){
            // 删除最小值
            heap_swap(1,sz);
            sz--;
            down(1);
        }else if(op[0]=='D'){
            // 删除第k个插入的数
            int tk;
            cin >> tk;
            tk = cnt[tk];
            heap_swap(tk,sz);
            sz--;
            up(tk);
            down(tk);
        }else {
            // change
            int tk,x;
            cin >> tk >> x;
            tk = cnt[tk];
            q[tk] = x;
            up(tk);
            down(tk);
        }
    }
}