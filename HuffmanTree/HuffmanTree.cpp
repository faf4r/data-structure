#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define CHARSET_SIZE 128
#define CODE_SIZE 16

typedef struct {
    float weight;           //Ȩ��
    int parent, left, right;//�ڵ���ϵ
} HuffmanTNode;

//PS:��������1��ʼ; �ո�Ҳ�����
typedef struct {
    char charset[CHARSET_SIZE];         //���������е��ַ�
    char code[CHARSET_SIZE][CODE_SIZE]; //����������
    int n;                              //ʵ���ַ���
    HuffmanTNode *tree;                 //��������
} HuffmanTree;


void select(HuffmanTNode *tree, int n, int &s1, int &s2){
    //����tree[1]-tree[n]֮���޸�ĸ����С�������ڵ�s1��s2
    s1 = 0; s2 = 0; //��ʼ����0�ǷǷ����
    for (int i=1; i<=n; i++){
        if (tree[i].parent)
            continue;   //�и�ĸ���ѱ�����
        if (s1==0)        s1 = i;
        else if (s2==0)   s2 = i;
        else {    //s1,s2����ֵ����Ҫ�Ƚ�
            if (tree[s1].weight>tree[i].weight && tree[s1].weight>=tree[s2].weight)         s1 = i;
            else if (tree[s2].weight>tree[i].weight && tree[s2].weight>=tree[s1].weight)    s2 = i;
        }
    }
}

void get_code(HuffmanTNode *tree, int index, char *code){
    //���ݹ���������tree[index]�Ĺ���������
    HuffmanTNode node=tree[index], parent;
    int i = index;          //������������
    char bit;               //����ȷ��code����������0��1
    int j = CODE_SIZE-1;    //�Ӻ���ǰ����code����
    int length = 0;         //����������ĳ���

    while (node.parent){
        parent = tree[node.parent];
        if (parent.left==i) bit = '0';
        else                bit = '1';
        code[j--] = bit;
        length++;
        i = node.parent;
        node = parent;
    }

    //������������Ӻ���ǰ��
    for (i=0, j++; j<CODE_SIZE; i++,j++){
        code[i] = code[j];
    }
    for (; i<CODE_SIZE; i++){
        code[i] = 0;
    }
}

HuffmanTree create_HuffmanTree_from_file(string input_file_name){
    ifstream input (input_file_name, ios::in);
    if (!input) {   //�ļ�������
        cerr << "Open Huffman_charset.txt error!" << endl;
        exit(-1);
    }

    //���ļ���ȡ����
    HuffmanTree T;
    input >> T.n; input.get();  //�����з�
    T.tree = new HuffmanTNode[2*T.n-1 +1];    //���������ڵ���Ϊ2n-1����������1��ʼ������������һ
    for (int i=1; i<=T.n; i++){
        input >> T.charset[i] >> T.tree[i].weight;
        input.get();            //�����з�
        //��ʼ��
        T.tree[i].parent = 0;
        T.tree[i].left = 0;
        T.tree[i].right = 0;
        for (int j=0; j<CODE_SIZE; j++){
            T.code[i][j] = 0;
        }
    }
    for (int i=T.n+1; i<=2*T.n-1; i++){ //��ʼ������������Ҷ�ӽڵ�
        T.tree[i].parent = 0;
        T.tree[i].left = 0;
        T.tree[i].right = 0;
    }
    input.close();

    //�����������
    for (int i=T.n+1; i<=2*T.n-1; i++){
        int s1, s2;
        select(T.tree, i-1, s1, s2);
        T.tree[s1].parent = i;
        T.tree[s2].parent = i;
        T.tree[i].left = s1;
        T.tree[i].right = s2;
        T.tree[i].weight = T.tree[s1].weight + T.tree[s2].weight;
    }

    //�����������
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
    if (!output) {   //�ļ�������
        cerr << "Open Huffman_code.txt error!" << endl;
        exit(-1);
    }

    output << "���������룺" << endl;
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
    //�����жϸñ����Ƿ��봮��indexλ��ƥ��
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
    cout << "��ѡ����Ҫ���еĲ�����" << endl;
    cout << "1.����" << endl;
    cout << "2.����" << endl;
    cout << "0.�˳�" << endl;
    cout << ">>> ";
    int opt;
    string s;
    while (cin >> opt){
        cin.get();  //�����з�
        switch (opt)
        {
        case 0: //�˳�
            release(T);
            exit(0);
            break;
        case 1: //����
            cout << "��������������ݣ�";
            cin >> s;
            cout << "���������£�" << endl;
            encode(T, s); cout << endl;
            break;
        case 2: //����
            cout << "��������������ݣ�";
            cin >> s;
            cout << "���������£�" << endl;
            decode(T, s); cout << endl;
            break;
        default:
        cout << "�Ƿ�����������ѡ��" << endl;
            break;
        }
        cout << "--------------------------" << endl;
        cout << "��ѡ����Ҫ���еĲ�����" << endl;
        cout << "1.����" << endl;
        cout << "2.����" << endl;
        cout << "0.�˳�" << endl;
        cout << ">>> ";
    }

    return 0;
}
