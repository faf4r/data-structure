#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

typedef char elemType;
typedef struct BiTNode{
    elemType data;
    BiTNode *left, *right;
    BiTNode(elemType val): data(val), left(NULL), right(NULL) {}
} BiTNode, *BiTree;

void create_full_BiTree(BiTree &T, int n){
    //�����������*��ȫ������*
    if (n==0){
        T = NULL;
        return;
    }
    queue<BiTree> que;
    BiTNode *p = NULL;
    T = new BiTNode(0);
    n--;
    que.push(T);
    while(n>0){    //n���жϽڵ����Ƿ񴴽�����
        p = que.front(); que.pop();    //�����������ȡ���ڵ�
        
        p->left = new BiTNode(0);      //���Һ��Ӷ�û�д�������������ֱ�Ӵ���
        n--;                           //ÿ����һ���ڵ�n��Ҫ��һ
        if (n<=0) break;               //������ط�ֻ����ڵ㣬���˳�
        p->right = new BiTNode(0);     //���ҽڵ㣬����
        n--;
        
        que.push(p->left);             //�����Ľڵ�Ҫ��ӵ��������ڲ������
        que.push(p->right);
    }
}

void __preOrder_assign(BiTree T, string &s, int &i){
    if (!T){ //T==NULL
        return;
    }
    T->data = s[i++];
    __preOrder_assign(T->left, s, i);
    __preOrder_assign(T->right, s, i);
}
//û��*����ʾNULL������ֻ�ܸ�ֵ��Ҫ��ǰ����
void assign_full_BiTree(BiTree &T, string s){
    //���Ѿ������Ķ�����ͨ����������ķ�ʽ��ֵ
    int i = 0;
    __preOrder_assign(T, s, i);
}

void read_tree_preOrder(BiTree &T){
    char ch = cin.get();
    if (ch=='*'){
        T = NULL;
        return ;
    }
    T = new BiTNode(ch);
    read_tree_preOrder(T->left);
    read_tree_preOrder(T->right);
}

//��*��ʾNULL
void __load_tree_preOrder(BiTree &T, string &s, int &i){
    if(s[i]=='*'){
        T = NULL;
        i++;
        return;
    }
    T = new BiTNode(s[i++]);
    __load_tree_preOrder(T->left, s, i);
    __load_tree_preOrder(T->right, s, i);
}
void load_tree_preOrder(BiTree &T, string s){
    //���ַ�����ȡ
    int i = 0; //�ַ���s���㿪ʼ����
    __load_tree_preOrder(T, s, i);
}

void release(BiTree &T){    //�ͷ��ڴ�
    if (!T) return; //T==NULL
    release(T->left);
    release(T->right);
    delete T;
    T = NULL;
}

void inOrderTraversal(BiTree T){
    if (!T){ //T==NULL
        // cout << "*"; //��NULLҪ��Ҫ���
        return;
    }
    inOrderTraversal(T->left);
    cout << T->data;
    inOrderTraversal(T->right);
}

void inOrderTraversal_stack(BiTree T){
    if (!T) return;
    stack<BiTNode *> s;
    BiTNode *p = T;
    while (p || !s.empty()){
        if (p){
            s.push(p);
            p = p->left;
        } else {
            p = s.top(); s.pop();
            cout << p->data;
            p = p->right;
        }
    }
    cout << endl;
}

void preOrderTraversal(BiTree T){
    if (!T){ //T==NULL
        // cout << "*"; //��NULLҪ��Ҫ���
        return;
    }
    cout << T->data;
    preOrderTraversal(T->left);
    preOrderTraversal(T->right);
}

void preOrderTraversal_stack(BiTree T){
    if (!T) return;
    stack<BiTNode *> s;
    BiTNode *p = T;
    while (p || !s.empty()){
        if (p){
            cout << p->data;
            s.push(p);
            p = p->left;
        } else {
            p = s.top(); s.pop();
            p = p->right;
        }
    }
    cout << endl;
}

void postOrderTraversal(BiTree T){
    if (!T){ //T==NULL
        // cout << "*"; //��NULLҪ��Ҫ���
        return;
    }
    postOrderTraversal(T->left);
    postOrderTraversal(T->right);
    cout << T->data;
}

void postOrderTraversal_stack(BiTree T){
    if (!T) return;
    stack<BiTNode *> s;
    BiTNode *cur=T, *pre=NULL;  //cur�ǵ�ǰ�����Ľڵ㣬pre����һ�������˵Ľڵ�
    while (cur || !s.empty()){
        if (cur){
            s.push(cur);
            cur = cur->left;
        } else {
            cur = s.top();  // s.pop(); ����û�г�ջ����Ϊ��Ҫ�ж��������Ƿ񱻷���
            if (!cur->right || cur->right==pre){ //��������Ϊ�ջ��ѱ����ʲŷ��ʸ��ڵ�
                s.pop();    //��ǰ�ڵ�Ҫ�����ʣ���ջ
                cout << cur->data;  //���ʸ��ڵ�
                pre = cur;  //��������ʵĽڵ��Ϊ��ǰ�ڵ�
                cur = NULL; //��ǰ�ڵ��ѱ����ʣ��ÿ�
            } else {    //��������Ϊ����δ������
                //��ǰ�ڵ㻹���÷��ʣ�Ҫ�ȷ��������������Բ���ջ
                cur = cur->right;
            }
        }
    }
    cout << endl;
}

void levelOrderTraversal(BiTree T){
    // if (!T) return;    //��д�ɲ�д����queue������ж�
    queue<BiTree> que;
    BiTNode *p;
    que.push(T);
    while(!que.empty()){
        p = que.front(); que.pop();
        if(p){
            cout << p->data;   //visit
            que.push(p->left); que.push(p->right); //����һ��Ľڵ������ӣ���ָ��Ҳ����
        }
    }
}

int find_preOrder(BiTree T, elemType val){  //��ջʵ��
    //����ǰ������ķ��ʴ��򣬲����ڷ���0
    if (!T) return 0;  //��Ϊ�գ�ֱ�ӷ���
    stack<BiTNode *> s;
    int count = 1;  //���ʴ����1��ʼ
    BiTNode *p = T;
    while (p || !s.empty()){
        if (p){
            //���ʸ��ڵ㣬����ʱ��cout�滻Ϊ�жϺ�count++����
            if (p->data == val) return count;
            else count++;
            s.push(p);  //�������ջ�� ����������
            p = p->left;
        } else {    //��������ͷ������������
            p = s.top(); s.pop();   //��ջ
            p = p->right;           //����������
        }
    };
    return 0; //������Ҳû�ҵ�������0
}

void __find_inOrder(BiTree T, elemType val, int &count, bool &found){
    //���ñ�֤�����ݹ�ʱȫ�ֿɼ�
    if (!T) return;     //�ڵ�Ϊ�ղ�����������

    __find_inOrder(T->left, val, count, found); //������

    //���ʸ��ڵ���ڵ�
    if (found) return;  //�Ѿ��ҵ�Ŀ�꣬�����ڵ�ֱ�ӷ���
    count++;            //��δ�ҵ�������ֵ��һ
    if (T->data == val){//�ҵ��ڵ㣬��ǣ�ֱ�ӷ���
        found = true;
        return;
    }
    __find_inOrder(T->right, val, count, found);//������
}
int find_inOrder(BiTree T, elemType val){   //�ݹ�ʵ��
    //������������ķ��ʴ��򣬲����ڷ���0
    // if (!T) return 0;    //��д�ɲ�д���ǿ��Ӻ���Ҳ�᷵��
    int count = 0;
    bool found = false;
    //��һ���ݹ���Ӻ������������㣬��㺯�����ڷ�װ
    __find_inOrder(T, val, count, found);
    return found ? count : 0;
}

void __find_postOrder(BiTree T, elemType val, int &count, bool &found){
    //���ñ�֤�����ݹ�ʱȫ�ֿɼ�
    if (!T) return;     //�ڵ�Ϊ�ղ�����������

    __find_postOrder(T->left, val, count, found); //������
    __find_postOrder(T->right, val, count, found);//������

    //���ʸ��ڵ���ڵ�
    if (found) return;  //�Ѿ��ҵ�Ŀ�꣬�����ڵ�ֱ�ӷ���
    count++;            //��δ�ҵ�������ֵ��һ
    if (T->data == val){//�ҵ��ڵ㣬��ǣ�ֱ�ӷ���
        found = true;
        return;
    }
}
int find_postOrder(BiTree T, elemType val){ //�ݹ�ʵ��
    //���Һ�������ķ��ʴ��򣬲����ڷ���0
    int count = 0;
    bool found = false;
    __find_postOrder(T, val, count, found);
    return found ? count : 0;
}


int main(){
    BiTree T;
    read_tree_preOrder(T); cin.get();   //������β���з�
    // string str;
    // cin >> str;
    // load_tree_preOrder(T, str);

    // inOrderTraversal(T); cout << endl;  //����
    // preOrderTraversal(T); cout << endl;
    // postOrderTraversal(T); cout << endl;
    // inOrderTraversal_stack(T);
    // preOrderTraversal_stack(T);
    // postOrderTraversal_stack(T);
    // levelOrderTraversal(T);

    char ch;
    int preOrder, inOrder, postOrder;
    cout << "���������ѯ������ַ���";
    while ((ch=cin.get()) != '#'){
        if (ch=='\n') continue;  //�����з�
        
        preOrder = find_preOrder(T, ch);
        if (preOrder == 0){
            cout << "�ַ�" << ch << "���ڸ�����" << endl;
            continue;
        } else{
            cout << "ǰ�������"; preOrderTraversal(T); cout << endl;
            cout << "\t���ʴ���" << preOrder << endl;
        }
        inOrder = find_inOrder(T, ch);
        cout << "���������"; inOrderTraversal(T); cout << endl;
        cout << "\t���ʴ���" << inOrder << endl;
        postOrder = find_postOrder(T, ch);
        cout << "���������"; postOrderTraversal(T); cout << endl;
        cout << "\t���ʴ���" << postOrder << endl;

        cout << "���������ѯ������ַ���";
    }
    

    release(T);

    return 0;
}
