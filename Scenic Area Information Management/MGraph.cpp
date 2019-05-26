#include "pch.h"
#include "MGraph.h"
#include <fstream>
#include <string>
#include<iostream>
#include<vector>
#define max 10000
#define INF 1 << 30
using namespace std;
MGraph::MGraph()
{
	verNum = 0;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			adj[i][j] = 0;
}



MGraph::~MGraph()
{
}
void MGraph::CreateMGraph1(MGraph *Gp,int num,int n,int m,int side)
{
	verNum = num;
	Gp->adj[n][m] = side;
	Gp->adj[m][n] = side;
}
void MGraph::search(int m) {
	cout << "景区名称:" << name[m] << endl;
	cout << "景区简介:" << introduce[m] << endl;
	for (int i = 0; i < verNum; i++) {
		if (adj[m][i] != 0) {
			cout << "相邻的景点:" << endl;
			cout << "           #" << name[i] << ':' << introduce[i] << "(距离" << adj[m][i] << ")" << endl;
		}
	}
}
void MGraph::SetInfo(string a, string b,int i,int num) {
	name[i] = a;
	introduce[i] = b;
	sideNum = num;
}
void MGraph::printG() {
	for (int i = 0; i < verNum; i++) {
		for (int j = 0; j < verNum; j++) {
			cout << adj[i][j] << ' ';
		}
		cout << endl;
	}
}
void MGraph::DFS(int vex, int visit[], int &index, pathlist &list) {
	visit[vex] = 1;//起点已访问
	list->verx[index++] = vex;//该点访问并入遍历链表
	//判断节点访问情况
	int flag = 0;
	for (int i = 0; i < verNum; i++) {
		if (visit[i] == 1) {
			flag++;
		}	
	}
	if (flag == verNum) {//已全部访问，保存遍历路径
		
		list->next = (pathlist)malloc(sizeof(path));
		for (int i = 0; i < verNum; i++) {
			list->next->verx[i] = list->verx[i];
			cout << name[list->verx[i]] << " -> ";
		}
		list = list->next;
		list->next = NULL;
		cout << endl;
	}
	else {//未全部访问
		
		for (int i = 0; i < verNum; i++) {
			//寻找未遍历过的点
			if (visit[i] == 0 && (adj[vex][i] != 0)) {
				//以该顶点为起点开始遍历
				DFS(i, visit, index, list);//递归调用
				visit[i] = 0;
				index--;//返回上一节点另寻遍历路径，回溯
			}
		}
	}
}
void MGraph::visit(int a,pathlist &list) {
	int index = 0;
	int visit[100];
	for (int i = 0; i < 100; i++) {
		visit[i] = 0;
	}
	DFS(a, visit, index, list);
}
void MGraph::Dijkstra(int start, int end, int dis[],int vis[]) {
	dis[start] = 0;
	int road[100];//记录路径
	for (int i = 0; i < 100; i++) {
		road[i] = -1;
	}
	for (int i = 0; i < verNum; i++) {
		int min = INF;
		int minmark;
		for (int j = 0; j < verNum; j++) {
			if (vis[j] == 0 && dis[j] <= min) {
				min = dis[j];
				minmark = j;
			}
		}
		
		vis[minmark] = 1;
		for (int j = 0; j < verNum; j++) {//此循环寻找与当前点相邻的点并更新最短距离
			if (adj[minmark][j] != 0) {
				if (vis[j] == 0 && dis[j] >= dis[minmark] + adj[minmark][j]) {
					dis[j] = dis[minmark] + adj[minmark][j];
					road[j] = minmark;
				}
			}
		}
	}
	int flag[100];
	for (int i = 0; i < 100; i++) {
		flag[i] = -1;
	}
	flag[0] = end;
	int x = 1;
	int a = end;
	while (1) {
		if (a == start) {
			flag[x - 1] = start;
			break;
		}
		flag[x] = road[a];
		a = road[a];
		x++;
	}
	for (x = x - 1; x >= 0; x--) {
		if (x > 0) {
			cout << name[flag[x]] << " -> ";
		}
		else if (x == 0) {
			cout << name[flag[x]] << endl;
		}
	}
	cout << "路程总长为：" << dis[end] << endl;
}
void MGraph::Short(int m, int k) {
	int dis[100];//记录起点到各点最短长度
	int vis[100];//记录节点是否被访问过
	for (int i = 0; i < 100; i++) {
		dis[i] = INF;//初始化长度为最大值INF
	}
	for (int i = 0; i < verNum; i++) {
		vis[i] = 0;
	}
	Dijkstra(m, k, dis, vis);//使用迪杰斯特拉算法
}
void MGraph::addVex() {
	cout << "确定添加第" << verNum << "号景点，请输入景点名称" << endl;
	string newname;
	cin >> newname;
	cout << "请输入景点介绍" << endl;
	string newInfo;
	cin >> newInfo;
	this->introduce[verNum] = newInfo;
	this->name[verNum] = newname;
	this->verNum = this->verNum + 1;
	ofstream file;
	file.open("info.txt", ios::out);
	file << this->verNum << endl;
	for (int i = 0; i < this->verNum; i++) {
		file << i << endl;
		file << this->name[i] << endl;
		file << this->introduce[i] << endl;
	}
	file.close();
	cout << "添加成功，输入#号返回主菜单" << endl;
}
void MGraph::deleteVex() {
	cout << "请输入要删除的景点编号：" << endl;
	int deleteN;
	cin >> deleteN;
	if (deleteN < 0 || deleteN >= verNum) {
		cout << "景区不存在" << endl;
	}
	else {
		this->verNum = this->verNum - 1;
		ofstream file;
		file.open("info.txt", ios::out);
		file << this->verNum << endl;
		for (int i = 0; i < this->verNum; i++) {
			if (i != deleteN) {
				file << i << endl;
				file << this->name[i] << endl;
				file << this->introduce[i] << endl;
			}
		}
		file.close();
		for (int i = 0; i < verNum; i++) {
			adj[deleteN][i] = 0;
			adj[i][deleteN] = 0;
		}
		ofstream file1;
		file1.open("road.txt", ios::out);
		int flag = 1;
		for (int i = 0; i < verNum; i++) {
			for (int j = 0; j < flag; j++) {
				if (adj[i][j] != 0) {
					file1 << i << ' ' << j << ' ' << adj[i][j] << endl;
				}
			}
			flag++;
		}
		file1 << 0 << ' ' << 0 << ' ' << 0;
		cout << "删除成功，输入#号返回上一级" << endl;
	}
}
void MGraph::addRoad() {
	cout << "请输入要添加道路的两个景点编号" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "输入了不存在的景点！！！,请输入#号返回" << endl;
	}
	else {
		if (adj[a][b] != 0) {
			cout << "这两个景点间已存在道路,请输入#号返回" << endl;
		}
		else {
			cout << "请输入距离：" << endl;
			int dis;
			cin >> dis;
				adj[a][b] = dis;
				adj[b][a] = dis;
			ofstream file1;
			file1.open("road.txt", ios::out);
			int flag = 1;
			for (int i = 0; i < verNum; i++) {
				for (int j = 0; j < flag; j++) {
					if (adj[i][j] != 0) {
						file1 << i << ' ' << j << ' ' << adj[i][j] << endl;
					}
				}
				flag++;
			}
			file1 << 0 << ' ' << 0 << ' ' << 0;
			cout << "已添加" << endl;
		}
	}
}
void MGraph::delRoad() {
    cout << "请输入要删除道路的两个景点编号" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "输入了不存在的景点！！！,请输入#号返回" << endl;
		//goto loop;
	}
	else {
		if (adj[a][b] == 0) {
			cout << "这两个景点间不存在道路,请输入#号返回" << endl;
			//goto loop;
		}
		else {
			adj[a][b] = 0;
			adj[b][a] = 0;
			ofstream file1;
			file1.open("road.txt", ios::out);
			int flag = 1;
			for (int i = 0; i < verNum; i++) {
				for (int j = 0; j < flag; j++) {
					if (adj[i][j] != 0) {
						file1 << i << ' ' << j << ' ' << adj[i][j] << endl;
					}
				}
				flag++;
			}
			file1 << 0 << ' ' << 0 << ' ' << 0;
			cout << "已删除" << endl;
		}
	}
}
void MGraph::setVer() {
	cout << "请输入要修改的景点编号" << endl;
	int n;
	cin >> n;
	if (n < 0 || n >= verNum) {
		cout << "景点不存在" << endl;
	}
	else {
		cout << "请选择要修改的对象:" << endl;
		cout << "1、景点名称" << endl;
		cout << "2、景点简介" << endl;
		int m;
		cin >> m;
		if (m == 1) {
			cout << "请输入新名称：" << endl;
			string na;
			cin >> na;
			name[n] = na;
		}
		else if (m == 2) {
			cout << "请输入新简介" << endl;
			string ins;
			cin >> ins;
			introduce[n] = ins;
		}
		ofstream file;
		file.open("info.txt", ios::out);
		file << this->verNum << endl;
		for (int i = 0; i < this->verNum; i++) {
			file << i << endl;
			file << this->name[i] << endl;
			file << this->introduce[i] << endl;
		}
		file.close();
		cout << "修改成功，输入#号返回主菜单" << endl;
	}
}
void MGraph::SetSide() {
	cout << "请输入要修改道路的两个景点编号" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "输入了不存在的景点！！！,请输入#号返回" << endl;
	}
	else {
		if (adj[a][b] == 0) {
			cout << "这两个景点间不存在道路,请输入#号返回" << endl;
		}
		else {
			cout << "请输入新的距离：" << endl;
			int dis;
			cin >> dis;
			adj[a][b] = dis;
			adj[b][a] = dis;
			ofstream file1;
			file1.open("road.txt", ios::out);
			int flag = 1;
			for (int i = 0; i < verNum; i++) {
				for (int j = 0; j < flag; j++) {
					if (adj[i][j] != 0) {
						file1 << i << ' ' << j << ' ' << adj[i][j] << endl;
					}
				}
				flag++;
			}
			file1 << 0 << ' ' << 0 << ' ' << 0;
			cout << "已添加" << endl;
		}
	}
}
pair<int, int> GetShortestEdge(const vector<vector<int> >& Graph, const vector<bool>& isIncluded)//求当前在MST之外距离MST最近的点的id
{
	int minID = -1;
	int minDist =INF;
	pair<int, int> minEdge;
	for (int i = 0; i < Graph.size(); i++)//i为MST内的点
	{
		if (!isIncluded[i]) continue;//如果不在MST里面，则跳过
		for (int j = 0; j < Graph.size(); j++) //j为MST外的点
			if (!isIncluded[j] && Graph[i][j] < minDist) { //找到不在MST内但是距离MST最近的点
				minID = j;
				minDist = Graph[i][j];
				minEdge = make_pair(i, j);
			}
	}
	return minEdge;
}
vector<pair<int, int> > Prim(const vector<vector<int> >& Graph, vector<bool>& isIncluded) {
	vector<pair<int, int> > MST;
	isIncluded[0] = true;
	//MST.push_back();
	for (int i = 1; i < Graph.size(); i++) {
		pair<int, int> minEdge = GetShortestEdge(Graph, isIncluded); //找到这次要放入的边i，j
		MST.push_back(minEdge); //放入
		isIncluded[minEdge.second] = true; //将j标记为已经放入
	}
	return MST;
}

void addEdge(const int& startP, const int& endP, const int& weight, vector<vector<int> >& Graph)
{
	Graph[startP][endP] = weight;
	Graph[endP][startP] = weight;
}
void MGraph::prim() {
	int vertex_num = verNum;
	vector<vector<int> > Graph(vertex_num, vector<int>(vertex_num, INF));
	for (int i = 0; i < verNum; i++) {
		for (int j = 0; j < verNum; j++) {
			if (adj[i][j] != 0) {
				addEdge(i, j, adj[i][j], Graph);
			}
		}
	}
	vector<bool> isIncluded(vertex_num, false);
	vector<pair<int, int> >  MST = Prim(Graph, isIncluded);
	int length = 0;
	for (int i = 0; i < MST.size(); i++) {
		//按照放入MST的顺序依次输出
		cout << "所需要铺设的管道" << endl;
		cout << MST[i].first << "->" << MST[i].second << "    " << "长度：" << adj[MST[i].first][MST[i].second] << endl;
		length += adj[MST[i].first][MST[i].second];
	}
	cout << "总规划长度：" << length << endl;
}