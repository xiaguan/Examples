#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

void quchong(vector<int>& nums,bool is_ordered = false){
    if(!is_ordered) sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
}

void print_vector(const vector<int>& vec){
    for_each(vec.begin(),vec.end(),[](const int & i){cout << i <<" ";});
    cout << "\n";
}

int main(){

    //有序实现
    vector<int> nums ={0,0,0,1,1,2,2,3,4,5};
    quchong(nums,true);


    vector<int> nums_unodered = {3,4,5,1,2,3,4,5,1,2};
    //无序实现
    //方法一：借助set实现
    unordered_set<int> result;
    for_each(nums.begin(),nums.end(),[](const int & i){resu})
    print_vector(nums);
    print_vector(nums_unodered);
}