#include <iostream>

using namespace std;

typedef struct Node {
    int val;
    Node *next;
} Node;

/**
 * @brief 用Iterator迭代器来说实现list的begin和end方法
 * 这个方法可以返回Iterator对象，然后*Iterator读取值，Iterator++到下一个值
 * 使用方法：
 * for (auto it=list.begin(); it!=list.end(); it++){}  //auto == Iterator
 * 
 * 此外，实现了begin和end之后，可以使用for (auto val : list){}来遍历
 */
class Iterator{
private:
    Node * current;
public:
    Iterator(Node *node){
        current = node;
    }
    int& operator*(){  //实现取值
        return current->val;
    }
    Iterator& operator++(){  //实现迭代的++
        current = current->next;
        return *this;  //注意这里返回的是对象本身（this是指针）
    }
    Iterator& operator++(int n){  //后置++
        current = current->next;
        return *this;
    }
    bool operator!=(const Iterator &other) const { //实现迭代判断条件!=
        return current != other.current;
    }
};

class List{
private:
    Node *head, *rear;  //用一个rear便于往后面直接插值
public:
    List();
    List(List &list);
    List(std::initializer_list<int> li);
    ~List();
    void append(int val);
    void insert(int index, int val);
    int size();
    bool empty();
    int operator[](int index);
    void clear();
    void remove(int val);  //删除遇到的第一个val
    void del(int index);   //删除索引index处的值
    Iterator begin();
    Iterator end();
    // 实现了begin和end之后，可以像std::initializer_list<int>那样使用
    // 由此，可以使用for (auto val : list){}来遍历
    void reverse();
};

List::List(){
    head = new Node;
    rear = new Node;
    head->val = 0; //头结点的val用来存储数据个数(size)
    head->next = NULL;
    rear->next =NULL;
}

List::List(List &list){
    head = new Node;
    rear = new Node;
    head->val = 0;
    head->next = NULL;
    rear->next =NULL;
    for (Iterator it=begin(); it!=end(); it++){
        append(*it);
    }
}

List::List(std::initializer_list<int> li){
    head = new Node;
    rear = new Node;
    head->val = 0;
    head->next = NULL;
    rear->next =NULL;
    for (auto it=li.begin(); it!=li.end(); it++){
        append(*it);
    }
}

List::~List(){
    clear();
    delete head, rear;
}

void List::append(int val){
    Node *tmp = new Node;
    tmp->val = val;
    tmp->next = NULL;
    if (empty()){
        head->next = tmp;
        rear->next = tmp;
        head->val++;
    } else{
        rear->next->next = tmp;
        rear->next = tmp;
        head->val++;
    }
    /**   不用rear实现插值
        Node *tmp = new Node;
        tmp->val = val;
        tmp->next = NULL;
        Node *iter = head;
        while (iter->next){
            iter = iter->next;
        }
        iter->next = tmp;
        head->val++;
    */
}

void List::insert(int index, int val){
    if (index>=size()){
        append(val);  //索引超了的话不报错，直接往后append
        return;
    }
    Node *tmp = new Node;
    Node *iter = head;  //用于遍历
    while (index-->0){ //这里取到的是index前一个位置，在这个位置后面插入tmp（索引从0开始的）
        iter = iter->next;
    }
    tmp->val = val;
    tmp->next = iter->next;
    iter->next = tmp;
    head->val++;
}

int List::size(){
    return head->val;
}

bool List::empty(){
    return head->next == NULL;
    // or  head->val==0   or rear->next==NULL;
}

void List::clear(){
    Node *tmp;
    while (head->next)
    {
        tmp = head->next;
        head->next = tmp->next;
        delete tmp;
    }
    head->val = 0;
    rear->next = NULL;
}

int List::operator[](int index){
    Node *tmp = head->next;
    while (index-->0){
        tmp = tmp->next;
    }
    return tmp->val;
}

void List::remove(int val){
    Node *iter=head, *tmp=iter->next;
    while(tmp){  //双指针一起遍历
        if ( ! (tmp->val==val) ){  //注意优先级
            iter = tmp;
            tmp = tmp->next;
            continue;
        }
        iter->next = tmp->next;
        delete tmp;
        head->val--;
        return;
    }
}
void List::del(int index){
    Node *iter=head, *tmp;
    while (index-->0){
        iter = iter->next;  //iter遍历到index上一位
    }
    tmp = iter->next;
    iter->next = tmp->next;
    delete tmp;
    head->val--;
}

Iterator List::begin(){  //如果为空的话，指向的就都是NULL，一般遍历时也不会遍历进去
    return Iterator(head->next);
}
Iterator List::end(){
    return Iterator(NULL); //使用时end是判断的，不会读取值，所以不会用到current->val
}

void List::reverse(){
    if (empty() || head->next->next==NULL) return;  //处理空链表和只有一个元素的的情况情况
    Node *prev=NULL, *current=head->next, *follow=head->next->next;
    rear->next = current;
    while (follow){
        current->next = prev;
        prev = current;
        current = follow;
        follow = follow->next;
    }
    current->next = prev;  //上面循环完current是最后一个值，但是还没指向prev
    head->next = current;
}

int main_test_reverse(){
    List li = {1,2,3,4,5};
    for (auto val : li) cout << val;
    cout << endl;
    li.reverse();
    for (auto val : li) cout << val;
    
    return 0;
}

int main() {
    int n, x,y;
    string op;
    while (cin >>n) {
        List list;
        while (n-->0) {
            cin >> op;
            if (op=="insert"){
                cin >> x >> y;
                list.insert(x, y);
            } else if (op=="delete"){
                cin >> x;
                list.remove(x);
            }
        }
        // for (auto i=0; i<list.size();i++){
        //     cout << list[i] << "  ";
        // }

        // for (auto it=list.begin(); it!=list.end(); it++){
        //     cout << *it << " ";
        // }

        for (auto val : list){
            cout << val << " ";
        }
        if (list.size()){
            cout << endl;
        } else {
            cout << "NULL" << endl;
        }
    }
}
