#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;
stack<int> nums;
stack<char> ops;

void eval() {
    cout << "op";
    auto b = nums.top(); nums.pop();
    auto a = nums.top(); nums.pop();
    auto c = ops.top(); ops.pop();
    if (c == '+') {
        nums.push(a + b);
    }
    if (c == '-') {
        nums.push(a - b);
    }
    if (c == '*') {
        nums.push(a * b);
    }
    if (c == '/') {
        nums.push(a / b);
    }
    cout << "done" << endl;
}

int main() {
    string line;
    cin >> line;
    unordered_map<char, int> ptr{ {'+',1},{'-',1},{'*',2},{'/',2} };
    for (int i = 0; i < line.size(); i++) {

        auto c = line[i];
        if (isdigit(c)) {
            int x = 0, j = i;
            while (j < line.size() && isdigit(line[j]))
                x = x * 10 + line[j++] - '0';
            i = j - 1;
            nums.push(x);
        }
        else if (c == '(') {
            ops.push(c);
        }
        else if (c == ')') {
            cout << "shh";
            while (ops.top() != '(') eval();
            ops.pop();
        }
        else {
            cout << c << endl;
            while (ops.size() && ops.top() != '(' && ptr[ops.top()] >= ptr[c]) { cout << "debug"<<ops.size(); eval(); }
            ops.push(c);
        }
    }
    cout << "shuru ";
    while (ops.size()) eval();
    cout << nums.top() << endl;
    return 0;
};