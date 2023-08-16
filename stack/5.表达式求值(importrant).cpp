/*
描述
请写一个整数计算器，支持加减乘三种运算和括号。

数据范围：
0≤∣s∣≤100，保证计算结果始终在整型范围内

要求：空间复杂度： O(n)，时间复杂度: O(n)

示例1
输入：
    "1+2"
返回值：
    3
示例2
输入：
    "(2*(3-4))*5"
返回值：
    -10
示例3
输入：
    "3+2*3*4-1"
返回值：
    26
*/

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * 返回表达式的值 //!网络题解
     * @param s string字符串 待计算的表达式
     * @return int整型
     */
    int solve(string s) {
        int res = 0; //用于返回当前字符串的计算结果
        stack<int> sum; //用于求和
        char sign = '+'; //记录前一个符号，初始化为+，因为可以看成当前字符串前先加0
        int num = 0; //用于将连续数字字符串转化成数字或者记录递归结果  //!这里初始为0，每次读一个char，并没有读完数字，如果遇到数字，就*10再算，知道遇到运算符才把num压栈
        for(int i = 0; i < s.size(); i++) { //遍历每一个字符
            if(s[i] >= '0' && s[i] <= '9') //先处理数字字符
                num = 10 * num + s[i] - '0'; //进位后加个位数
            if(s[i] == '(') { //对于括号
                int left = i++, count = 1; //用left记录最左括号位置，count记录左括号数，i当成右指针右移一格
                while(count > 0) { //最终目的是找到与最左括号匹配的右括号，类似于栈操作
                    if(s[i] == '(') count++;
                    else if(s[i] == ')') count--;
                    i++;
                }
                num = solve(s.substr(left + 1, i - left - 2)); //迭代计算括号内数值，注意不要包含最左最右括号，不然会死循环
                i--; //此时i是最右括号下一位，需要左移一位防止最右括号在字符串尾时发生越界从而使下面的判定失效
            }
            //! 它是先在整个式子前面加个符号，这样保证每个数前面都有一个对应的符号来运算，
            //! 这样每次遇到运算符的时候，都是作为sign存储下次用的，对于每个sign，就可以用前面算的num值了
            //! 另外这里上下分开的，上面计算num，下面处理sign
            if(i == s.size() - 1 || s[i] == '+' || s[i] == '-' || s[i] == '*') { //对于字符串尾，或者加减乘，此时我们用的符号是上一次的，结算当前数字
                if(sign == '+') sum.push(num); //加法入栈
                else if(sign == '-') sum.push(-num); //减法相当于加负数
                else if(sign == '*') sum.top() *= num; //乘法与栈顶相乘
                sign = s[i]; //更新符号，若为末尾的右括号也无妨，因为马上就退出循环了
                num = 0; //重置当前数
            }
        }
        while(!sum.empty()) { //将栈内所有数字相加
            res += sum.top();
            sum.pop();
        }
        return res; //返回当前字符串计算结果
    }

    /**
     * 遇到'+'就直接push后面的值，但是后面可能是括号，所以'+'可以忽略
     * 
     */
    //!!!! compile failed...
    int my_solution(string s){
        int result = 0;  //返回值

        stack<int> st;
        int num;
        int a,b;
        for (int i=0; i<s.size(); i++){
            switch (s[i])
            {
            case '+':  //这个等于无用，直接跳过
                break;
            case '-':
                if (s[i+1]=='('){
                    st.push(- deal_bracket(s, ++i));
                } else {
                    st.push(- get_num(s, i));
                }
                break;
            case '*':
                a = st.top();
                st.pop();
                if (s[i+1]=='('){
                        b = deal_bracket(s, ++i);
                    } else {
                        b = get_num(s, i);
                    }
                st.push(a*b);
                break;
            case '(':
                st.push(deal_bracket(s, ++i));
                break;
            case ' ':
                break;
            default:  // 剩下为数字
                num = get_num(s, i);
                st.push(num);
                break;
            }
        }
        while (!st.empty()){
            result += st.top();
            st.pop();
        }

        return result;
    }

    /**
     * 从index开始读取一个数并返回，同时修改index去到新的位置
     * 用的是一个num来存储的方法，当然也可以构造字符串，然后用stoi(string)方法
     */
    int get_num(string s, int &index){
        int num = 0;
        for (; s[index]>='0' && s[index]<='9' && index<s.size(); index++){  //保证遍历时是数字且保证在s序列以内
            num = num*10 + s[index]-'0';
        }
        index--;  //此时是非数字符号，要-1，因为回到主程序for结尾会i++
        return num;
    }
    /**
     * 专门处理遇到括号，把整个括号里构建子字符串去计算值
     */
    int deal_bracket(string s, int &index){
        int count = 1; //记录左括号的，运行该函数代表默认有一个了
        string sub;
        int start=index, length=0;
        while (count!=0 && index<s.size()){
            if (s[index]==')'){
                count--;
            } else if (s[index]=='('){
                count++;
            }
            index++;
            length++;
        }
        sub = s.substr(start, length);
        index--;  //遇到有括号之后还有index++，所以要在结束的时候减回来
        return my_solution(sub);
    }
};

int main(void){
    Solution s;
    cout << s.my_solution("1+2") << endl;

    return 0;
}
