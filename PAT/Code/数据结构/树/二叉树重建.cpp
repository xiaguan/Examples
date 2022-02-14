#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> pre,in,pos;
int n,idx;

//1 2 3 4 5  
//3 2 4 1 5

/* 由于前序遍历的原因，第一个出现的是根，后面两个可能是子节点
*  此时又根据中序遍历的结果，1左右两端的点分别位于它的左右树上
*  这题只需要后序遍历的结果，树的重建还是比较简陋
*/

void rec(int l,int r){
    if(l >= r) return;
    int root = pre[idx++];   // 先找根
    int m = distance(in.begin(),find(in.begin(),in.end(),root));  

    //将左树和右树分隔开
    rec(l,m);     // 左树
    rec(m+1,r);    // 右树
    pos.push_back(root);   //最后添加根节点
}


int main(){
    int k;
    cin >> n;
    //前序遍历读入
    for(int i = 0;i<n;i++){
        cin >> k;
        pre.push_back(k);
    }
    //中序遍历读入
    for(int i= 0;i<n;i++){
        cin >> k;
        in.push_back(k);
    }

    // 二叉树重建
    idx = 0;
    rec(0,n);

    for(int i = 0;i<n;i++){
        if(i) cout <<" ";
        cout << pos[i];
    }
    cout << endl;
}