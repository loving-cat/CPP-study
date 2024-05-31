#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<array>
//struct Point
//{
//	int x;
//	int y;
//};
//
//class Date
//{
//public:
//	Date(int year,int month,int day)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{
//		//std::cout << "Date(int year,int month,int day)" << std::endl;
//	}
//	void Print()
//	{
//			std::cout << "Date:" << _year << "-" << _month << "-" << _day << std::endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
////一切都可以用列表初始化
////并且可以省略掉=
//int main()
//{
//	int i = 0;
//	int j = { 0 };
//	int k{ 0 };
//	int array1[]{ 1,2,3,4,5 };
//	int array2[5]{ 0 };
//	Point p{ 1,2 };
//
//	Date d1(2023, 11, 25);
//
//	//类型转换 构造+拷贝构造->优化直接构造
//	Date d2 = { 2023,11,25 };
//	//本质还是调用构造函数
//	Date d3{ 2023,11,25 };
//	std::string s1 = "xxxxx";
//
//	const Date& d4 = { 2023,11,25 };
//	Date* p1 = new Date[3]{ d1,d2,d3 };
//	Date* p2 = new Date[3]{ {2022,11,25},{2022,11,26},{2022,11,27} };
//	
//	for (int i = 0; i < 3; i++)
//	{
//		p2[i].Print();
//	}
//
//	return 0;
//}

 class Date
{
public:
	Date(int year,int month,int day)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		//std::cout << "Date(int year,int month,int day)" << std::endl;
	}
	void Print()
	{
			std::cout << "Date:" << _year << "-" << _month << "-" << _day << std::endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
//int main()
//{
//	std::vector<int> v1 = { 1,2,3,4 };
//	for (auto e : v1)
//	{
//		std::cout << e << " ";
//	}
//	std::cout << std::endl;
//	std::vector<int> v2{ 1,2,3,4 };
//	std::list<int> lt = { 10,20,30 };
//
//	v1 = { 10,20,30,50 };
//	for (auto e : v1)
//	{
//		std::cout << e << " ";
//	}
//	std::cout << std::endl;
//	//多参数构造类型转换 构造函数
//	//跟对应构造函数参数个数匹配
//	Date d2 = { 2023,11,25 };
//
//	auto il = { 10,20,30,40,50 };
//	std::cout << typeid(il).name() << std::endl;
//
//
//	auto il1 = { 10,20,30,40,50 };
//
//	std::initializer_list<int> il2 = { 10,20,30 };
//	std::initializer_list<int>::iterator it2 = il2.begin();
//	while(it2 != il2.end())
//	{
//		std::cout << *it2 << std::endl;
//		++it2;
//	}
//	std::cout << std::endl;
//
//	for (auto e : il2)
//	{
//		std::cout << e << " ";
//	}
//	std::cout << std::endl;
//
//	std::pair<std::string, std::string> kv1("sort", "排序");
//	std::map<std::string, std::string> dict = { {"insert","插入"},{"get","获取"} };
//
//
//
//	return 0;
//}

 //int main()
 //{
	// int i = 1;
	// double d = 2.2;
	// //类型以字符串形式获取到
	// std::cout << typeid(i).name() << std::endl;
	// std::cout << typeid(d).name() << std::endl;
	// //typeid(i).name() j;
	// auto j = i;
	// auto ret = i * d;
	// decltype(ret) x;

	// //用ret的类型去实例化vector
	// //decltype可以推到对象的类型，这个类型是可以用
	// //用来模板实参，或者再定义对象
	// std::vector<decltype(ret)> v;
	// v.push_back(1);
	// v.push_back(1.1);
	// for (auto e : v)
	// {
	//	std::cout << e << " ";
	// }
	// std::cout << std::endl;


	// return 0;
 //}


 //array-------------------------------------------------------
 //int main()
 //{
	// std::array<int, 10> a1;
	// std::cout << sizeof(a1) << std::endl;
	// //a1[10];
	// std::vector<int> v(10, 0);
	// std::cout << sizeof(v) << std::endl;

	// return 0;
 //}
 //array-------------------------------------------------------

int main()
{
	double x = 1.1, y = 2.2;
	//左值
	int i = 0;
	int j = i;
	//常见的右值
	10;
	x + y;
	//fmin(x + y);

	//左值引用能否给右值取别名？ 不能，但是const左值引用可以
	const int& r1 = 10;
	const int& r2 = i + j;
	//右值引用
	int&& rr1 = 10;
	int&& rr2 = i + j;
	//右值引用能否给左值取别名？ 不能，但是右值引用可以给move(左值)
	int&& rr3 = std::move(i);


	return 0;
}







