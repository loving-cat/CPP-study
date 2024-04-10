#pragma once
#include<iostream>
using namespace std;
//先声明后定义 也能解决模板无法分离编译的问题
template<class T>
T Add(const T& left, const T& right);
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}
//声明和定义放到一起，直接就可以实例化，编译时就有地址，不需要链接

void func();
 