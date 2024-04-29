#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#include"HashTable.h"

//int main()
//{
//	unordered_set<int> s;
//	s.insert(5);
//	s.insert(4);
//	s.insert(2);
//	s.insert(3);
//	s.insert(1);
//	unordered_set<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	unordered_map<string, string> dict;
//	dict["sort"];
//	dict["sort"] = "ÅÅÐò";
//	dict["string"] = "×Ö·û´®";
//	dict["abc"] = "xx";
//	for (auto& kv : dict)
//	{
//		cout << kv.first << ": "<<kv.second<<" ";
//	}
//	cout << endl;
//
//
//	return 0;
//}

//int main()
//{
//	bit::TestHT1();
//	bit::TestHT2();
//	return 0;
//}
#include"MyUnorderedMap.h"
#include"MyUnorderedSet.h"
int main()
{
	//hash_bucket::TestHT1();
	//hash_bucket::TestHT2();
	bit::test_map();
	bit::test_set();
	return 0;
}