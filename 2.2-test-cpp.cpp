#include<iostream>
#include<map>
#include<string>
using namespace std;

//#include "Func.h"

// int main()
// {
//     f(1);
//     return 0;
// }

// int main()
// {
//     int a = 0;
//     auto b =a;
//     auto c = &a;
//     //获取变量b的实际类型
//     cout << typeid(b).name() << endl;
//     //获取变量c的实际类型
//     cout << typeid(c).name() << endl;

//     //auto 实际价值 简化代码，类型很长时，可以让它自动推到
//     std::map<std::string,std::string> dict;
//     //①
//     //std::map<std::string,std::string>::iterator dit = dict.begin();
//     //②
//     //auto dit = dict.begin();
//     //③
//     //typedef std::map<std::string,std::string>::iterator DictIt;

//     return 0;
// }
// typedef char* pstring;
// int main()
// {
//     const pstring p1 = nullptr; //err
//     const pstring* p1;

//     cout << typeid(p1).name() << endl;
//     return 0;
// }

// int main()
// {
//     int a = 0;
//     auto b = &a;
//     auto* c = &a;
//     auto& d = a;

//     int array[] = {1,2,3,4,5,6,7,8};
//     for(int i = 0; i< sizeof(array) / sizeof(int); ++i)
//     {
//         cout << array[i] << " ";
//     }
//     cout << endl;

//     //范围for -- 语法糖
//     //自动依次取数组中数据赋值给e对象，自动判断结束
//     for(auto& e : array)
//     {  
//         e*=2;
//         cout << e << " ";
//     }
//     cout << endl;
//     for(auto x : array)
//     {
//         cout << x << " ";
//     }
//     cout << endl;
//     return 0;
// }
// int main()
// {
//     int* p1 = NULL;
//     int* p2 = nullptr;
//     return 0;
// }
// void f(int)
// {
//     cout << "f(int)" <<endl;
// }

// void f(int*)
// {
//     cout << "f(int*)" <<endl;
// }

// int main()
// {
//     f(0);
//     f(NULL); //NULL在传统C文件内是自变量0
//     f(nullptr);//修复补丁
//     return 0;
// }

// //c++兼容c结构体用法
// typedef struct ListNode
// {
//     int val;
//     struct ListNode* next;
// }LTN;
// //C： struct ListNode 是类型
// //c++把结构体升级成类
// struct ListNode
// {
//     int val;
//     ListNode* next;
// };
//类里面可以有数据，可以定义数据，函数
//类
// struct Stack
// {
//     //成员函数
    // void Init(int n = 4)
    // {
    //     a = (int*)malloc(sizeof(int)* capacity);
    //     if(nullptr == a)
    //     {
    //         perror("malloc申请空间失败");
    //         return;
    //     }
    //     capacity = n;
    //     size = 0;
    // }
    // void Push(int x)
    // {
    //     a[size++] = x;
    // }
//     //成员变量
//     int* a;
//     int size;
//     int capacity;
// };
#include"2.2-Stack.h"
//在上面的结构体定义中,C++更喜欢用Class命名
//类的定义
class className
{
    
};

class Date
{
public:
    void Init(int year,int month,int day)
    {
        year_ = year;
        month_ = month;
        day_ = day;
    }
private:
    int year_;
    int month_;
    int day_;
};
int main()
{
    Stack st;
    st.Init();
    st.Push(1);
    st.Push(2);
    st.Push(3);

    Date d1;
    d1.Init(2023,2,3);
    return 0;
}