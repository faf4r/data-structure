//思路讲解：https://www.bilibili.com/video/BV1Bw411H7fW
#include <iostream>
#include <fstream>

using namespace std;

#define MAXSIZE 100
#define inf 65535

typedef char vertexType;
typedef struct {
    vertexType vertex[MAXSIZE];
    int edge[MAXSIZE][MAXSIZE]; //inf无边，否则为权重值
    int vertexNum, edgeNum;
} Graph;

int locate(Graph G, vertexType item) {
    for (int i = 0; i<G.vertexNum; i++) {
        if (G.vertex[i] == item)
            return i;
    }
    return -1;
}

Graph read_Graph(string file_name) {
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
    int i1, i2, weight;
    for (int i = 0; i<G.vertexNum; i++) {
        for (int j = i; j<G.vertexNum; j++) {
            G.edge[i][j] = inf;   //初始化邻接矩阵
            G.edge[j][i] = inf;
        }
    }
    for (int i = 0; i<G.edgeNum; i++) {
        input.get(); input >> v1;
        input.get(); input >> v2;
        input >> weight;
        i1 = locate(G, v1);
        i2 = locate(G, v2);
        G.edge[i1][i2] = weight;
        G.edge[i2][i1] = weight;
    }

    input.close();
    return G;
}

typedef struct {
    int u, v;   //顶点的索引
    int weight;
} Edge;
void miniSpanTree_prim(Graph G, Edge *edge){
    // 每次找一条(u in unreachSet , v in reachSet) 权重最小的边，把u加入到reachSet

    bool reachSet[MAXSIZE];   //标记顶点是否reach，unreach就是它的取反，就不单独设置了
    Edge path[MAXSIZE];       //记录reach和unreach集合之间连接的边的最小值
    
    //初始化，顶点v0初始为reach
    reachSet[0] = true;
    for (int i = 1; i<G.vertexNum; i++)
        reachSet[i] = false;
    for (int i = 0; i<G.vertexNum; i++) {
        path[i].u = i;  //u in unreachSet
        path[i].v = 0;  //v in reachSet 初始为与v0相连
        path[i].weight = G.edge[i][0];
    }
    
    int min;        //(u, v)的最小权值
    int u;          //index of u in unreachSet
    int edge_index = 0; //结果集edge的索引

    //开始正式遍历,实际是while (unreachSet)
    for (int i = 1; i<G.vertexNum; i++) {   //i只作遍历计数用，无实义
        /*1.寻找最小边*/
        min = inf; u = 0;   //初始化一个最小值
        for (int j = 1; j<G.vertexNum; j++) {
            if (!reachSet[j] && path[j].weight<min) {
                min = path[j].weight;
                u = j;
            }
        }

        /*2.找到最小边，将u添加到reachSet，并更新结果集edge。*/
        reachSet[u] = true;
        edge[edge_index++] = path[u];

        /*3.新加入了个u，更新一下path看有没有与u相连的权更小的边*/
        for (int j = 1; j<G.vertexNum; j++) {
            if (!reachSet[j] && G.edge[j][u]<path[j].weight) {
                // (j in unreachSet, u in reachSet)
                // path[j].u = j;  //本身就是这个值
                path[j].v = u;
                path[j].weight = G.edge[j][u];
            }
        }
    }
}

void printMST(Graph G, Edge *edge) {
    cout << "edge\tweight" << endl;
    char u, v;
    for (int i = 0; i<G.vertexNum-1; i++) {
        u = G.vertex[edge[i].u];
        v = G.vertex[edge[i].v];
        cout << u << "  " << v << "\t" << edge[i].weight << endl;
    }
}

int main() {
    Graph G = read_Graph("input.txt");
    Edge edge[MAXSIZE];

    miniSpanTree_prim(G, edge);
    printMST(G, edge);

    return 0;
}
