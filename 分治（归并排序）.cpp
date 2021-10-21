#include <iostream>
#include <vector>
using namespace std;
void p_vector(vector<int> n) {
    for (auto x : n) {
        cout << x << " ";
    }
    cout << endl;
}
vector<int> merge(vector<int> left, vector<int> right) {
    int n = 0;
    vector<int> result(left.size()+right.size());
    auto l_begin = left.begin(), r_begin = right.begin();
    while (l_begin != left.end() && r_begin != right.end()) {
        if (*l_begin < *r_begin) {
            result[n++] = *l_begin;
            l_begin++;
        }
        else {
            result[n++] = *r_begin;
            r_begin++;
        }
    }
    while (l_begin != left.end()) {
        result[n++] = *l_begin;
        l_begin++;
    }
    while (r_begin != right.end()) {
        result[n++] = *r_begin;
        r_begin++;
    }
    return result;
}

vector<int> mergesort(vector<int>& nums) {
    if (nums.size() <2) return nums;
    p_vector(nums);
    const size_t mid = nums.size()/ 2;
    vector<int> left(nums.begin(), nums.begin() + mid);
    vector<int> right(nums.begin() + mid , nums.end());
    return merge(mergesort(left), mergesort(right));
}
int main() {
    vector<int> n{ 6,5,4,3,2,1 };
    n = mergesort(n);
    p_vector(n);
    
}
