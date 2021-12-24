#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <functional>
#include <numeric>
#include <time.h>

#define f(x,y) return x<y?x:y;

using namespace std;

clock_t start, end1;


template <typename Iterator, typename T>
struct accmulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accmulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last); //长度
    if (!length) return init;

    unsigned long const min_per_threads = 25;
    unsigned long const max_threads = (length + min_per_threads - 1) / min_per_threads;
    unsigned long const harware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(harware_threads != 0 ? harware_threads : 2, max_threads);
    cout << num_threads << endl;

    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator bloack_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = bloack_start;
        std::advance(block_end, block_size); // 迭代器移动
        threads[i] = std::thread(accmulate_block<Iterator, T>(), bloack_start, block_end, std::ref(results[i])                                                                                                                              );
        bloack_start = block_end;
    }
    accmulate_block<Iterator, T>()(bloack_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fun_ref(&std::thread::join));

    return accumulate(results.begin(), results.end(), init);
}



int main() {
    auto p  = new vector<int>(1e5,1);
    auto nums = *p;

    int n = 1;
    cout << f(19,10);
    cout << n << endl;
    start = clock();
    cout << parallel_accmulate(nums.begin(), nums.end(), 0)<<endl;
    for(int i = 0;i<10;i++) parallel_accmulate(nums.begin(),nums.end(),0);
    end1 = clock();
    double endtime = (double)(end1 - start) / CLOCKS_PER_SEC;
    cout << endtime * 1000 << endl; //ms为单位

    start = clock();
    long result = 0;
    for(int i = 0;i<10;i++){
        result = 0;
        auto begin_s = nums.begin();
        while(begin_s != nums.end()) result += *begin_s++;
    }
    cout << result << endl;
    end1 = clock();
    endtime = (double)(end1 - start) / CLOCKS_PER_SEC;
    cout << endtime * 1000 << endl; //ms为单位


    start = clock();
    cout << accumulate(nums.begin(), nums.end(), 0)<<endl;
    for(int i = 0;i<10;i++) accumulate(nums.begin(),nums.end(),0);
    end1 = clock();
    endtime = (double)(end1 - start) / CLOCKS_PER_SEC;
    cout << endtime * 1000 << endl; //ms为单位

    delete p;
}