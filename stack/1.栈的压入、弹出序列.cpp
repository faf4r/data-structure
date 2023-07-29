/*  栈的压入、弹出序列
描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
1. 0<=pushV.length == popV.length <=1000
2. -1000<=pushV[i]<=1000
3. pushV 的所有数字均不相同

示例1
输入：
[1,2,3,4,5],[4,5,3,2,1]
返回值：
true
说明：
可以通过push(1)=>push(2)=>push(3)=>push(4)=>pop()=>push(5)=>pop()=>pop()=>pop()=>pop()
这样的顺序得到[4,5,3,2,1]这个序列，返回true

示例2
输入：
[1,2,3,4,5],[4,3,5,1,2]
返回值：
false
说明：
由于是[1,2,3,4,5]的压入顺序，[4,3,5,1,2]的弹出顺序，要求4，3，5必须在1，2前压入，
且1，2不能弹出，但是这样压入的顺序，1又不能在2之前弹出，所以无法形成的，返回false      
*/

//! 关键：在不断push的过程中，如果遇到与popV相同的元素，就要暂停push而出栈，直到与popV不同再继续push
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */

    //! 法一：用一个实际的栈来模拟该过程，时间空间都是O(n)
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        stack<int> s;
        int j=0;
        for (auto i=0;i<pushV.size();i++){
            s.push(pushV[i]);
            while (!s.empty()/*如果push的数据都pop了，就不要继续了，否则pop会报错*/ && s.top()==popV[j]/*元素相同就要pop掉*/)
            {
                s.pop();
                j++;
            }
        }
        return s.empty();
    }

    //! 法二：用int size抽象表示栈的容量，而不实际使用栈，空间复杂度减小到O(1)
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        int top=-1, j=0;
        for (int element : pushV){  //遍历vector的元素(按顺序来的，下面的修改不改变后面的数据，所以遍历的元素是没问题的)
            top++;  // 进栈，top+1，下面给pushV（也就是栈）压入值
            pushV[top] = element;  //!把pushV当成一个栈(因为压栈也是这个顺序)，修改原数据，但是后面top不会超过压栈遍历顺序，所以后面数据不会影响
            while (top!=-1/*等价于栈不为空*/ && pushV[top]==popV[j])
            {
                top--;
                j++;
            }
        }
        return top==-1 ? true : false;
    }
};


int main(void){
    vector<int> s = {0,1,2};
    for (auto i:s){
        cout << &i << "  " << &s[i] << endl;
    }
    /*
    0x70fddc  0x7f2570
    0x70fddc  0x7f2574
    0x70fddc  0x7f2578
    ///! 从结果可知，for遍历元素时，是逐个逐个的用一个局部变量接收vector的值，
    ///! 遍历应该类似于Python用next继续，或者它内置的一个index，保证一定是按顺序遍历的，只要不改变长度，每个index位置不会变的
    ///! 当对s[i]进行操作时，确实会改变vector的值，但是在该题中，一定不会改变后面数据的值，而前面数据已经用了
    
    ///? 比如说传入的pushA是[0,1,2,3,4,5],popA是[2,1,5,4,0]那他就是
    ///? 先进栈3个，stack为[0,1,2]，然后pop了两个变成[0]，然后再进栈两个变成，[0,3,4,5]
    ///? 这个时候，它如果使用pushA直接作为栈的话，pushA就变成了[0,3,4,5,4,5]，所以改变了原数据
    */
    return 0;
}

//! 因为方法二要修改原数组，所以虽然是O(1)空间，但是仍然感觉不太好
