#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void read_words(ifstream &in,vector<string> &result){
    string line,word;
    while(getline(in,line)){
        istringstream record(line);
        while(record>>word){
            result.push_back(word);
        }
        result.push_back("\n");
    }
}

int main(){
    ofstream out("text3.txt");
    out<<"begin";
    ifstream in_text1("text1.txt",ios::in);
    ifstream in_text2("text2.txt",ios::in);
    

    string line1,line2;
    while((getline(in_text1,line1) && line1!="end") && (getline(in_text2,line2) && line2!="end")){
        string a,b,c;
        istringstream record1(line1);
        istringstream record2(line2);
        while(record1>>a && record2>>b){
            if(a=="begin" || b=="begin") break;
            else{
                c = to_string(atoi(a.c_str())+atoi(b.c_str()));
                c += " ";
                out<<c;
            }
        }
        out<<'\n';
    }
    out<<"end"<<endl;
    return 0;
}