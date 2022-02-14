#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;


// 二叉搜索树满足以下条件：
// 首先，它是一棵二叉树
// 左子结点<=父节点，右子结点>=父节点


struct Node{
    int key;
    Node * parent,*left,*right;
    Node(int key):key(key){
        parent = left = right = nullptr;
    }
};
//左侧要比右侧小

Node *root,*NIL;  //设置根和不存在条件


// ----------------------------插入-------------------------------------------------------------
//插入键值为a的结点
void insert(int a){
    Node * z = new Node(a);
    Node * temp = root;
    Node * pre;   // 上一个，前一个

    while(temp!=NIL){
        pre = temp;
        if(a <= temp->key){
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }

    //此时的temp是a要插入到的位置
    //分情况，1.根结点，2.非根结点
    // 根结点
    if(!pre){
    //pre不存在，根结点
    root = z;return ;
    }

    //非根结点,柑橘pre->key和a的大小关系，进行子结点的分配
    if(a <= pre->key){
        pre->left = z;
        z->parent = pre;
    }else{
        pre->right = z;
        z->parent = pre;
    }
}

void preprint(Node * idx){
    if(idx == NIL) return;
    printf(" %d",idx->key);
    preprint(idx->left);
    preprint(idx->right);
}

void inprint(Node * idx){
    if(idx == NIL) return;
    inprint(idx->left);
    printf(" %d",idx->key);
    inprint(idx->right);
}

void print(){
    inprint(root);
    printf("\n");
    preprint(root);
    printf("\n");
}

// -------------------查找--------------------------
Node* find(int target){
    auto temp = root;
    while(temp != NIL && temp->key != target){
        if(target <= temp->key) temp = temp->left;
        else temp = temp->right;
    }
    return temp;
}

//找到最小值
Node * treeMinium(Node * x){
    while(x->left) x = x->left;
    return x;
}

Node * treeSuccessor(Node * x){
    //当从删除节点函数调用时，这个if是没有用的，因为传入的节点有两个子节点
    if(x->right) return treeMinium(x->right);  // 寻找右节点的左树最小值
    //如果是删除函数的话，这里已经结束

    Node * y = x->parent;    //y为x的上一个节点
    while(y && x==y->right){  //y存在并且x是y的右子节点
        x = y;
        y = y->parent;
    }
    return y;
}

// ---------------------删除-----------------------------
void tree_node_delete(Node* z){
    Node * y;   //要删除的对象
    Node * x;   // y的子节点

    //确定要删除的节点
    // 节点的删除分两种情况
    // 1.它只有一个或没有子节点，直接删除它本身就性
    // 2.它有两个子节点 ，让右树的最小值顶替它成为新的节点
    // 第二种情况选取右树的最小值是为了符合二叉搜索树的性质
    if(!z->left || !z->right) y = z;
    else y = treeSuccessor(z);

    //确定子节点
    // case 1:只存在一个或不存在子节点 
    // case 2: 存在两个子节点，通过上次递归，它的左节点是必不存在的
    // 综上，y至多存在一个子节点
    if(y->left) x= y->left;
    else x= y->right;

    // 不一定存在子节点
    if(x){
        x->parent = y->parent;
    }
    //如果y不存在父节点，意味着删除的是根节点
    if(!y->parent){
        root = x;
    }else{
        //如果删除的不是根节点
        // 判断y是父节点的左节点还是右节点
        if(y == y->parent->left){
            y->parent->left = x;
        }else{
            y->parent->right = x;
        }
    }

    if(y != z){
        // case 2: 特殊处理
        z->key = y->key;
    }
    delete y;
}

int main(){
    int n;
    scanf("%d",&n);
    string op;
    root = NIL = nullptr;
    for(int i = 0;i<n;i++)
    {
        cin >> op;
        if(op[0] == 'i'){
            int a;
            scanf("%d",&a);
            insert(a);
        }
        if(op[0]=='p'){
            print();
        }
        if(op[0] == 'f'){
            int a;
            scanf("%d",&a);
            auto result = ::find(a);
            if(result == NIL){
                printf("no\n");
            }else{
                printf("yes\n");
            }
        }
        if(op[0] == 'd'){
            int a ;
            scanf("%d ",&a);
            tree_node_delete(find(a));
        }
    }
    return 0;
}