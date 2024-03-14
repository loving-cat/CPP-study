//#include<iostream>
//using namespace std;
//
//
////模板->泛型编程
////Swap 交换的泛型编程
//template <class T> void swap(T& a, T& b)
//{
//	T c(a);
//	a = b;
//	b = c;
//}
//
////类模板定义
//template<class T>
//class Stack
//{
//public:
//	void push(const T& x)//常量话其绑定的X，让X不能被修改,常引用
//	{
//
//	}
//private:
//	T* _a;
//	int _top;
//	int _capacity;
//};
//
//int main()
//{
//
//	Stack<int> a;
//	Stack<double> a2;
//
//	return 0;
//}