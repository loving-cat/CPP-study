#pragma once
#include<stdlib.h>

//类成员函数声明和定义分离
//struct Stack
class Stack
{
public:
    //成员函数
    void Init(int n = 4);
    void Push(int x);
private:
    //成员变量
    int* a;
    int size;
    int capacity;
};