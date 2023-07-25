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

//使用链表实现栈
typedef struct Node {
    int val;
    Node *next;
} Node;

class LinkStack{
private:
    Node top;
public:
    LinkStack(){
        top.val = 0;  //元素个数
        top.next = NULL;
    }
    ~LinkStack(){
        Node *temp;
        while (top.next)
        {
            temp = top.next;
            top.next = temp->next;
            delete temp;
        }
    }
    LinkStack deepcopy();
    void push(int val);
    int pop();
    bool is_empty(){
        return top.next==NULL ? true : false;
    };
};

void LinkStack::push(int val){
    Node *temp = new Node;
    temp->next = top.next;
    temp->val = val;
    top.next = temp;
    top.val++;
}

int LinkStack::pop(){
    if (top.next == NULL)
        throw StackEmpty();
    else {
        Node *temp = top.next;
        top.next = temp->next;
        top.val--;
        int val = temp->val;
        delete temp;
        return val;
    }
}

LinkStack LinkStack::deepcopy(){
    //先头插法全部读出来，再全部压入栈，元素的正逆序
    Node head, *ptr=top.next;  //head是复制过去的链表的head，ptr用于遍历top
    head.next = NULL;
    while (ptr != NULL)
    {
        Node *temp = new Node;
        temp->next = head.next;
        temp->val = ptr->val;
        head.next = temp;
        ptr = ptr->next;
    }

    LinkStack stack;
    //依次压入元素
    ptr = head.next;
    while (ptr != NULL)
    {
        stack.push(ptr->val);
        ptr = ptr->next;
    }
    return stack;
}

int main(void){
    int n;
    cin >> n;
    string op;
    int val;
    LinkStack stack;
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
