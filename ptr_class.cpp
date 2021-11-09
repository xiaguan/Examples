// 动态内存管理类StrVec

/*1：element:指向分配的内存中的首元素
 * 2： first_free:指向最后一个实际元素之后的位置
 *  3:cap:  指向分配的内存末尾之后的位置
 * */

#include <iostream>
#include <memory>

/*四个工具函数
 * alloc_n_copy分配内存，并拷贝一个给定范围中的元素。
 * free会销毁构造的元素并释放内存
 * chk_n_alloc 保证StrVec至少有容纳一个新元素的空间。如果没有空间，调用reallocate分配
 * reallocate  重新分配内存
 * */

class StrVec{
public:
    StrVec(): elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec& s);
    StrVec &operator=(const StrVec &s);
    ~StrVec();

    void push_back(const std::string &s);
    size_t size() const {return first_free-elements;};
    size_t capacity() const{return cap-elements;};
    std::string *begin() const {return elements;};
    std::string *end() const {return first_free;};
private:
    static std::allocator<std::string> alloc;
    std::string *elements,*first_free,*cap;

    void chk_n_alloc(){if(size()==capacity()) reallocate();}
    std::pair<std::string*,std::string*> alloc_n_copy(const std::string*,const std::string*);
    void free();
    void reallocate();
};

void StrVec::push_back(const std::string& s){
    chk_n_alloc();
    alloc.construct(first_free++,s);
}

//待解决
std::pair<std::string*,std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    auto data = alloc.allocate(e-b);
    return {data,std::uninitialized_copy(b,e,data)};
}

void StrVec::free() {
    if(elements){
        for(auto p = first_free;p!=elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements,cap-elements);
    }
}

StrVec::StrVec(const StrVec &s){
    auto newdata = alloc_n_copy(s.begin(),s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() {
    free();
}