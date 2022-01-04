#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <memory>

using namespace std;
using line_no = vector<string>::size_type; //无符号整形

// QueryResult
class QueryResult {
	friend ostream& print(ostream&, const QueryResult&);
public:
	//构造函数 
	QueryResult(string s, shared_ptr<set <line_no>> p,shared_ptr<vector<string>> f) :word(s), lines(p), file(f) {};
private:
	// QueryResult 三个成员 单词，单词所在的行，所在行的内容
	string word;
	shared_ptr<set <line_no>> lines;
	shared_ptr<vector<string>> file;
};

// TextQuery的声明
class TextQuery {
public:
	TextQuery(std::ifstream&); //构造函数的声明
	QueryResult query(const std::string& s) const;//查询函数
private:
	shared_ptr<vector<string>> file;  //一个指向vector<string>中的每个string对应文件的每一行
	map < string, shared_ptr<set<line_no>>> wm;  //每个单词，所出现的行号
};

// TextQuery 构造函数的定义
TextQuery::TextQuery(ifstream& is):file(new vector<string>) {
	//file是一个智能指针
	string text;
	while(getline(is, text)) {
		//先读行
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);  //使用istingstrem获得每一行中的word
		string word;
		while (line >> word) {
			auto& lines = wm[word];  // 这里的lines是shared_ptr 
			if (!lines)
				//如果lines为空，重置
				lines.reset(new set<line_no>);
			lines->insert(n);//否则将行号插入word对应的set里面
		}
	}
}

// query查询函数的定义
//接受一个待查询单词 
QueryResult TextQuery::query(const string& word) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(word);
	if (loc == wm.end())
		return QueryResult(word, nodata, file);
	else
		return QueryResult(word, loc->second, file);
}
string make_plural(size_t ctr, const string& word, const string& ending) {
	return (ctr > 1) ? word + ending: word;
}

ostream& print(ostream& os, const QueryResult& qr) {
	os << qr.word << "occurs" << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	for (auto num : *(qr.lines)) {
		os << "\t(line" << num + 1 << ")"
			<< *(qr.file->begin() + num) << endl;
	}
	return os;
}

void runQueries(ifstream& infile) {
	TextQuery tq(infile);//使用该文件流初始化一个TextQuery对象tq
	while (true) {
		cout << "enter word to look for,or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
}
int main() {
	ifstream openfile("test.txt");
	if (openfile) {
		cout << "File open success!" << endl;
		runQueries(openfile);
	}
	else {
		throw runtime_error("open failed");
	}
	return 0;
}
