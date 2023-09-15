#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int val;
    struct Node *next;
    Node(int _val){
        val = _val;
        next = nullptr;
    }
} Node;

class Solution
{
private:
    int n;
    int m;
    int length;
    Node *head;

public:
    Solution(){
        head = new Node(0);
        head->next = head;
    }
    Solution(int n_, int m_): n(n_), m(m_) {
        head = new Node(0);
        head->next = head;
        while (n-->0){
            Node *tmp = new Node(n+1);
            tmp->next = head->next;
            head->next = tmp;
            length++;
        }
        n = length;
        display();
        cout << endl;
    }
    ~Solution(){
        while (!empty()){
            Node *tmp = head->next;
            head->next = tmp->next;
            delete tmp;
        }
        delete head;
    }
    bool empty(){
        return head->next == head;
    }
    
    vector<int> solve();

    vector<int> to_vector(){
        vector<int> ret;
        Node *p = head->next;
        while (p != head){
            ret.push_back(p->val);
            p = p->next;
        }
        return ret;
    }

    void display(){
        Node *p = head->next;
        while (p != head){
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }
};


vector<int> Solution::solve(){
    int count = m-1;
    Node *p = head, *tmp;
    while (length >= m){
        //步进m-1
        cout << endl << "?" << endl;
        while (count-->0){
            cout << "count: " << count << " ";
            p = p->next;
            if (p->next = head){
                p = p->next;
            }
        }
        //删除第m个人
        tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        length--;
        count = m-1;
        // display();
    }
    return to_vector();
}


int main(){
    Solution solution{41, 3};
    solution.solve();
    solution.display();
    
    return 0;
}