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
    //层序遍历创建*完全二叉树*
    if (n==0){
        T = NULL;
        return;
    }
    queue<BiTree> que;
    BiTNode *p = NULL;
    T = new BiTNode(0);
    n--;
    que.push(T);
    while(n>0){    //n是判断节点数是否创建够了
        p = que.front(); que.pop();    //按层序遍历，取出节点
        
        p->left = new BiTNode(0);      //左右孩子都没有创建，所以左孩子直接创建
        n--;                           //每创建一个节点n就要减一
        if (n<=0) break;               //若这个地方只有左节点，就退出
        p->right = new BiTNode(0);     //有右节点，创建
        n--;
        
        que.push(p->left);             //创建的节点要添加到队列用于层序遍历
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
//没有*来表示NULL，所以只能赋值，要提前创建
void assign_full_BiTree(BiTree &T, string s){
    //给已经创建的二叉树通过先序遍历的方式赋值
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

//用*表示NULL
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
    //从字符串读取
    int i = 0; //字符串s从零开始读入
    __load_tree_preOrder(T, s, i);
}

void release(BiTree &T){    //释放内存
    if (!T) return; //T==NULL
    release(T->left);
    release(T->right);
    delete T;
    T = NULL;
}

void inOrderTraversal(BiTree T){
    if (!T){ //T==NULL
        // cout << "*"; //看NULL要不要输出
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
        // cout << "*"; //看NULL要不要输出
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
        // cout << "*"; //看NULL要不要输出
        return;
    }
    postOrderTraversal(T->left);
    postOrderTraversal(T->right);
    cout << T->data;
}

void postOrderTraversal_stack(BiTree T){
    if (!T) return;
    stack<BiTNode *> s;
    BiTNode *cur=T, *pre=NULL;  //cur是当前遍历的节点，pre是上一个访问了的节点
    while (cur || !s.empty()){
        if (cur){
            s.push(cur);
            cur = cur->left;
        } else {
            cur = s.top();  // s.pop(); 这里没有出栈，因为还要判断右子树是否被访问
            if (!cur->right || cur->right==pre){ //当右子树为空或已被访问才访问根节点
                s.pop();    //当前节点要被访问，出栈
                cout << cur->data;  //访问根节点
                pre = cur;  //最近被访问的节点改为当前节点
                cur = NULL; //当前节点已被访问，置空
            } else {    //右子树不为空且未被访问
                //当前节点还不该访问，要先访问右子树，所以不出栈
                cur = cur->right;
            }
        }
    }
    cout << endl;
}

void levelOrderTraversal(BiTree T){
    // if (!T) return;    //可写可不写，在queue里面会判断
    queue<BiTree> que;
    BiTNode *p;
    que.push(T);
    while(!que.empty()){
        p = que.front(); que.pop();
        if(p){
            cout << p->data;   //visit
            que.push(p->left); que.push(p->right); //将下一层的节点入队入队，空指针也可以
        }
    }
}

int find_preOrder(BiTree T, elemType val){  //用栈实现
    //查找前序遍历的访问次序，不存在返回0
    if (!T) return 0;  //树为空，直接返回
    stack<BiTNode *> s;
    int count = 1;  //访问次序从1开始
    BiTNode *p = T;
    while (p || !s.empty()){
        if (p){
            //访问根节点，遍历时的cout替换为判断和count++即可
            if (p->data == val) return count;
            else count++;
            s.push(p);  //根子针进栈， 遍历左子树
            p = p->left;
        } else {    //左子树到头，遍历右子树
            p = s.top(); s.pop();   //退栈
            p = p->right;           //遍历右子树
        }
    };
    return 0; //遍历完也没找到，返回0
}

void __find_inOrder(BiTree T, elemType val, int &count, bool &found){
    //引用保证整个递归时全局可见
    if (!T) return;     //节点为空不操作，返回

    __find_inOrder(T->left, val, count, found); //左子树

    //访问根节点根节点
    if (found) return;  //已经找到目标，后续节点直接返回
    count++;            //还未找到，计数值加一
    if (T->data == val){//找到节点，标记，直接返回
        found = true;
        return;
    }
    __find_inOrder(T->right, val, count, found);//右子树
}
int find_inOrder(BiTree T, elemType val){   //递归实现
    //查找中序遍历的访问次序，不存在返回0
    // if (!T) return 0;    //可写可不写，非空子函数也会返回
    int count = 0;
    bool found = false;
    //用一个递归的子函数来负责运算，这层函数用于封装
    __find_inOrder(T, val, count, found);
    return found ? count : 0;
}

void __find_postOrder(BiTree T, elemType val, int &count, bool &found){
    //引用保证整个递归时全局可见
    if (!T) return;     //节点为空不操作，返回

    __find_postOrder(T->left, val, count, found); //左子树
    __find_postOrder(T->right, val, count, found);//右子树

    //访问根节点根节点
    if (found) return;  //已经找到目标，后续节点直接返回
    count++;            //还未找到，计数值加一
    if (T->data == val){//找到节点，标记，直接返回
        found = true;
        return;
    }
}
int find_postOrder(BiTree T, elemType val){ //递归实现
    //查找后序遍历的访问次序，不存在返回0
    int count = 0;
    bool found = false;
    __find_postOrder(T, val, count, found);
    return found ? count : 0;
}


int main(){
    BiTree T;
    read_tree_preOrder(T); cin.get();   //处理行尾换行符
    // string str;
    // cin >> str;
    // load_tree_preOrder(T, str);

    // inOrderTraversal(T); cout << endl;  //换行
    // preOrderTraversal(T); cout << endl;
    // postOrderTraversal(T); cout << endl;
    // inOrderTraversal_stack(T);
    // preOrderTraversal_stack(T);
    // postOrderTraversal_stack(T);
    // levelOrderTraversal(T);

    char ch;
    int preOrder, inOrder, postOrder;
    cout << "请输入待查询次序的字符：";
    while ((ch=cin.get()) != '#'){
        if (ch=='\n') continue;  //处理换行符
        
        preOrder = find_preOrder(T, ch);
        if (preOrder == 0){
            cout << "字符" << ch << "不在该树中" << endl;
            continue;
        } else{
            cout << "前序遍历："; preOrderTraversal(T); cout << endl;
            cout << "\t访问次序：" << preOrder << endl;
        }
        inOrder = find_inOrder(T, ch);
        cout << "中序遍历："; inOrderTraversal(T); cout << endl;
        cout << "\t访问次序：" << inOrder << endl;
        postOrder = find_postOrder(T, ch);
        cout << "后序遍历："; postOrderTraversal(T); cout << endl;
        cout << "\t访问次序：" << postOrder << endl;

        cout << "请输入待查询次序的字符：";
    }
    

    release(T);

    return 0;
}
