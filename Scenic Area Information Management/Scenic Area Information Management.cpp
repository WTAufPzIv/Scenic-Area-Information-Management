// Scenic Area Information Management.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "MGraph.h"
#include "path.h"
#include<sstream> 
#include "Edge.h"
using namespace std;
bool AllisNum(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
int main()
{
	MGraph grph;
	pathlist list;
	ifstream infile;
	ifstream infile1;
	infile.open("info.txt",ios::in);
	infile1.open("road.txt", ios::in);
	string *name;//景点数组
	string *introduce;//景区介绍数组
	int **ver;//顶点数组
	int *side;//边数组
	int flag;//统计路的数量
	int num;//景点数量
	assert(infile.is_open());//如果打开文件失败，输出错误信息
	while (!infile.eof()) {
		int i;
		infile >> num;
		name = new string[num];
		introduce = new string[num];
		while (1) {
			infile >> i;
			infile >> name[i];
			infile >> introduce[i];
			//cout << num << i <<name[i]<< introduce[i];
			if (i == num-1)
				break;
		}
		break;
	}
	int arrlen = num * (num - 1) / 2;  //已知顶点数量求最大边数
	ver = new int*[arrlen];
	for (int i = 0; i < arrlen; i++)   //为指针数组的每个元素分配一个数组
		ver[i] = new int[2];
	side = new int[arrlen];
	 flag = 0;
	while (!infile1.eof()) {
		infile1 >> ver[flag][0] >> ver[flag][1];
		infile1 >> side[flag];
		//cout << ver[flag][0] << ver[flag][1] << side[flag] << endl;
		flag++;
	}
	cout << flag << endl;
	for (int i = 0; i < flag; i++) {
		grph.CreateMGraph1(&grph, num, ver[i][0], ver[i][1], side[i]);
	}
	for (int i = 0; i < num; i++) {
		grph.SetInfo(name[i], introduce[i], i, flag-1);
	}

	

	infile.close();
	grph.printG();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "          ----------------------------------欢迎使用景区自助服务系统----------------------------------" << endl;
	cout << endl;
	cout << "                                                   *1:查询景点" << endl;
	cout << "                                                   *2:景点导航" << endl;
	cout << "                                                   *3:快速到达" << endl;
	cout << "                                                   *4:景区建设(管理)" << endl;
	int id;
	cin >> id;
	if (id == 1) {
		int m;
		system("cls");
		cout << "请输入您要查询的景点编号(输入#号返回主菜单):" << endl;
		string n;
		while (cin >> n) {
			if (n == "#") {
				system("cls");
				main();
			}
			else if (AllisNum(n)){
				std::istringstream is(n);
				is >> m;
				if (m >= grph.verNum) {
					cout << "景区不存在请重新输入!!!" << endl;
				}
				else {
					grph.search(m);
				}
			}
			else {
				cout << "不合法的输入!!!" << endl;
			}
		}
	}
	else if (id == 2) {
		int m;
		system("cls");
		//cout << "请输入您所在的景点编号(输入#号返回主菜单):" << endl;
		string n;
		while (1) {
			cout << "请输入您所在的景点编号(输入#号返回主菜单):" << endl;
			cin >> n;
			if (n == "#") {
				system("cls");
				main();
			}
			else if (AllisNum(n)) {
				std::istringstream is(n);
				is >> m;
				if (m >= num) {
					cout << "景区不存在请重新输入!!!" << endl;
				}
				else {
					cout << "从您所在位置出发所有导航路线路线:" << endl;
					list = (pathlist)malloc(sizeof(path));
					grph.visit(m,list);
				}
			}
			else {
				cout << "不合法的输入!!!" << endl;
			}
		}
	}
	else if (id == 3) {
		int m;
		int k;
		system("cls");
		string n;
		string x;
		while (1) {
			cout << "请输入您所在的景点编号(输入#号返回主菜单):" << endl;
			cin >> n;
			if (n == "#") {
				system("cls");
				main();
			}
			else if (AllisNum(n)) {
				std::istringstream is(n);
				is >> m;
				if (m >= num) {
					cout << "景区不存在请重新输入!!!" << endl;
				}
				else {
					cout << "请输入您的目的景点编号:" << endl;
					cin >> x;
					if (AllisNum(x)) {
						std::istringstream iis(x);
						iis >> k;
						if (k >= num) {
							cout << "景区不存在请重新输入!!!" << endl;
						}
						else {
							if (m == k) {
								cout << "您已经在" << name[m] << "了哦" << endl;
							}
							else {
								cout << "已为您规划最佳路线" << endl;
								grph.Short(m, k);
							}
						}
					}
					else {
						cout << "不合法的输入!!!" << endl;
					}
				}
			}
			else {
				cout << "不合法的输入!!!" << endl;
			}
		}
	}
	else if (id == 4) {
		system("cls");
	cout << "请选择设置项目(输入#号返回主菜单):" << endl;
		cout << "1:增加景点" << endl;
		cout << "2:删除景点" << endl;
		cout << "3:增加道路" << endl;
		cout << "4:删除道路" << endl;
		cout << "5:修改景点信息" << endl;
		cout << "6:修改道路长度" << endl;
		cout << "7:生成管道铺设规划" << endl;
		string n;
		while (cin >> n) {
			if (n == "#") {
				system("cls");
				main();
			}
			else {
				int men;
				std::istringstream iiis(n);
				iiis >> men;
				cout << men << endl;
				if (men == 1) {
					grph.addVex();
				}
				else if (men == 2) {
					grph.deleteVex();
				}
				else if (men == 3) {
					grph.addRoad();
				}
				else if (men == 4) {
					grph.delRoad();
				}
				else if (men == 5) {
					grph.setVer();
				}
				else if (men == 6) {
					grph.SetSide();
				}
				else if (men == 7) {
					grph.prim();
				}
			}
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
