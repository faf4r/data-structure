/*
描述
牛牛拿到了一个字符串。
他每次“点击”，可以把字符串中相邻两个相同字母消除，例如，字符串"abbc"点击后可以生成"ac"。
但相同而不相邻、不相同的相邻字母都是不可以被消除的。
牛牛想把字符串变得尽可能短。他想知道，当他点击了足够多次之后，字符串的最终形态是什么？

输入描述：
一个字符串，仅由小写字母组成。（字符串长度不大于300000）
输出描述：
一个字符串，为“点击消除”后的最终形态。若最终的字符串为空串，则输出0。

示例1
输入：
    abbc
输出：
    ac
示例2
输入：
    abba
输出：
    0
示例3
输入：
    bbbbb
输出：
    b
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int _main() {
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

//! 法二：用一个string代替实现stack，便于最后输出结果
int main(void){
    struct {
        string data;
        int top=-1;
    } stack;
    char ch;

    while (cin >> ch)
    {
        if (stack.top==-1 || stack.data[stack.top]!=ch){
            stack.data.push_back(ch);
            stack.top++;
        } else {
            stack.data.pop_back();
            stack.top--;
        }
    }

    if (stack.top==-1)
        cout << 0;
    else
        cout << stack.data;

    return 0;
}
