#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;


map<string, string> buildMap(ifstream &map_file)
{
    // 结果保存
    map<string,string> trans_map;
    string key;
    string value;
    // 将map_file 的第一个单词读入key 然后再讲后面的规则读入value
    while(map_file>>key && getline(map_file,value)){
        if(value.size() > 1){
            trans_map[key] = value.substr(1); //删除前置空格
        }
        else{
            //如果没有对应规则 抛出异常
            throw runtime_error("no rule for" +key);
        }
    }
    return trans_map;
}

string  transform(const string &s,const map<string,string> &m){
    //转换函数  注意该函数返回的是左值
    auto map_it = m.find(s);
    if(map_it != m.cend())
        return map_it->second;
    else
        return s;
}
void word_transform(ifstream &map_file, ifstream &input){
    // 处理rules.txt 中的内容
    auto trans_map = buildMap(map_file);
    string text;
    // 处理input 文件流 和string流进行交互
    while(getline(input, text)){
        istringstream stream(text);
        string word;
        bool firstword = true;  //控制是否打印空格,说实话这么写有点繁琐？
        while(stream>>word){
            if(firstword){
                firstword = false;
            }
            else{
                cout << " ";
            }
            cout << transform(word,trans_map);
        }
        cout << endl;
    }
}

int main(){
    string map_file_name = "rules.txt";
    string filename= "test.txt";
    ifstream input(filename,ios::in);
    ifstream f_map_file(map_file_name);
    cout << input.is_open();
    word_transform(f_map_file,input);
    return 0;
}
