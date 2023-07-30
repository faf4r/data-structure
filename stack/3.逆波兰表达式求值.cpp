/*
描述
给定一个逆波兰表达式，求表达式的值。

数据范围：表达式长度满足 1≤n≤10^4，表达式中仅包含数字和 + ，- , * , / ，其中数字的大小满足∣val∣≤200 。

示例1
输入：
["2","1","+","4","*"]
返回值：
12

示例2
输入：
["2","0","+"]
返回值：
2
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief 用栈存储数据，遇到符号就pop两个出来计算，计算结果push回去下次使用，最后返回top（这时只有唯一一个元素了）
     * @param tokens string字符串vector 
     * @return int整型
     */
    int evalRPN(vector<string>& tokens) {
        stack<int> s;  //存储数据
        int a, b;  //遇到字符pop两个数据来运算
        for (auto ch : tokens){
            if (ch=="+"){
                b = s.top(); s.pop();  //注意c++的stack它的pop不返回值，要取值得先top再删掉它
                a = s.top(); s.pop(); //注意顺序，a运算b，逆波兰是ab符号，a是先入栈的，所以要后出
                s.push(a+b);
            } else if (ch=="-")
            {
                b = s.top(); s.pop();
                a = s.top(); s.pop();
                s.push(a-b);
            } else if (ch=="*")
            {
                b = s.top(); s.pop();
                a = s.top(); s.pop();
                s.push(a*b);
            } else if (ch=="/")
            {
                b = s.top(); s.pop();
                a = s.top(); s.pop();
                s.push(a/b);
            } else {
                s.push(stoi(ch));
            }
        }
        return s.top();
    }
};


int main(void){
    Solution s;
    vector<string> tokens = {"2","1","+","4","*"};
    cout << s.evalRPN(tokens)<< endl;
    return 0;
}