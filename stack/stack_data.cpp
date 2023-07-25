#include <iostream>
#include <string>

using namespace std;

class StackEmpty: public std::exception{
public:
    const char * what() const noexcept{
        cout << "Error: Stack is empty." << endl;
        return "Error: Stack is empty.";
    }
};

//使用数组实现栈，操作时直接返回数据，否则报错
#define MAXSIZE 100000
class stack
{
private:
    int data[MAXSIZE];
    int top;
public:
    stack(){
        top = -1;
    }
    bool push(int val){
        if (top == MAXSIZE-1)
            return false;
        else {
            data[++top] = val;
            return true;
        }
    }
    int pop(){
        if (top > -1){
            return data[top--];
        }
        else
            throw StackEmpty();  //stack is empty
    }
    bool is_empty(){
        return top==-1 ? true : false;
    }
    bool is_full(){
        return top==MAXSIZE-1 ? true : false;
    }
};


int main(void){
    int n;
    cin >> n;
    string op;
    int val;
    stack stack;
    for (auto i=0; i<n; i++){
        cin >> op;
        if (op=="push"){
            cin >> val;
            stack.push(val);
        }
        else if (op=="pop"){
            if (stack.is_empty()){
                cout << "error" << endl;
            }
            else {
                cout << stack.pop() << endl;
            }
        }
        else {
            if (stack.is_empty()){
                cout << "error" << endl;
            }
            else {
                val = stack.pop();
                stack.push(val);
                cout << val << endl;
            }
        }
    }

    return 0;
}
