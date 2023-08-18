#include <iostream>

#define MAXSIZE 100000

using namespace std;

class Queue {
  private:
    int data[MAXSIZE];
    int head, rear;  //因为rear不是拿来取值的（虽然会拿来赋值），所以让rear指向实际末尾值的下一个索引，便于判断空
    bool full;  //只有用数组实现的才会有队满，因为队空或满都是head==rear，所以要加一个专门的flag
  public:
    Queue();
    Queue(std::initializer_list<int> list);
    Queue(Queue &queue);
    void push(int val);
    void pop();
    int front();
    bool empty();
    bool isFull(){return full;}
};

Queue::Queue() {
    head = 0;
    rear = 0;
    full = false;
}

Queue::Queue(std::initializer_list<int> list) {
    if (list.size() > MAXSIZE) throw "out of size.";
    head = 0;
    rear = 0;
    for (auto i=list.begin(); i!=list.end(); i++) {
        push(*i);
    }
}

Queue::Queue(Queue &queue){
    head = 0;
    rear = 0;
    full = false;
    for (int i=queue.head; i!=queue.rear; i=(i+1)%MAXSIZE){
        push(queue.data[i]);
    }
}

void Queue::push(int val) {
    if (full) throw "Queue is full.";
    data[rear] = val;
    rear = (rear + 1) % MAXSIZE;
    if (head == rear) full = true;
}

void Queue::pop() {
    if (empty()) throw "Queue is empty.";
    head = (head + 1) % MAXSIZE;
    if (full) full = false;
}

int Queue::front() {
    if (empty()) throw "Queue is empty.";
    return data[head];
}

bool Queue::empty() {
    return head == rear && !full;
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
                if (queue.empty())
                    cout << "error\n";
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

/*  文心一言问出来的
///! 主要只用了front和rear，然后front==rear的时候才会为空，rear+1==front的时候才是满
///! 这里的rear指的是最后一个元素的位置
#include <iostream>  
using namespace std;  
  
const int MAX_SIZE = 100; // 队列最大容量  
  
class Queue {  
private:  
    int data[MAX_SIZE]; // 存储队列元素的数组  
    int front; // 队头指针  
    int rear; // 队尾指针  
public:  
    Queue() {  
        front = rear = -1; // 初始化队列  
    }  
    bool isEmpty() {  
        return front == rear;  
    }  
    bool isFull() {  
        return (rear + 1) % MAX_SIZE == front; // 判断是否已满  
    }  
    void enqueue(int x) {  
        if (isFull()) {  
            cout << "Queue is full" << endl;  
            return;  
        }  
        rear = (rear + 1) % MAX_SIZE; // 处理大端问题  
        data[rear] = x;  
        if (isEmpty()) {  
            front = rear;  
        }  
    }  
    void dequeue() {  
        if (isEmpty()) {  
            cout << "Queue is empty" << endl;  
            return;  
        }  
        cout << data[front] << " "; // 输出出队元素  
        front = (front + 1) % MAX_SIZE; // 处理大端问题  
    }  
    void display() {  
        if (isEmpty()) {  
            cout << "Queue is empty" << endl;  
            return;  
        }  
        cout << "Queue: ";  
        int i = front;  
        while (i != rear) { // 注意不是 i <= rear，避免重复输出最后一个元素  
            cout << data[i] << " ";  
            i = (i + 1) % MAX_SIZE; // 处理大端问题  
        }  
        cout << endl;  
    }  
};
*/