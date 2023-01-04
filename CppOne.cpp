#define _CRT_SECURE_NO_WARNINGS 1
//C++兼容C语法


////局部域/全局域
//#include<stdio.h>
//int a = 2;
//void f1()
//{
//	int a = 0;
//	printf("%d\n", a);
//	printf("%d\n", ::a); // ::域作用限定符
//}
//
////Node名字重复，C语言无法解决
////使用C++的namespace解决
////namespace支持嵌套
//#include"List.h"
//#include"Queue.h"
//int main()
//{
//	struct AQueue::bit::Node node;
//	struct BList::Node node2;
//
//	AQueue::bit::min = 5;
//	printf("%d", AQueue::bit::min);
//	return 0;
//}

/////////////////////////////////////////////////

//#include"Queue.h"


//1,制定命名空间访问
//int main()
//{
//	struct AQueue::bit::Queue q;
//	AQueue::bit::QueueInit(&q);
//	AQueue::bit::QueuePush(&q,1);
//	AQueue::bit::QueuePush(&q,2);
//
//	return 0;
//}

//2，全局展开，一般情况，不建议使用
//#include<iostream>
//#include"Queue.h"
//
//using namespace std;
//int main()
//{
//	struct Queue q;
//	QueueInit(&q);
//	QueuePush(&q, 1);
//	QueuePush(&q, 2);
//
//	cout << "1111";
//	return 0;
//}

////3.部分展开
//#include<iostream>
//
////常用展开
//using std::cout;
//using std::endl;
//using std::cin;
//
//int main()
//{
//	cout << "1111" << endl;
//	int i = 0;
//	cin >> i;
//
//	return 0;
//}

//实际开发项目使用1，3方法

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	// << 流插入
//	// endl '\n'
//	cout << "hello world" << endl;
//	cout << "hello world" << '\n';
//
//	//自动识别类型
//	int n = 0;
//	cin >> n;
//	//double a[5];
//	double* a = (double*)malloc(sizeof(double) * n);
//	if (a == NULL)
//	{
//		perror("malloc fail");
//		exit(-1);
//	}
//	for (int i = 0; i < n; ++i)
//	{
//		cin >> a[i];
//	}
//	for (int i = 0; i < n; ++i)
//	{
//		cout << a[i] << endl;
//	}
//	cout << endl;
//	char name[10] = "张三";
//	int age = 18;
//	cout << "姓名：" << name << endl;
//	cout << "年龄：" << age << endl;
//
//	printf("姓名：%s 年龄：%d", name, age);
//	return 0;
//}

#include<iostream>
//缺省参数
//void Func(int a = 0)
//{
//	std::cout << a << std::endl;
//}
//int main()
//{
//	Func(1);
//	Func();
//	return 0;
//}

////全缺省
//void Func(int a = 10, int b = 20, int c = 30)
//{
//	std::cout << "a=" << a << std::endl;
//	std::cout << "b=" << a << std::endl;
//	std::cout << "c=" << a << std::endl;
//	std::cout << std::endl;
//
//}
//int main()
//{
//	Func(1, 2, 3);
//	Func(1, 2);
//	Func(1);
//	Func();
//
//	////不能这样写↓
//	//Func(, 2, );
//	//Func(, , 3);
//	return 0;
//}

////半缺省
////必须从右往左连续缺省
//void Func(int a , int b = 20, int c = 30)
//{
//	std::cout << "a=" << a << std::endl;
//	std::cout << "b=" << a << std::endl;
//	std::cout << "c=" << a << std::endl;
//	std::cout << std::endl;
//
//}
//int main()
//{
//	//使用缺省值，必须从右往左连续使用
//	Func(1, 2, 3);
//	Func(1, 2);
//	Func(1);
//	Func();
//
//	////不能这样写↓
//	//Func(, 2, );
//	//Func(, , 3);
//	return 0;
//}

void Func(int a , int b = 20, int c = 30)
{
	std::cout << "a=" << a << std::endl;
	std::cout << "b=" << a << std::endl;
	std::cout << "c=" << a << std::endl;
	std::cout << std::endl;

}
struct Stack
{
	int* a;
	int top;
	int capcacity;
};

void StackInit1(struct Stack* ps)
{
	//写死了
	ps->a = (int*)malloc(sizeof(int) * 4);
	if (ps->a == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	ps->top = 0;
	ps->capcacity = 4;
}

void StackInit(struct Stack* ps,int DefaultCapcacity = 4)
{
	ps->a = (int*)malloc(sizeof(int) * 4);
	if (ps->a == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	ps->top = 0;
	ps->capcacity = DefaultCapcacity;
}

int main()
{
	Func(1, 2, 3);
	Func(1, 2);
	Func(1);

	Stack st1;//最多要存100个数
	StackInit(&st1);

	Stack st2;//不知道多少数据
	StackInit(&st2);

}
