#define _CRT_SECURE_NO_WARNINGS 1
//C++����C�﷨


////�ֲ���/ȫ����
//#include<stdio.h>
//int a = 2;
//void f1()
//{
//	int a = 0;
//	printf("%d\n", a);
//	printf("%d\n", ::a); // ::�������޶���
//}
//
////Node�����ظ���C�����޷����
////ʹ��C++��namespace���
////namespace֧��Ƕ��
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


//1,�ƶ������ռ����
//int main()
//{
//	struct AQueue::bit::Queue q;
//	AQueue::bit::QueueInit(&q);
//	AQueue::bit::QueuePush(&q,1);
//	AQueue::bit::QueuePush(&q,2);
//
//	return 0;
//}

//2��ȫ��չ����һ�������������ʹ��
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

////3.����չ��
//#include<iostream>
//
////����չ��
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

//ʵ�ʿ�����Ŀʹ��1��3����

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	// << ������
//	// endl '\n'
//	cout << "hello world" << endl;
//	cout << "hello world" << '\n';
//
//	//�Զ�ʶ������
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
//	char name[10] = "����";
//	int age = 18;
//	cout << "������" << name << endl;
//	cout << "���䣺" << age << endl;
//
//	printf("������%s ���䣺%d", name, age);
//	return 0;
//}

#include<iostream>
//ȱʡ����
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

////ȫȱʡ
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
//	////��������д��
//	//Func(, 2, );
//	//Func(, , 3);
//	return 0;
//}

////��ȱʡ
////���������������ȱʡ
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
//	//ʹ��ȱʡֵ�����������������ʹ��
//	Func(1, 2, 3);
//	Func(1, 2);
//	Func(1);
//	Func();
//
//	////��������д��
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
	//д����
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

	Stack st1;//���Ҫ��100����
	StackInit(&st1);

	Stack st2;//��֪����������
	StackInit(&st2);

}
