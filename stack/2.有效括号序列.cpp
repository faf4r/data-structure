/*
描述
给出一个仅包含字符'(',')','{','}','['和']',的字符串，判断给出的字符串是否是合法的括号序列
括号必须以正确的顺序关闭，"()"和"()[]{}"都是合法的括号序列，但"(]"和"([)]"不合法。

数据范围：字符串长度 0≤n≤10000

要求：空间复杂度 O(n)，时间复杂度 O(n)

示例1
    输入：
        "["
    返回值：
        false

示例2
    输入：
        "[]"
    返回值：
        true
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * @param s string字符串 
     * @return bool布尔型
     */
    //! 个人思路，将左括号push，遇到右括号就判断，对应就pop，不对应直接返回false，最后要求栈为空
    bool isValid(string s) {
        stack<char> stack;
        for (auto ch : s){
            switch (ch)
            {
            case '{':
                stack.push(ch);
                break;
            case '[':
                stack.push(ch);
                break;
            case '(':
                stack.push(ch);
                break;
            case ')':
                if (!stack.empty() && stack.top()=='('){
                    stack.pop();
                } else {
                    return false;
                }
                break;
            case ']':
                if (!stack.empty() && stack.top()=='['){
                    stack.pop();
                } else {
                    return false;
                }
                break;
            case '}':
                if (!stack.empty() && stack.top()=='{'){
                    stack.pop();
                } else {
                    return false;
                }
                break;
            }
        }
        return stack.empty();
    }

    //! 官方题解，栈push的是右括号，匹配的时候只需判断相等即可，其实也差不多
    bool isValid(string s) {
        //辅助栈
        stack<char> st;
        //遍历字符串
        for(int i = 0; i < s.length(); i++){
            //遇到左小括号
            if(s[i] == '(')
                //期待遇到右小括号
                st.push(')');
            //遇到左中括号
            else if(s[i] == '[')
                //期待遇到右中括号
                st.push(']');
            //遇到左打括号
            else if(s[i] == '{')
                //期待遇到右打括号
                st.push('}');
            //必须有左括号的情况下才能遇到右括号
            else if(st.empty())
                return false;
            //右括号匹配则弹出
            else if(st.top() == s[i])
                st.pop();
        }
        //栈中是否还有元素
        return st.empty();
    }
};