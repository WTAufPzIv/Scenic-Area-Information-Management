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
	cout << "��������:" << name[m] << endl;
	cout << "�������:" << introduce[m] << endl;
	for (int i = 0; i < verNum; i++) {
		if (adj[m][i] != 0) {
			cout << "���ڵľ���:" << endl;
			cout << "           #" << name[i] << ':' << introduce[i] << "(����" << adj[m][i] << ")" << endl;
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
	visit[vex] = 1;//����ѷ���
	list->verx[index++] = vex;//�õ���ʲ����������
	//�жϽڵ�������
	int flag = 0;
	for (int i = 0; i < verNum; i++) {
		if (visit[i] == 1) {
			flag++;
		}	
	}
	if (flag == verNum) {//��ȫ�����ʣ��������·��
		
		list->next = (pathlist)malloc(sizeof(path));
		for (int i = 0; i < verNum; i++) {
			list->next->verx[i] = list->verx[i];
			cout << name[list->verx[i]] << " -> ";
		}
		list = list->next;
		list->next = NULL;
		cout << endl;
	}
	else {//δȫ������
		
		for (int i = 0; i < verNum; i++) {
			//Ѱ��δ�������ĵ�
			if (visit[i] == 0 && (adj[vex][i] != 0)) {
				//�Ըö���Ϊ��㿪ʼ����
				DFS(i, visit, index, list);//�ݹ����
				visit[i] = 0;
				index--;//������һ�ڵ���Ѱ����·��������
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
	int road[100];//��¼·��
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
		for (int j = 0; j < verNum; j++) {//��ѭ��Ѱ���뵱ǰ�����ڵĵ㲢������̾���
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
	cout << "·���ܳ�Ϊ��" << dis[end] << endl;
}
void MGraph::Short(int m, int k) {
	int dis[100];//��¼��㵽������̳���
	int vis[100];//��¼�ڵ��Ƿ񱻷��ʹ�
	for (int i = 0; i < 100; i++) {
		dis[i] = INF;//��ʼ������Ϊ���ֵINF
	}
	for (int i = 0; i < verNum; i++) {
		vis[i] = 0;
	}
	Dijkstra(m, k, dis, vis);//ʹ�õϽ�˹�����㷨
}
void MGraph::addVex() {
	cout << "ȷ����ӵ�" << verNum << "�ž��㣬�����뾰������" << endl;
	string newname;
	cin >> newname;
	cout << "�����뾰�����" << endl;
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
	cout << "��ӳɹ�������#�ŷ������˵�" << endl;
}
void MGraph::deleteVex() {
	cout << "������Ҫɾ���ľ����ţ�" << endl;
	int deleteN;
	cin >> deleteN;
	if (deleteN < 0 || deleteN >= verNum) {
		cout << "����������" << endl;
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
		cout << "ɾ���ɹ�������#�ŷ�����һ��" << endl;
	}
}
void MGraph::addRoad() {
	cout << "������Ҫ��ӵ�·������������" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "�����˲����ڵľ��㣡����,������#�ŷ���" << endl;
	}
	else {
		if (adj[a][b] != 0) {
			cout << "������������Ѵ��ڵ�·,������#�ŷ���" << endl;
		}
		else {
			cout << "��������룺" << endl;
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
			cout << "�����" << endl;
		}
	}
}
void MGraph::delRoad() {
    cout << "������Ҫɾ����·������������" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "�����˲����ڵľ��㣡����,������#�ŷ���" << endl;
		//goto loop;
	}
	else {
		if (adj[a][b] == 0) {
			cout << "����������䲻���ڵ�·,������#�ŷ���" << endl;
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
			cout << "��ɾ��" << endl;
		}
	}
}
void MGraph::setVer() {
	cout << "������Ҫ�޸ĵľ�����" << endl;
	int n;
	cin >> n;
	if (n < 0 || n >= verNum) {
		cout << "���㲻����" << endl;
	}
	else {
		cout << "��ѡ��Ҫ�޸ĵĶ���:" << endl;
		cout << "1����������" << endl;
		cout << "2��������" << endl;
		int m;
		cin >> m;
		if (m == 1) {
			cout << "�����������ƣ�" << endl;
			string na;
			cin >> na;
			name[n] = na;
		}
		else if (m == 2) {
			cout << "�������¼��" << endl;
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
		cout << "�޸ĳɹ�������#�ŷ������˵�" << endl;
	}
}
void MGraph::SetSide() {
	cout << "������Ҫ�޸ĵ�·������������" << endl;
	int a, b;
	cin >> a >> b;
	if (a < 0 || b < 0 || a >= verNum || b >= verNum) {
		cout << "�����˲����ڵľ��㣡����,������#�ŷ���" << endl;
	}
	else {
		if (adj[a][b] == 0) {
			cout << "����������䲻���ڵ�·,������#�ŷ���" << endl;
		}
		else {
			cout << "�������µľ��룺" << endl;
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
			cout << "�����" << endl;
		}
	}
}
pair<int, int> GetShortestEdge(const vector<vector<int> >& Graph, const vector<bool>& isIncluded)//��ǰ��MST֮�����MST����ĵ��id
{
	int minID = -1;
	int minDist =INF;
	pair<int, int> minEdge;
	for (int i = 0; i < Graph.size(); i++)//iΪMST�ڵĵ�
	{
		if (!isIncluded[i]) continue;//�������MST���棬������
		for (int j = 0; j < Graph.size(); j++) //jΪMST��ĵ�
			if (!isIncluded[j] && Graph[i][j] < minDist) { //�ҵ�����MST�ڵ��Ǿ���MST����ĵ�
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
		pair<int, int> minEdge = GetShortestEdge(Graph, isIncluded); //�ҵ����Ҫ����ı�i��j
		MST.push_back(minEdge); //����
		isIncluded[minEdge.second] = true; //��j���Ϊ�Ѿ�����
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
		//���շ���MST��˳���������
		cout << "����Ҫ����Ĺܵ�" << endl;
		cout << MST[i].first << "->" << MST[i].second << "    " << "���ȣ�" << adj[MST[i].first][MST[i].second] << endl;
		length += adj[MST[i].first][MST[i].second];
	}
	cout << "�ܹ滮���ȣ�" << length << endl;
}