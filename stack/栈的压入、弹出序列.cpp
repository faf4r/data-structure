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

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */

     //! 或者用一个栈的实际操作来实现
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        //! 索引不能出现顺序（除了开头），比如示例2中最后的12就是顺序，所以错了45321
        //! 按照正常进出栈顺序来，最终index理论上要走到最后
        int index=0, p1=0, p2=0, top=0;
        for (auto i=0; i<pushV.size(); i++){
            if (pushV[i]==popV[index]){
                p2 = i;
                p1 = i;
                while (pushV[p1]==popV[index])
                {
                    p1--;
                    index++;
                }
                
                index++;
            }
        }

    }
};


int main(void){
    return 0;
}