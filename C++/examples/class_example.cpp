#include <iostream>
#include <string>
using namespace std;

// 定义一个人类的类，拥有年龄,性别，姓名三个个私有属性
//性别为常量

class People
{
    //声明为友元，便于输出量
    friend ostream& operator<<(ostream& o, const People& p);
public:
    // 构造函数的开始
    People() : age(0), name("Null") ,is_boy(true) {}

    People(int x, std::string s) : age(x),name(s),is_boy(true) {}
    People(int x, std::string s,bool in_boy) : age(x), name(s),is_boy(in_boy) {}
    People(int x) : People(x, "Null",true) {}
    People(std::string s) : People(0, s,true) {}

    //拷贝构造函数
    People(const People& p) {
        *this = p;
    }

    //一些成员函数
    string get_name() const {
        return this->name;
    }
    virtual void p_job(){
        cout << this->name <<"'s job is "<<"null"<<endl;
    }

    // 加号运算符通过成员函数重载
    People operator+(People& y) {
        People temp;
        temp.age = this->age + y.age;
        return temp;
    }

    // 前置递增运算符的重载
    People& operator++() {
        this->age += 1;
        return *this;
    }

    //后置递增运算符的重载
    // int表示占位参数，用于区分前置和后置
    People operator++(int) {
        //后置递增先返回值，后递增
        People temp(*this);
        this->age += 1;
        return temp;
    }

protected:
    int age;
    std::string name;
    bool is_boy;
};

// 左移运算符只能在全局区进行重载
ostream& operator<<(ostream& o, const People& p) {
    o << "The people's name is " << p.name;
    o << " ,age is " << p.age;
    o << ",sex is " <<((p.is_boy)?"boy":"girl");
    return o;
}

class Student:public People{
public:

    //构造函数
    Student(int x,char grades): student_id(x) ,score(grades){}
    Student() : student_id(-1),score('0') {}

    Student(int std_id,char grades,int age, string name, bool boy):
    student_id(std_id), score(grades),People(age,name,boy) {}
    Student(const Student &s){
        *this=s;
    }

    virtual void p_job(){
        cout << this->name << "'s job is student" <<endl;
    }

    ~Student(){}

    int student_id;  //学生号
    char score;   // 成绩，分为ABCD四个等级,0表示错误

};


/*People& operator++(People &p){
    p.age += 1;
    return p;
}*/

int main() {
    string name("su");
    People ss(19,"sss",0);
    Student su(2021,'a',19,"su",1);
    ss.p_job();
    su.p_job();
    cout << su ;    //隐式转换
}