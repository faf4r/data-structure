#include <iostream>

using namespace std;

typedef enum {ERROR, OK} status;

//使用数组实现栈，操作时返回status
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
    status push(int val){
        if (top == MAXSIZE-1)
            return ERROR;
        else {
            data[++top] = val;
            return OK;
        }
    }
    status pop(int *var){
        if (top > -1){
            *var = data[top--];
            return OK;
        }
        else
            return ERROR;
    }
    bool is_empty(){
        return top==-1 ? true : false;
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
                stack.pop(&val);
                cout << val << endl;
            }
        }
        else {
            if (stack.is_empty()){
                cout << "error" << endl;
            }
            else {
                stack.pop(&val);
                stack.push(val);
                cout << val << endl;
            }
        }
    }

    return 0;
}
