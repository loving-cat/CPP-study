//#include<iostream>
//using namespace std;

//int main()
//{
//	cout << "hello cpp" << endl;
//
//	system("pause");
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	cout << "a="<< a << endl;
//	char b = 'b';
//	cout << "b is " << b << endl;
//	system("pause");
//	return 0;
//}

//#define Day 7
//int main()
//{
//	cout<< "一周总共有: " << Day << endl;
//
//	//2，const修饰的变量
//	const int month = 12;
//	//month = 24//err const 修饰的变量也是常量
//	cout << "一年总共有：" << month << endl;
//	system("pause");
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
////标识符命名规则
////1.标识符不可以是关键字
////2.标识符是由字母，数字，下划线构成
////3.标识符第一个字符只能是字母或下划线
////4.标识符是区分大小写的
//int main()
//{
//	//1.标识符不可以是关键字
//	//int char = 10;
//
//	//2,标识符是由字母，数字，下划线构成
//	int abc = 10;
//	int _abc = 10;
//	int _123abc = 30;
//
//	//3,标识符第一个字符只能是字母或下划线
//	//int 123abc = 40;
//
//	//4,标识符区分大小写
//	int aaa = 100;
//	cout << aaa << endl;
//	system("pause");
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	short a = 10;
//	cout << "short 类型所占内存空间" << sizeof(a) << endl;
//	cout << "short 类型所占内存空间" << sizeof(short) << endl;
//	cout << "int 类型所占内存空间" << sizeof(int) << endl;
//	cout << "char 类型所占内存空间" << sizeof(char) << endl;
//	cout << "float 类型所占内存空间" << sizeof(float) << endl;
//	cout << "double 类型所占内存空间" << sizeof(double) << endl;
//	cout << "long 类型所占内存空间" << sizeof(long) << endl;
//	cout << "long long类型所占内存空间" << sizeof(long long) << endl;
//	system("pause");
//	return 0;
//}

#include<iostream>
using namespace std;

int main()
{

	//单精度 float 统计到后面7位有效数字
	//双精度 double 统计到后面的15-16位有效数字
	//默认情况下，输出一个小数，会显示出6位有效数字
	float f1 = 3.1415926f;
	cout << "f1 = " << f1 << endl;
	double d1 = 3.1415926;
	cout << "d1 = " << d1 << endl;

	//科学计数法
	float f2 = 3e2;//3 * 10 ^ 2;
	cout << "f2 = " << f2 << endl;
	float f3 = 3e-2;// 3 * 0.1 ^2;
	cout << "f3 = " << f3 << endl;
	system("pause");
	return 0;
}

