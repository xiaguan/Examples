#include <iostream>
using namespace std;

const int N = 1e6+10;

int m;
int e[N],l[N],r[N],idx;

//在某个下标k的右边插入一个x
void insert(int k ,int x){
    // 首先存下当前的值
    e[idx] = x;
    //在右边插入x，换句话说，这个数的左边就是下标k
    l[idx]=k;
    //再插入，双向链表，左右都要改变
    r[idx] = r[k];
    l[r[k]] = idx;

    // 更新r[k]
    r[k] = idx++;
}

void remove(int a){
    l[r[a]] =l[a];
    r[l[a]] = r[a];
}

int main()
{
    cin >> m;

    // 0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;

    while (m -- )
    {
        string op;
        cin >> op;
        int k, x;
        if (op == "L")
        {
            // 左侧插入
            cin >> x;
            insert(0, x);
        }
        else if (op == "R")
        {
            cin >> x;
            insert(l[1], x);
        }
        else if (op == "D")
        {
            cin >> k;
            remove(k + 1);
        }
        else if (op == "IL")
        {
            cin >> k >> x;
            insert(l[k + 1], x);
        }
        else
        {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }

    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
    cout << endl;

    return 0;
}
