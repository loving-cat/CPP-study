#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<ctime>
#include "sanziqi.cpp"
using namespace std;

void menu()
{
	cout << "************************" << endl;
	cout << "***	1.��ʼ��Ϸ	  ***" << endl;
	cout << "***	0.�˳���Ϸ	  ***" << endl;
	cout << "************************" << endl;
}

void cl(int nums)
{
	srand((unsigned)time(NULL));
	int num = rand() % 100 + 1;
	cout << "��������" << endl;
	while (1)
	{
		cin >> nums;
		if (nums > num)
		{
			cout << "����" << endl;
		}
		else if (nums < num)
		{
			cout << "С��" << endl;
		}
		else
		{
			cout << "�����" << endl;
			break;
		}
	}
}
int main()
{
	int inputt = 0;
	int nums = 0;
	do
	{
		menu();
		cin >> inputt;
		switch (inputt)
		{
		case 1:
			cout << "��ʼ��Ϸ" << endl;
			cl(nums);
			break;
		case 0:
			cout << "�˳���Ϸ" << endl;
			return 0;
			break;
		default:
			cout << "ѡ�����" << endl;
			break;
		}
	} while (1);
}