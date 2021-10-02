/* Copyright Pitao
*  Email pitaohc@qq.com
*  Licence: GNU General Public License V3
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <Windows.h>
using namespace std;
constexpr int MAX = 256 * 1024; //1MB数组
vector<int*> vect;
//获得可用内存
double getFreeMemory()
{
	static const double DIV = 1024 * 1024 * 1024;
	MEMORYSTATUSEX statex; //内存统计对象
	statex.dwLength = sizeof(statex); //设置长度
	GlobalMemoryStatusEx(&statex); //获取当前内存信息
	//单位GB
	double totalPhysicalMem = statex.ullTotalPhys / DIV; //总物理内存
	double freePhysicalMem = statex.ullAvailPhys / DIV; //可用物理内存
	double totalVirtualMem = statex.ullTotalPageFile / DIV; //总虚拟内存
	double freeVirtualMem = statex.ullAvailPageFile / DIV; //可用虚拟内存
	cout << "总物理内存\t" << totalPhysicalMem << "GB" << endl
		<< "可用物理内存\t" << freePhysicalMem << "GB" << endl
		<< "总虚拟内存\t" << totalVirtualMem << "GB" << endl
		<< "可用虚拟内存\t" << freeVirtualMem << "GB" << endl;
	return freeVirtualMem - 1;//-1 保证不会崩溃
}
//分配内存
void Distribute(int memorySize)
{
	srand(time(NULL)); //初始化随机种子
	memorySize *= 1024;
	int* p=nullptr;
	int process = 0;//进度条
	for (int i = 0; i < memorySize; ++i)
	{
		if (i > memorySize * process/ 100 )
		{
			process++;
			if(process%5==0)
				cout << "■" ;
			printf("%02d%%", process);
			printf("\b\b\b");
		}
		int num = rand();
		p = new int[MAX];
		fill(p, p + MAX, num);
		vect.push_back(p);
	}
	cout<<"\b100%" << endl;

}
//回收内存
void Recover()
{
	for (auto ip : vect)
	{
		if(ip!=nullptr)
			delete[] ip;
	}
}
int main(int argc, char* argv[])
{
	char copyright[] = "Pitaohc@qq.com";
	int n =getFreeMemory();
	cout << "初始化\n";
	Sleep(5000);
	cout << "清理阶段\n";
	Distribute(n);
	cout << "回收内存\n";
	Recover();
	Sleep(5000);
	getFreeMemory();
	system("pause");
	return 0;
}
