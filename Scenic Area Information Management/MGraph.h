#pragma once
#include <string>
#include "path.h"
#include "Edge.h"
using namespace std;
class MGraph
{
public:
	int verNum;//景点数量
	int sideNum;//边的数量
	int adj[100][100];//景点邻接矩阵
	string name[100];
	string introduce[100];
	MGraph();
	~MGraph();
	void CreateMGraph1(MGraph *Gp,int ,int ,int ,int);  //建立无向图的邻接矩阵
	void SetInfo(string, string ,int,int);//设置景区信息
	void visit(int,pathlist &list);//景区导航
	void printG();//打印邻接矩阵
	void DFS(int vex,int visit[], int &index, pathlist &list);//从v出发深度优先遍历并搜索所有路径
	void search(int m);//查询景点信息
	void Short(int, int);//迪杰斯特拉算法求最短路径
	void Dijkstra(int ,int,int dis[],int vis[]);
	void addVex();
	void deleteVex();
	void addRoad();
	void delRoad();
	void setVer();
	void SetSide();
	void prim();//prim算法求最小生成树
};

