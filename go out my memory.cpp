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
constexpr int MAX = 256 * 1024; //1MB����
vector<int*> vect;
//��ÿ����ڴ�
double getFreeMemory()
{
	static const double DIV = 1024 * 1024 * 1024;
	MEMORYSTATUSEX statex; //�ڴ�ͳ�ƶ���
	statex.dwLength = sizeof(statex); //���ó���
	GlobalMemoryStatusEx(&statex); //��ȡ��ǰ�ڴ���Ϣ
	//��λGB
	double totalPhysicalMem = statex.ullTotalPhys / DIV; //�������ڴ�
	double freePhysicalMem = statex.ullAvailPhys / DIV; //���������ڴ�
	double totalVirtualMem = statex.ullTotalPageFile / DIV; //�������ڴ�
	double freeVirtualMem = statex.ullAvailPageFile / DIV; //���������ڴ�
	cout << "�������ڴ�\t" << totalPhysicalMem << "GB" << endl
		<< "���������ڴ�\t" << freePhysicalMem << "GB" << endl
		<< "�������ڴ�\t" << totalVirtualMem << "GB" << endl
		<< "���������ڴ�\t" << freeVirtualMem << "GB" << endl;
	return freeVirtualMem - 1;//-1 ��֤�������
}
//�����ڴ�
void Distribute(int memorySize)
{
	srand(time(NULL)); //��ʼ���������
	memorySize *= 1024;
	int* p=nullptr;
	int process = 0;//������
	for (int i = 0; i < memorySize; ++i)
	{
		if (i > memorySize * process/ 100 )
		{
			process++;
			if(process%5==0)
				cout << "��" ;
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
//�����ڴ�
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
	cout << "��ʼ��\n";
	Sleep(5000);
	cout << "����׶�\n";
	Distribute(n);
	cout << "�����ڴ�\n";
	Recover();
	Sleep(5000);
	getFreeMemory();
	system("pause");
	return 0;
}
