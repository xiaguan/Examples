#include <iostream>
#include <cstdio>
using namespace std;

struct Node{
    int p,l,r;
};

const int N = 25;
const int NIL = -1;
Node tree[N];
int n;

//前序遍历 根->左树->由树
void preoder(int idx){
    if(idx == NIL) return;
    printf(" %d",idx);
    preoder(tree[idx].l);
    preoder(tree[idx].r);
}

// 中序遍历 左树->根->右树
void inoder(int idx){
    if(idx == NIL) return ;
    inoder(tree[idx].l);
    printf(" %d",idx);
    inoder(tree[idx].r);
}

// 后序遍历 左树->右树->根
void postoder(int idx){
    if(idx == NIL) return ;
    postoder(tree[idx].l);
    postoder(tree[idx].r);
    printf(" %d",idx);
}

int main(){
    cin >> n;
    // 初始化
    for(int i = 0;i<n;i++){
        tree[i].p = tree[i].l = tree[i].r = NIL;
    }
    // 处理输入
    for(int i = 0 ;i<n;i++){
        int node  , l ,r;
        cin >> node >> l >> r;
        tree[node].l = l;
        tree[node].r = r;

        if(l != NIL) tree[l].p = l;
        if(r != NIL) tree[r].p = r;
    }

    // 寻找根节点
    int root;
    for(int i = 0;i<n;i++){
        if(tree[i].p ==NIL){
            root = i;
            break;
        }
    }
    printf("Preorder\n");
    preoder(root);
    printf("\n");
    printf("Inorder\n");
    inoder(root);
    printf("\n");
    printf("Postorder\n");
    postoder(root);
    printf("\n");
    return 0;
}