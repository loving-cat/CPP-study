#include"2.2-Stack.h"

void Stack::Init(int n)
{
    a = (int*)malloc(sizeof(int)* capacity);
    if(nullptr == a)
    {
        perror("malloc申请空间失败");
        return;
    }
    capacity = n;
    size = 0;
}
void Stack::Push(int x)
{
    a[size++] = x;
}