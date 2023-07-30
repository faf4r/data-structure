#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    stack<char> s;
    char ch;
    while (cin >> ch)
    {
        if (s.empty() || s.top()!=ch){
            s.push(ch);
        } else {
            s.pop();
        }
    }

    string ret;  //用于把stack剩下数据读出来返回
    if (s.empty())
        ret = "0";
    else
        while (!s.empty())
        {
            ret.insert(0, 1, s.top());  //在原串下标为0的字符前插入1个字符char  (0, string)//两个参数时是插入字符串，这里是字符
            s.pop();
        }
    cout << ret;

    return 0;
}
