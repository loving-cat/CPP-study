#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//void StackInit(Stack* ps, int defalutCapacity = 4)
//{
//
//}

//int main()
//{
//	cout << "hello world" << endl;
//	return 0;
//}

////��������
////Linux�ĺ������ι���
////_Z3Addii(��ַ)
//int Add(int left, int right)
//{
//	cout << "int Add(int left,int right)" << endl;
//	return left + right;
//}
////_Z3Adddd
//double Add(double left, double right)
//{
//	cout << "double Add(double left, double right),nums = " << left + right << endl;
//	return left + right;
//}
//
//int main()
//{
//	Add(1, 2);	  //call _Z3Addii(��ַ)
//	Add(1.1, 2.2);//call _Z3Adddd(��ַ)
//	return 0;
//}

////���ã����Ѵ��ڱ���ȡ��һ��������
//int main()
//{
//	int i = 0;
//	int& k = i;
//	int j = i;
//	cout << &i << endl;
//	cout << &k << endl;
//	cout << &j << endl;
//	//k��i��ַ��ͬ��������ԭ������ַ��ͬ
//	++k;
//	++j;
//
//	int& m = i;
//	int& n = i;
//
//	++n;
//	return 0;
//}

////C����
//void Swap(int* x, int* y)
//{
//	int tmp = *x;
//	*x = *y;
//	*y = tmp;
//}
//int main()
//{
//	int i = 0, j = 1;
//	Swap(&i, &j);
//	printf("%d %d", i, j);
//	return 0;
//}

//C++
void Swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

typedef struct Node
{
	struct Node* next;
	int val;
}Node,*PNode;

//void PushBack(Node*& phead, int x)
void PushBack(PNode& phead,int x)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (phead == nullptr)
	{
		phead = newnode;
	}
}

typedef struct SeqList
{
	int* a;
	int size;
	int capaicty;
}SQ;

void PushBack(SQ& s, int x)
{

}
int main()
{
	//int i = 0, j = 1;
	//Swap(i, j);
	//cout << i << endl;
	//cout << j << endl;

	////��ָ��ȡ����
	//int* p = &i;
	//int*& rp = p;
	Node* plist = NULL;
	PushBack(plist, 3);
	PushBack(plist, 2);
	PushBack(plist, 1);
	return 0;
}