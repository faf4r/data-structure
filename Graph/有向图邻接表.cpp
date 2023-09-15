#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MAXSIZE 100

typedef char vertexType;
typedef struct edgeNode {
    int adj_vertex; //该边指向的顶点的位置索引
    edgeNode *next; //下一个边
    edgeNode(int i): adj_vertex(i), next(NULL) {}
} edgeNode;
typedef struct vertexNode {
    vertexType vertex;  
    edgeNode *first;    //指向第一个边
} vertexNode;
typedef struct {
    vertexNode vertices[MAXSIZE];
    int vertexNum, edgeNum;
} Graph;

int locate(Graph &G, vertexType item) {
    for (int i = 0; i<G.vertexNum; i++) {
        if (G.vertices[i].vertex == item)
            return i;
    }
    return -1;
}

Graph creat_Graph(string file_name) {
    ifstream input(file_name.c_str(), ios::in);
    if (!input) {cout << "open input file error." << endl;  exit(-1);}

    Graph G;
    input >> G.vertexNum >> G.edgeNum;
    //读取顶点
    for (int i = 0; i<G.vertexNum; i++){
        input.get();  //处理空格及换行符
        input >> G.vertices[i].vertex;
    }
    //初始化边
    for (int i = 0; i<G.vertexNum; i++) {
        G.vertices[i].first = NULL;
    }
    //读取边
    char v1, v2;
    int i1, i2;
    for (int i = 0; i<G.edgeNum; i++) {
        input.get(); input >> v1;
        input.get(); input >> v2;
        i1 = locate(G, v1);
        i2 = locate(G, v2);
        //前插法
        edgeNode *p = new edgeNode(i2);
        p->next = G.vertices[i1].first;
        G.vertices[i1].first = p;
    }

    input.close();
    return G;
}

void release(Graph &G) {
    for (int i = 0; i<G.vertexNum; i++) {
        edgeNode *p;
        while (G.vertices[i].first) {
            p = G.vertices[i].first;
            G.vertices[i].first = p->next;
            delete p;
        }
    }
}

void DFS(Graph &G, int i, bool *visited) {
    cout << G.vertices[i].vertex;
    visited[i] = true;
    edgeNode *p = G.vertices[i].first;
    while (p) {
        int j = p->adj_vertex;
        if (!visited[j])
            DFS(G, j, visited);
        p = p->next;
    }
}
void DFStraverse(Graph &G) {
    bool *visited = new bool[G.vertexNum];
    for (int i = 0; i<G.vertexNum; i++)
        visited[i] = false; //初始化visited

    for (int i = 0; i<G.vertexNum; i++) {
        if (!visited[i])
            DFS(G, i, visited);
    }
    delete[] visited;
}

void BFS(Graph &G, int index, bool *visited) {
    queue<int> que;
    que.push(index);
    int i;
    while (!que.empty()) {
        i = que.front(); que.pop();
        if (visited[i])
            continue;
        cout << G.vertices[i].vertex;
        visited[i] = true;
        edgeNode *p = G.vertices[i].first;
        while (p) {
            if (!visited[p->adj_vertex])
                que.push(p->adj_vertex);
            p = p->next;
        }
    }
}
void BFSTraverse(Graph &G) {
    bool *visited = new bool[G.vertexNum];
    for (int i = 0; i<G.vertexNum; i++)
        visited[i] = false; //初始化visited

    for (int i = 0; i<G.vertexNum; i++) {
        if (!visited[i])
            BFS(G, i, visited);
    }
    delete[] visited;
}

int main() {
    Graph G = creat_Graph("input2.txt");
    cout << "DFS: "; DFStraverse(G); cout << endl;
    cout << "BFS: "; BFSTraverse(G); cout << endl;
    release(G);
    return 0;
}
