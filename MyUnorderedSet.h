#pragma once
#include"HashTable.h"

namespace bit
{
	template<class K,class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, K, SetKeyOfT,Hash>::const_iterator iterator;
		typedef typename hash_bucket::HashTable<K, K, SetKeyOfT,Hash>::const_iterator const_iterator;

	/*	iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}*/
		const_iterator begin() const
		{
			return _ht.begin();
		}
		const_iterator end() const
		{
			return _ht.end();
		}
		pair<iterator,bool> Insert(const K& key)
		{
			//返回普通迭代器，没有返回const迭代器
			//return _ht.Insert(key);
			//绑死的写法
			auto ret = _ht.Insert(key);
			//用其值依次去构造
			return pair<const_iterator, bool>(const_iterator(ret.first._node,ret.first._pht,ret.first._hashi),ret.second);
		}
		iterator find(const K& key)
		{
			return _ht.Find(key);
		}
		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}
	private:
		hash_bucket::HashTable<K, K, SetKeyOfT,Hash> _ht;
	};
	void test_set()
	{
		unordered_set<int> us;
		us.Insert(5);
		us.Insert(15);
		us.Insert(52);
		us.Insert(3);
		us.Insert(1);

		unordered_set<int>::iterator it = us.begin();
		while (it != us.end())
		{
			cout << *it << " ";
			++it;
		}
		for (auto e : us)
		{
			cout << e << " ";
		}
		cout << endl;
	}

}
