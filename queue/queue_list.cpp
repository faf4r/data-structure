#include <iostream>

using namespace std;

typedef struct Node
{
    int val;
    Node *next;
} Node;


class Queue{
private:
    Node *head, *rear;
public:
    Queue();
    ~Queue();
    void push(int val);
    void pop();
    bool empty();
    int front();
    int back();
    int size();
    Queue(Queue& queue);
    Queue(std::initializer_list<int> list);
};

Queue::Queue(){
    head = new Node;
    rear = new Node;
    head->next = NULL;
    rear->next = NULL;
    head->val = 0;  //空闲位置，可以拿来存储队列长度
}

Queue::~Queue(){
    while (!empty())
        pop();
    delete head;
    delete rear;
}

Queue::Queue(Queue &queue){
    head = new Node;
    rear = new Node;
    head->next = NULL;
    rear->next = NULL;
    head->val = 0;

    Node *tmp = queue.head->next;
    while (tmp)
    {
        push(tmp->val);
        tmp = tmp->next;
    }
}

Queue::Queue(std::initializer_list<int> list){
    head = new Node;
    rear = new Node;
    head->next = NULL;
    rear->next = NULL;
    head->val = 0;

    for (auto val=list.begin(); val!=list.end(); val++){
        push(*val);
    }
}

int Queue::size(){
    return head->val;
}

bool Queue::empty(){
    return head->next==NULL;
}

int Queue::front(){
    if (empty()) throw "Queue is empty.";
    return head->next->val;
}

int Queue::back(){
    if (empty()) throw "Queue is empty.";
    return rear->next->val;
}

void Queue::push(int val){
    Node *tmp = new Node;
    tmp->val = val;
    tmp->next = NULL;
    if (empty()){
        head->next = tmp;
        rear->next = tmp;
    } else{
        rear->next->next = tmp;
        rear->next = tmp;
    }
    head->val++;
}

void Queue::pop(){
    if (empty()) throw "Queue is empty.";
    Node *tmp = head->next;
    head->next = tmp->next;
    if (empty()){ //empty(){head->next==NULL}
        rear->next = NULL;
    }
    delete tmp;
    head->val--;
}

int main() {
    int n, val;
    string op;
    Queue queue;
    while (cin >> n) { // while处理多个 case
        while (n -- > 0) {
            cin >> op;
            if (op == "push") {
                cin >> val;
                queue.push(val);
            } else if (op == "pop") {
                if (queue.empty()){
                    cout << "error" << endl;
                }
                else{
                    cout << queue.front() << endl;
                    queue.pop();
                }
            } else if (op == "front") {
                if (queue.empty()) cout << "error\n";
                else cout << queue.front() << endl;
            }
        }
    }
}

// int main(){
//     Queue q1 = {1,2,3,4};
//     cout << q1.front() << endl;
//     Queue q2 = q1;  //拷贝构造函数
//     // 重载赋值运算符
//     // Queue q2;
//     // q2 = q1;
//     q2.pop();
//     cout << q1.front() << endl;
    
//     return 0;
// }
