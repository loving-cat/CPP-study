#include<iostream>
#include<vector>
using namespace std;
#include"Red_Black_Tree.h"
#include"MyMap.h"
#include"MySet.h"
//
//int main()
//{
//	int a[] = { 4,2,6,1,3,5,15,7,16,14 };
//	RBTree<int, int> t;
//	for(auto e:a)
//	{
//		t.Insert(make_pair(e, e));
//	}
//	t.InOrder();
//	cout << t.IsBalance() << endl;
//	return 0;
//}
//int main()
//{
//	const int N = 100000;
//	vector<int> v;
//	v.reserve(N);
//	//srand(time(0));
//
//	for (size_t i = 0; i < N; i++)
//	{
//		v.push_back(rand() + i);
//		//cout << v.back() << endl;
//	}
//
//	size_t begin2 = clock();
//	RBTree<int, int> t;
//	for (auto e : v)
//	{
//		if (e == 29365)
//		{
//			int i = 0;
//		}
//
//		cout << "Insert:" << e << "->";
//		t.Insert(make_pair(e, e));
//		//cout << t.IsBalance() << endl;
//	}
//	size_t end2 = clock();
//
//	cout << "Insert:" << end2 - begin2 << endl;
//
//	cout << t.IsBalance() << endl;
//	cout << t.Height() << endl;
//	cout << t.Size() << endl;
//
//	size_t begin1 = clock();
//	for (auto e : v)
//	{
//		t.Find(e);
//	}
//
//	for (size_t i = 0; i < N; i++)
//	{
//		t.Find((rand() + i));
//	}
//
//	size_t end1 = clock();
//
//	cout << "Find:" << end1 - begin1 << endl;
//
//	return 0;
//}

void test_set()
{
	bit::set<int> s;
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(2);
	bit::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto e : s)
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test_map()
{
	bit_Two::map<string,string> dict;
	dict.insert(make_pair("sort", "ÅÅÐò"));
	dict.insert(make_pair("find", "ËÑË÷"));
	dict.insert(make_pair("sort", "ÅÅÐò"));
	bit_Two::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		//cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}
int main()
{
	test_map();

	test_set();

	return 0;
}