# C++ 并发学习
## thread
### 使用std::thread t(callable object);
t：线程名称 callable obeject:可调用对象，例如函数，重载了()的类，lambda
### t.join()
执行到此，如果t未执行完毕，等待t的结束，如果执行完毕就继续向下执行
如果t执行完毕，t.joinable()返回false,没执行完毕返回true;

### t.joinable()
 可以判断t是否在执行线程，换种角度说，t是否可以进行操作
### t.detch()
将线程分离出去，不管t执行与否，t.detch后，joinable都会返回fasle;
### std::move转移线程所有权 
std::unique_ptr 和std::thread可移动，但不可拷贝。
### std::thread::id
1.可以通过调用get_id()获取，如果t没有与任何线程关联，get_id()返回std::thread::type默认值（thread::id of a non-executing thread），这个值表示无限程。
2. 当前线程中低啊用std::this_thread::get_id
这个类型的值可以作为无序容器的键值
这个值一般从1（main）函数开始，向后递增


## 条件竞争
写只能有一个写，读可以有多个写

## mutex
std::mutex 创建互斥量实例
### mutex.lock()
如果mutex此时已经被Lock了，则该线程阻塞，直到mutex可以被lock.
### mutex.unlock()
即使mutex由另一个线程lock，unlock也能解锁，所以lock和unlock一定要配套，lock可以阻塞，unlock不行
### lock_guard<std::mutex>
构造时上锁，析构时unlock,
使用std::adopt_lock，表示已上锁，只用unlock
### scoped_lock()(C++17)
这个新类型能接受不定数量的互斥量类型作为模板参数，以及相应的互斥量（数量和类型）作为构造函数，支持构造即上锁（C++17可以通过隐式参数模板类型推导机制构造实例）

### std::lock可以一次性锁住多个互斥量，并且没有死锁风险
std::lock 要么将两个都锁住，要不一个都不锁

## std::unique_lock-灵活的锁
与lock_guard不同的是，它提供了很多外接接口对锁进行操作。
同时，std::unique_lock不会总与互斥量的数据类型有关。
std::adopt_lock，对互斥量进行管理
std::defer_lock,保持解锁状态，std::unique_lock会占用比较多的空间，并且比lock_guard要慢一些。
### 可以移动(std::move)

### std::call_once 和std::once_flag
保证函数只会被执行一次

## std::shared_mutex
读写锁，shared是读，没有的是写，读可以多个一起读，写只能一个写

## 等待条件达成(condition_variable)
需要一个互斥量一起才能工作（互斥量是为了同步），condition_variable仅限于与std::mutex一起工作，而std::condition_variable_any可以和任何满足最低标准的互斥量一起工作，后者会产生额外的开销。
### std::condition_variable 变量名
初始化
### cond.notify_one() 
唤醒其中一个线程
### cond.wait(unique_lock,返回bool的可执行对象)


