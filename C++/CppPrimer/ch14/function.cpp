#include <iostream>
#include <stack>
#include <unordered_map>
#include <functional>
using namespace std;



class Caculator{
public:
    static unordered_map<char,function<double(const double&,const double&)>> caozuo;
private:
    stack<int> nums;
    stack<char> ops;
};
unordered_map<char,function<double(const double&,const double&)>> Caculator::caozuo ={
        {
            '+',[](const double&a,const double&b){return a+b;}
            },
        {
                '-',[](const double&a,const double&b){return a-b;}
        },{
                '*',[](const double&a,const double&b){return a*b;}
        },{
                '/',[](const double&a,const double&b){return a/b;}
        }
};
int main(){
    Caculator hh;
    cout<<hh.caozuo['+'](1.111,1.0);
}