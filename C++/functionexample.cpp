#include <iostream>
#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>

// 测定一个函数的运行n次的时间ms计算，返回double
template <typename T>
std::chrono::duration<double,std::ratio<1,1000>> func_run_time(std::function<T> func, int n){
    auto start = std::chrono::high_resolution_clock::now();
    while(n--){
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration<double,std::ratio<1,1000>>(end-start);
    return result;
}