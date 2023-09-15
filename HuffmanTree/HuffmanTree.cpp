#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define CHARSET_SIZE 128
#define CODE_SIZE 16

typedef struct {
    float weight;           //权重
    int parent, left, right;//节点间关系
} HuffmanTNode;

//PS:索引均从1开始; 空格也会编码
typedef struct {
    char charset[CHARSET_SIZE];         //哈夫曼树中的字符
    char code[CHARSET_SIZE][CODE_SIZE]; //哈弗曼编码
    int n;                              //实际字符数
    HuffmanTNode *tree;                 //哈夫曼树
} HuffmanTree;


void select(HuffmanTNode *tree, int n, int &s1, int &s2){
    //返回tree[1]-tree[n]之间无父母的最小的两个节点s1、s2
    s1 = 0; s2 = 0; //初始化，0是非法结果
    for (int i=1; i<=n; i++){
        if (tree[i].parent)
            continue;   //有父母，已被操作
        if (s1==0)        s1 = i;
        else if (s2==0)   s2 = i;
        else {    //s1,s2都有值，需要比较
            if (tree[s1].weight>tree[i].weight && tree[s1].weight>=tree[s2].weight)         s1 = i;
            else if (tree[s2].weight>tree[i].weight && tree[s2].weight>=tree[s1].weight)    s2 = i;
        }
    }
}

void get_code(HuffmanTNode *tree, int index, char *code){
    //根据哈夫曼树求tree[index]的哈弗曼编码
    HuffmanTNode node=tree[index], parent;
    int i = index;          //遍历哈夫曼树
    char bit;               //用于确定code接下来插入0或1
    int j = CODE_SIZE-1;    //从后往前遍历code数组
    int length = 0;         //哈弗曼编码的长度

    while (node.parent){
        parent = tree[node.parent];
        if (parent.left==i) bit = '0';
        else                bit = '1';
        code[j--] = bit;
        length++;
        i = node.parent;
        node = parent;
    }

    //将哈弗曼编码从后往前移
    for (i=0, j++; j<CODE_SIZE; i++,j++){
        code[i] = code[j];
    }
    for (; i<CODE_SIZE; i++){
        code[i] = 0;
    }
}

HuffmanTree create_HuffmanTree_from_file(string input_file_name){
    ifstream input (input_file_name, ios::in);
    if (!input) {   //文件不存在
        cerr << "Open Huffman_charset.txt error!" << endl;
        exit(-1);
    }

    //从文件读取输入
    HuffmanTree T;
    input >> T.n; input.get();  //处理换行符
    T.tree = new HuffmanTNode[2*T.n-1 +1];    //哈夫曼树节点数为2n-1，但索引从1开始，所以总数加一
    for (int i=1; i<=T.n; i++){
        input >> T.charset[i] >> T.tree[i].weight;
        input.get();            //处理换行符
        //初始化
        T.tree[i].parent = 0;
        T.tree[i].left = 0;
        T.tree[i].right = 0;
        for (int j=0; j<CODE_SIZE; j++){
            T.code[i][j] = 0;
        }
    }
    for (int i=T.n+1; i<=2*T.n-1; i++){ //初始化哈夫曼树非叶子节点
        T.tree[i].parent = 0;
        T.tree[i].left = 0;
        T.tree[i].right = 0;
    }
    input.close();

    //构造哈夫曼树
    for (int i=T.n+1; i<=2*T.n-1; i++){
        int s1, s2;
        select(T.tree, i-1, s1, s2);
        T.tree[s1].parent = i;
        T.tree[s2].parent = i;
        T.tree[i].left = s1;
        T.tree[i].right = s2;
        T.tree[i].weight = T.tree[s1].weight + T.tree[s2].weight;
    }

    //求哈弗曼编码
    for (int i=1; i<=T.n; i++){
        get_code(T.tree, i, T.code[i]);
    }

    return T;
}

void release(HuffmanTree &T){
    delete[] T.tree;
}

void output_Huffman_code(HuffmanTree T, string output_file_name){
    ofstream output(output_file_name, ios::out);
    if (!output) {   //文件不存在
        cerr << "Open Huffman_code.txt error!" << endl;
        exit(-1);
    }

    output << "哈弗曼编码：" << endl;
    for (int i=1; i<=T.n; i++){
        output << "'" << T.charset[i] << "': " << T.code[i] << endl;
    }
    output.close();
}

void encode(HuffmanTree T, string s){
    for (int i=0; i<s.length(); i++){
        for (int j=1; j<=T.n; j++){
            if (T.charset[j] != s[i])
                continue;
            cout << T.code[j];
            break;
        }
    }
}

bool match(char *code, string s, int &index){
    //用于判断该编码是否与串的index位置匹配
    int i=0, j=index;
    while (code[i]){
        if (code[i++] != s[j++])
            return  false;
    }
    index = j;
    return true;
}

void decode(HuffmanTree T, string s){
    int j = 0;
    while (j<s.length()){
        for (int i=1; i<=T.n; i++){
            if (match(T.code[i], s, j)){
                cout << T.charset[i];
                break;
            }
        }
    }
}

int main(){
    HuffmanTree T = create_HuffmanTree_from_file("Huffman_charset.txt");
    output_Huffman_code(T, "Huffman_code.txt");

    cout << "--------------------------" << endl;
    cout << "请选择你要进行的操作：" << endl;
    cout << "1.编码" << endl;
    cout << "2.解码" << endl;
    cout << "0.退出" << endl;
    cout << ">>> ";
    int opt;
    string s;
    while (cin >> opt){
        cin.get();  //处理换行符
        switch (opt)
        {
        case 0: //退出
            release(T);
            exit(0);
            break;
        case 1: //编码
            cout << "请输入待编码内容：";
            cin >> s;
            cout << "编码结果如下：" << endl;
            encode(T, s); cout << endl;
            break;
        case 2: //解码
            cout << "请输入待解码内容：";
            cin >> s;
            cout << "解码结果如下：" << endl;
            decode(T, s); cout << endl;
            break;
        default:
        cout << "非法输入请重新选择！" << endl;
            break;
        }
        cout << "--------------------------" << endl;
        cout << "请选择你要进行的操作：" << endl;
        cout << "1.编码" << endl;
        cout << "2.解码" << endl;
        cout << "0.退出" << endl;
        cout << ">>> ";
    }

    return 0;
}
