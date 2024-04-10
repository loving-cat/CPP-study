#include"Func.h"
//template<class T>
//T Add(const T& left, const T& right)
//{
//	return left + right;
//}

void func()
{
	cout << "void func()" << endl;
}

//ÏÔÊ¾ÊµÀý»¯
template
double Add<double>(const double& left, const double& right);
template
int Add<int>(const int& left, const int& right);