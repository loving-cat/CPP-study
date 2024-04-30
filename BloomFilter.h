#pragma once
#include<iostream>
using namespace std;

struct BKDRHash
{
	size_t operator()(const string& key)
	{
		//BKDR
		size_t hash = 0;
		for (auto e : key)
		{
			hash *= 31;
			hash += e;
		}
		return hash;
	}
};

struct APHash
{
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		size_t ch;
		for (size_t i = 0; i < key.size(); ++i)
		{
			char ch = key[i];
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct DJBHash
{
	size_t operator()(const string& key)
	{
		size_t hash = 5381;
		for(auto ch : key)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};

template<size_t N,
class K = string,
class HashFunc1 = BKDRHash,
class HashFunc2 = APHash,
class HashFunc3 = DJBHash>

class BloomFilter
{
public:
	void Set(const K& key)
	{
		size_t hash1 = HashFunc1()(key) % N;
		size_t hash2 = HashFunc2()(key) % N;
		size_t hash3 = HashFunc3()(key) % N;
		_bs.set(hash1);
		_bs.set(hash2);
		_bs.set(hash3);
	}
	//一般不支持删除，删除一个值可能会影响其他值
	//非要支持删除，也是可以的，用多个位标记一个值，存引用计数
	//但是这样的话，空间消耗的就变大了
	void Reset(const K& key)
	{

	}
	bool Test(const K& key)
	{
		//判断不存在是准确的
		size_t hash1 = HashFunc1()(key) % N;
		if (_bs.test(hash1) == false)
			return false;
		size_t hash2 = HashFunc2()(key) % N;
		if (_bs.test(hash2) == false)
			return false;
		size_t hash3 = HashFunc3()(key) % N;
		if (_bs.test(hash3) == false)
			return false;
		//存在误判的
		return true;
	}
private:
	bitset<N> _bs;
};

void TestBF1()
{
	BloomFilter<100> bf;
	bf.Set("猪八戒");
	bf.Set("沙悟净");
	bf.Set("孙悟空");
	bf.Set("唐三藏");
	bf.Set("白龙马");

	cout << bf.Test("猪八戒") << endl;
	cout << bf.Test("沙悟净") << endl;
	cout << bf.Test("孙悟空") << endl;
	cout << bf.Test("唐三藏") << endl;
	cout << bf.Test("白龙马") << endl;
	cout << bf.Test("白龙马1") << endl;
	cout << bf.Test("白龙马2") << endl;
	cout << bf.Test("白龙马 ") << endl;
	cout << bf.Test("搞子哥") << endl;


}