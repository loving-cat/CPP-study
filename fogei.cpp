#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<ctime>
#include "sanziqi.cpp"
using namespace std;

void menu()
{
	cout << "************************" << endl;
	cout << "***	1.开始游戏	  ***" << endl;
	cout << "***	0.退出游戏	  ***" << endl;
	cout << "************************" << endl;
}

void cl(int nums)
{
	srand((unsigned)time(NULL));
	int num = rand() % 100 + 1;
	cout << "输入数字" << endl;
	while (1)
	{
		cin >> nums;
		if (nums > num)
		{
			cout << "大了" << endl;
		}
		else if (nums < num)
		{
			cout << "小了" << endl;
		}
		else
		{
			cout << "答对了" << endl;
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
			cout << "开始游戏" << endl;
			cl(nums);
			break;
		case 0:
			cout << "退出游戏" << endl;
			return 0;
			break;
		default:
			cout << "选择错误" << endl;
			break;
		}
	} while (1);
}