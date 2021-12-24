#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//设计思路


vector<vector<string>> getfile(ifstream &fs){
    vector<vector<string>> result;
    string line;
    while(getline(fs,line)){
        istringstream l(line);
        vector<string> words;
        string word;
        while(l>>word){
            words.push_back(word);
        }
        result.push_back(words);
    }
    return result;
}