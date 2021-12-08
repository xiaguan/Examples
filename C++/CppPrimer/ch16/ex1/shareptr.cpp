#include <iostream>
using namespace std;

// 尝试用share_ptr写一个list



template <typename T> class shareptr {
public:
    shareptr();//默认初始化
    shareptr(const T& t); //使用T类型的数据初始化
    shareptr(T*);
    shareptr(const shareptr<T>& sp); //拷贝一个shareptr的指针
    ~shareptr();
    shareptr<T> operator=(shareptr<T>& sp);
    T& operator*(); //解引用操作符
    T*& get();
private:
    T* p = nullptr;
    int* rf_count_p = nullptr;
};

//默认构造函数
template <typename T>
shareptr<T>::shareptr() {
    rf_count_p = new int(0);
}

// 使用T对象初始化
template <typename T>
shareptr<T>::shareptr(const T& t) {
    p = new T(t);
    rf_count_p = new int(1);
}

template <typename T>
shareptr<T>::shareptr(T* t) {
    p = t;
    rf_count_p = new int(1);
}

// 将另一个shareptr拷贝
template <typename T>
shareptr<T>::shareptr(const shareptr<T>& rp) {
    // 清空内存
    if (p != nullptr) delete p;
    if(rf_count_p)delete rf_count_p;
    //重置指针
    p = rp.p;
    rf_count_p = rp.rf_count_p;
    //引用数加1
    (*rf_count_p)++;
}

template <typename T>
T& shareptr<T>::operator*() {
    return *(this->p); // 解引用操作符
}

template <typename T>
shareptr<T> shareptr<T>::operator=(shareptr<T>& rp) {
    //左侧对象等于右侧对象
    if (rp.get() == nullptr) return *this;
    if (*rf_count_p == 1) { delete p; delete rf_count_p; }
    else (* rf_count_p)--;
    p = rp.p;
    rf_count_p = rp.rf_count_p;
    (*rf_count_p)++;
    return *this;
}

template <typename T>
shareptr<T>::~shareptr<T>() {
    if (*rf_count_p == 1) {
        if (p) {
            cout << "释放内存" << (*p).data << endl;
            delete p;
        }
        delete rf_count_p;
    }
    else {
        (*rf_count_p)--;
    }
}

template <typename T>
T*& shareptr<T>::get() {
    return this->p;
}

struct su_list {
    su_list() {
        data = 0;
        next.get() = nullptr;
    }
    su_list(const int& x,shareptr<su_list>& p) {
        data = x;
        next = p;
    }
    su_list(const int& x) {
        data = x;
        next.get() = nullptr;
    }
    int data;
    shareptr<su_list> next;
};

shareptr<su_list> head = new su_list(0);


void insert(const int& x) {

    shareptr<su_list> temp = new su_list(x);
    if ((*head).next.get() != nullptr) {
        (*temp).next = (*head).next;
    }
    else {
        (*temp).next.get() = nullptr;
    }
    (*head).next = temp;
}

void printlist(shareptr<su_list>& h) {

    auto temp = ( * h).next;

    while (temp.get() != nullptr) {
        cout << (*temp).data << " ";
        temp = (*temp).next;
        if ((*temp).next.get() == nullptr) {
            cout << (*temp).data << endl;;
            break;
        }
    }
}

void rev_printlist(shareptr<su_list>& h) {
    shareptr<su_list> rev_head(su_list(0));
    (*rev_head).next.get() = nullptr;
    auto temp = (*h).next;
    while ((*temp).next.get() != nullptr) {
        shareptr<su_list> ss(su_list((*temp).data));
        if ((*rev_head).next.get() == nullptr) {
            (*ss).next.get() = nullptr;
        }
        else {
            (*ss).next = (*rev_head).next;
            
        }
        (* rev_head).next = ss;
        temp = (*temp).next;
        if ((*temp).next.get() == nullptr) {
            shareptr<su_list> cc(su_list((*temp).data,(*rev_head).next));
            (*rev_head).next = cc;
        }
    }

    printlist(rev_head);
}


int main() {
    int n;
    cout << "input the number you want to enter\n";
    (*head).next.get() = nullptr;
    while (cin >> n) {
        insert(n);
    }
    cout << "正向打印" << endl;
    printlist(head);
    cout << "逆向打印" << endl;
    rev_printlist(head);
}