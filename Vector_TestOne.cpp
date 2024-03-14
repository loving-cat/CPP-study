#include<iostream>
#include<vector>
#include<time.h>
//vector是顺序表
void test_vector1()
{
	std::vector<int> v;
	//尾插
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	
	for (size_t i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	//反向迭代
	//std::vector<int>::reverse_iterator it2 = v.rbegin();
	auto it2 = v.rbegin();
	while (it2 != v.rend())
	{
		std::cout << *it2 << " ";
		++it2;
	}
	std::cout << std::endl;

	for (auto e : v)
	{
		std::cout << e << "";
	}
	std::cout << std::endl;

	std::vector<int> copy(v);
	for (auto e : copy)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

//支持N个V构造
void test_vector2()
{
	std::vector<int> v1(10, 1);
	for (auto e : v1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	//迭代器区间构造，所有的迭代器区间都是左闭右开[x,y)
	std::vector<int> v2(v1.begin(), v1.end());
	for (auto e : v2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::string s1("hello world");
	std::vector<char> v3(s1.begin(), s1.end());
	for (auto e : v3)
	{
		std::cout << e ;
	}
	std::cout << std::endl;


}

void TestVectorExpand()
{
	size_t sz;
	std:: vector<int> v;
	const size_t n = 10000000;

	size_t begin = clock();
	//v.reserve(n);
	sz = v.capacity();
	std::cout << "making v grow:\n";
	for (int i = 0; i < n; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	size_t end = clock();
	std::cout << "消耗时间：" << end - begin << std::endl;
}
void test_vector4()
{
	std::vector<int> v1;
	v1.resize(10, 0);

	std::vector<int> v2(10, 0);
}

int main()
{
	TestVectorExpand();
	//test_vector2();
	return 0;

}