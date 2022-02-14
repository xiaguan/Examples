#include <iostream>
using namespace std;

const int N = 2000000;
int n, q[N+1];

//堆排序
//主要函数是down，也就是确定其位置的函数
// 主要思想:一个结点i，父节点是i/2,左结点2i,右结点时2i+1;  类似于一个二叉树。
// 父节点的值>左子结点>右子结点

void down(int idx){ 
   // 从n/2开始排序
   // 一个结点，有父节点，左子结点，和右子结点，满足大根堆的性质

   int l,r,large;
   l  = 2*idx;
   r = 2*idx +1;


   //边界问题
   if(l <= n && q[idx] < q[l]){
       large = l;
   }else{
       large = idx;
   }

   if(r <= n && q[large]<q[r]) large = r;

   // 此时找到三者中最大的那一个
   if(large != idx) {
       swap(q[large],q[idx]);
       down(large); // 将idx换过去后继续排序
       }
}

int main(){
    cin >> n;

    //处理输入
    for(int i = 1;i<=n;i++) cin >> q[i];

    //排序
    //排序只用排一半
    for(int i = n/2;i>=1;i--) down(i);

    //输出
    for(int i = 1;i<=n;i++){
        cout <<" "<<q[i];
    }
    cout <<'\n';
    return 0;
}