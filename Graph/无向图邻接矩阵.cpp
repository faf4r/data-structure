#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MAXSIZE 100

typedef char vertexType;
typedef struct {
    vertexType vertex[MAXSIZE];
    int edge[MAXSIZE][MAXSIZE];
    int vertexNum, edgeNum;
} Graph;

int locate(Graph &G, vertexType item) {
    for (int i = 0; i<G.vertexNum; i++) {
        if (G.vertex[i] == item)
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
        input >> G.vertex[i];
    }

    //读取边
    char v1, v2;
    int i1, i2;
    for (int i = 0; i<G.vertexNum; i++) {
        for (int j = i; j<G.vertexNum; j++) {
            G.edge[i][j] = 0;   //初始化邻接矩阵
            G.edge[j][i] = 0;
        }
    }
    for (int i = 0; i<G.edgeNum; i++) {
        input.get(); input >> v1;
        input.get(); input >> v2;
        i1 = locate(G, v1);
        i2 = locate(G, v2);
        G.edge[i1][i2] = 1;
        G.edge[i2][i1] = 1;
    }

    input.close();
    return G;
}

void DFS(Graph &G, int i, bool *visited) {
    cout << G.vertex[i];
    visited[i] = true;
    for (int j = 0; j<G.vertexNum; j++) {
        if (G.edge[i][j] && !visited[j])
            DFS(G, j, visited);
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
        cout << G.vertex[i];
        visited[i] = true;
        for (int j = 0; j<G.vertexNum; j++) {
            if (G.edge[i][j] && !visited[j])
                que.push(j);
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
    Graph G = creat_Graph("input1.txt");
    cout << "DFS: "; DFStraverse(G); cout << endl;
    cout << "BFS: "; BFSTraverse(G); cout << endl;
    return 0;
}
