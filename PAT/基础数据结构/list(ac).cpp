#include <iostream>
using namespace std;

const int n = 1e6+10;
int e[n],ne[n];
int head = -1,idx= 0;

void add_to_head(int x){
    // 存放当前的值
    e[idx] = x;
    // 它的前一个元素是之前head的下标
    ne[idx] = head;
    head = idx++;
}

// 在下标为K的元素后插入一个x
void add(int k , int x){
    // 存下当前的值
    e[idx] = x;

    // 它的前一个元素时k
    ne[idx] = ne[k];

    ne[k] = idx++;
}

void remove( int k ){
    ne[k] = ne[ne[k]];
}

int main(){
    int m;
    cin>> m;

    while(m--){
        int k,x;

        char op;
        cin>>op;

        if(op == 'H'){
            cin>>x;
            add_to_head(x);
        }
        if(op == 'I'){
            cin>>k>>x;

            add(k-1,x);
        }
        if(op == 'D'){
            cin>>k;
            if(!k) head = ne[head];
            else remove(k-1);
        }
    }

    for(int i = head;i!=-1;i=ne[i]){
        printf("%d ",e[i]);
    }
    cout << endl;
    return 0;
}