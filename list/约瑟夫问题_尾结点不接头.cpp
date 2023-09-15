#include <iostream>

using namespace std;


typedef struct Node{
    int val;
    struct Node *next;
    Node(int n){
        val = n;
        next == NULL;
    }
} Node;


int main(){
    int n=41, m=3, length=0;
    Node *tmp, *p;
    Node *head = new Node(0);

    p = head;
    //尾插法，尾结点指向第一个节点
    for (int i=1; i<=n; i++) {
        tmp = new Node(i);
        p->next = tmp;
        tmp->next = head->next;
        length++;
        p = tmp;
    }

    p = head;
    while (length != 1){  //剩一个
        int count = m-1;
        while (count-->0){
            p = p->next;
        }
        tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        length--;

        head->next = p; //head->next可能被删除了，要重新赋值
    }
    
    p = head->next;
    do {
        cout << p->val << " ";
        p = p->next;
    } while (p != head->next);
    cout << endl;

    //从第二个开始释放
    p = head->next;
    tmp = p->next;
    while (p!=tmp){
        p->next = tmp->next;
        delete tmp;
        tmp = p->next;
    }
    delete head->next;
    delete head;
    
    return 0;
}