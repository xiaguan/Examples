// 拉链法 ，后面有开放寻址法，还有一个待补的rehash

#include <iostream>
#include <cstring>
using namespace std;

const int N = 100003;

int e[N];  //存储数据
int h[N],ne[N];  //数组模拟链表
//h是头节点的意思

int idx = 0;
/*
 * 拉链法： 思想核心就是得到同一个余数时，得到一个k，每个k对应一个链表
 * k对应的链表头就是h[k],它的下一结点默认初始化为-1
 * 向链表中插入数据时，ne[idx] = h[k]，idx记录它存放在e中的位置
 * h[k] = idx++;    头节点的下一个结点变为idx
 * 这样通过for(int i = h[k];i!=-1;i = ne[i]) 就可以实现链表的查找
 */

//插入
void insert(int key){
    int k = (key%N+N)%N;
    e[idx] = key;   //存储数据

    //链表插入
    ne[idx] = h[k];
    h[k] = idx++;
}

bool find(int target){
    int k = (target%N+N)%N;
    for(int i = h[k];i != -1;i = ne[i]){
        if(e[i]==target) return true;
    }
    return false;
}

int main(){
    int n;
    cin >> n;
    memset(h,-1,sizeof(h));
    while(n--){
        char op[2];
        int a;
        scanf("%s %d",op,&a);

        if(op[0]=='I'){
            //插入
            insert(a);
        }else{
            //查询
            if(find(a)){
                puts("Yes");
            }else{
                puts("No");
            }
        }
    }
}


// 开放寻址
#include <iostream>
#include <cstring>
using namespace std;

const int N = 200003;
const int null = 0x3f3f3f3f;
int q[N];

int find(int target){
    int k = (target%N+N)%N;
    while(q[k] != null && q[k] != target){
        cout << q[k]<<" "<<null<<endl;
        k++;
    }
    return k;
}

int main(){
    // 插入查询
    char op[3];
    int num;
    int n;
    cin >> n;
    // memset小知识，memset是以一个一个字节填充的，第二个参数只能填一个字节大小
    memset(q,0x3f,sizeof(q));
    while(n--){
        scanf("%s %d",op,&num);
        if(op[0]=='I'){
            //插入

            q[find(num)] = num;
        }else{
            //查询
            if(q[find(num)]==num){
                puts("Yes");
            }else{
                puts("No");
            }
        }
    }
}