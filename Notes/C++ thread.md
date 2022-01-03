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

### std::shared_mutex
读写锁，shared是读，没有的是写，读可以多个一起读，写只能一个写

## 等待条件达成(condition_variable)
需要一个互斥量一起才能工作（互斥量是为了同步），condition_variable仅限于与std::mutex一起工作，而std::condition_variable_any可以和任何满足最低标准的互斥量一起工作，后者会产生额外的开销。
### std::condition_variable 变量名
初始化
### cond.notify_one() 
唤醒其中一个线程
### cond.wait(unique_lock,返回bool的可执行对象)

## 使用期望值等待一次性事件
### std::future
C++ 标准库中有两种期望值，声明在头文件<future>头文件中：唯一期望值（uniquefutures）(std::future<>) 和共享期望值(shared futures)(std::shared_futrue<>)。std::future的实例只能与一个指定事件相关联，而std::shared_futrue的实例能关联多个事件。后者的实现中，所有实例会在同时变为就绪状态。与数据无关的地方，可以使用std::future<void> 和std::shared_futrue<void>的特化模板。
期望值本身并不提供同步访问。当多个线程需要访问一个独立期望值对象时，必须使用互斥量或类似同步机制对访问进行保护。
#### future操作
share 从*this转移共享状态给shared_futrue并返回
get 获取结果
valid 检查future是否拥有共享状态
wait  等待结果可用
wait_for 
wait_until

get是一次性事件，调用后valid为false,共享状态被释放。

### 后台任务的返回值
#### std::async
std::thread 并不提供直接接受返回值的机制，这里就需要std::async函数模板（同样声明在<future>头文件中）

当不着急要任务结果时，可以使用std::async启动一个异步或同步任务。std::async会返回一个std::future对象，这个对象持有最终计算出来的结果。当需要这个值时，只需要调用这个对象的get()成员函数；并且会阻塞线程知道期望值状态为就绪；之后，返回计算结果。

std::async的使用方法和std::thread差不多。
对于异步还是同步，由第一个参数决定
1. std::lanuch::async 异步
2. std::lanuch::defered 同步
3. std::lanuch::async | std::launch::defered 可以异步或同步，由系统决定
4. 默认是3
书上说的是std::lanuch::defered,表明函数调用被延迟到wait()或get()函数调用时才执行，std::launch::async 表明函数必须在其独立上的线程上执行。

std::async()做如下的事情
·自动创建一个线程(或从内部线程池中挑选)和一个promise对象。
·然后将std::promise对象传递给线程函数，并返回相关的std::future对象
·当我们传递参数的函数退出时，它的值将被设置在这个promise对象中，所以最终的返回值将在std::future对象中可用

### 任务与期望值关联
std::packaged_task<> 对一个函数或可调用对象，绑定一个期望值。当调用其独享时，它就会调用相关函数或可调用对象，将期望状态设置为就绪，返回值也会被储存。模板参数是函数签名<返回值类型(形参列表)>。
使用get_future返回std::future<> 

#### 使用std::promises
每个线程同时处理多个连接事件，对需要处理大量的网络连接的应用而言是普通的做法。
std::promise<T>提供设定值的方式，与std::future<T>相关联。一对std::promise/std::future。期望值可以阻塞等待线程，同时，提供数据的线程可以使用组合中的承诺值来对相关值进行设置，并将期望值的状态设置为“就绪”

future让你取回数据，promise让你设置数据。
promise的内部有一个future

操作：
get_future 
set_value
set_value_at_thread_exit
set_exception
set_exception_at_thread_exit

可以通过一个std::promise 的get_future() 成员函数来获取与之相关的std::future 对象，跟std::packaged_task的用法类似。当承诺值已经设置完毕，对应期望值的状态就变为就绪，并且可用于检索已存储的值。在设置值之前销毁std::promise ，将会存储一个异常。

eg:单线程处理多接口的实现
   在这个例子中，可以使用一堆std::promise<bool>/std::future<bool> 找出一块传出成功的数据块;

```
#include <future>

void process_connections(connection_set& connections) //多个连接处理函数 传入的是连接set
 {
    while(!done(connections)) // 1  //如果连接处理未完成
    {
        // 遍历连接集合
        for(connection_iterator // 2
            connection=connections.begin(),end=connections.end();
        connection!=end;
             ++connection)
        {
        if(connection->has_incoming_data()) // 如果连接有即将到来的数据
        {
        data_packet data=connection->incoming();   // 获取数据
        std::promise<payload_type>& p=connection->get_promise(data.id); // 注意：这里是std::promise 的引用
        p.set_value(data.payload);
        }
        if(connection->has_outgoing_data()) // 5
        {
        outgoing_packet data=onnection->top_of_outgoing_queue();
        connection->send(data.payload);
        data.promise.set_value(true); // 设置期望值为就绪
        }
        }
    }
 }
```

#### std::shared_future
std::future，一个线程等待一个结果。而std::shared_future实例可以拷贝,所以多个对象可以引用同一关联期望值的结果。
每一个std::shared_futrue的独立对象上，成员函数调用返回的结果还是不同步的，所以为了在多个线程访问一个独立对象是避免数据竞争，必须使用锁。




