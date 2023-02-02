#include<iostream>
using namespace std;

#define Add(a,b) ((a)+(b))
// int main()
// {
//     //引用
//     int a = 0;
//     int& b = a;
//     int& c = b;
//     cout << &a << endl; //取地址
//     cout << &b << endl;
//     cout << &c << endl;

//     int x = 10;
//     c = x;
//     cout << &x << endl;
//     cout << &c << endl;
//     return 0;
// }

//引用返回
int& Count()
{
    static int n =0;
    n++;
    return n;
}

int main()
{
    int ret = Count();
    return 0;
}