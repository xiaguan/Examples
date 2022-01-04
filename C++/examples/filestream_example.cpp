#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct PersonInfo{
    string name;
    vector<string> phones;
};
int a = 10 ;
cout << a << endl;

int main(){
    ifstream in("test.txt",ios::in);
    if(in){
        cout << "File open success:" << endl;
    }
    string line, word;
    vector<PersonInfo> people;
    while(getline(in,line) && line!="over"){
        cout << "Getline success: " << line << endl;
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while( record >> word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    for(int i = 0; i <people.size();i++){
        cout << people[i].name << "'s phone number is: ";
        for(int n = 0;n<people[i].phones.size();n++){
            cout << people[i].phones[n] << " ";
        }
        cout << endl;
    }
    in.close();
    return 0;
}