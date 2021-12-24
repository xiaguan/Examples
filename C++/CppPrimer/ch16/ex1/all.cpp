#include <iostream>
using namespace std;

// 求数组长度
template <typename  T,size_t N> constexpr
int func(const T (&t)[N]){
    return N;
}

// 数组begin和end的实现
template <typename T>
T* begin(const T &t){return &t;}

template <typename T,size_t N>
T* end(const T (&t)[N]){return &t[N];}


// 为什么C++程序员更喜欢用!=而不喜欢< ，并且迭代器不喜欢下标
// 因为这种编程风格再标准库提供的所有容器上都有效

// 使用size_type和size打印容器元素
template <typename T>
void printblob(const T &t){
    typename T::size_type n = 0;
    while(n != t.size()) cout << t[n++] <<" ";
    cout << endl;
}

// 使用begin和end重载
template <typename T>
void printblob(const T &t){
    auto start = t.begin();
    while(start != t.end()) cout << *start++ <<" ";
    cout << endl;
}
