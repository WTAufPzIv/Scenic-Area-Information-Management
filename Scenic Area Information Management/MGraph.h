#pragma once
#include <string>
#include "path.h"
#include "Edge.h"
using namespace std;
class MGraph
{
public:
	int verNum;//��������
	int sideNum;//�ߵ�����
	int adj[100][100];//�����ڽӾ���
	string name[100];
	string introduce[100];
	MGraph();
	~MGraph();
	void CreateMGraph1(MGraph *Gp,int ,int ,int ,int);  //��������ͼ���ڽӾ���
	void SetInfo(string, string ,int,int);//���þ�����Ϣ
	void visit(int,pathlist &list);//��������
	void printG();//��ӡ�ڽӾ���
	void DFS(int vex,int visit[], int &index, pathlist &list);//��v����������ȱ�������������·��
	void search(int m);//��ѯ������Ϣ
	void Short(int, int);//�Ͻ�˹�����㷨�����·��
	void Dijkstra(int ,int,int dis[],int vis[]);
	void addVex();
	void deleteVex();
	void addRoad();
	void delRoad();
	void setVer();
	void SetSide();
	void prim();//prim�㷨����С������
};

