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
    StrVec(StrVec &&s) noexcept;
    StrVec &operator=(const StrVec &s);
    StrVec &operator=(StrVec &&) noexcept;
    ~StrVec();

    void push_back(const std::string &s);
    size_t size() const {return first_free-elements;};
    size_t capacity() const{return cap-elements;};
    std::string *begin() const {return elements;};
    std::string *end() const {return first_free;};
private:
    std::allocator<std::string> alloc;
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
    // alloc.allocate(n)调用成功后返回一个指向该段内存第一个元素的指针
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

StrVec &StrVec::operator=(const StrVec &s) {
    auto data = alloc_n_copy(s.begin(),s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate(){
    auto newcapacity = size()?2*size():1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0 ;i !=size();i++){
        alloc.construct(dest++,std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements+newcapacity;
}

StrVec::StrVec(StrVec &&s)noexcept: elements(s.elements),first_free(s.first_free),cap(s.cap){
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    if( this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}



