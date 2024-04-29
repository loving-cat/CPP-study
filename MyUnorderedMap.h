#pragma once
#include"HashTable.h"

namespace bit
{

	template<class K,class V,class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT,Hash>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		pair<iterator, bool> Insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}
		const V& operator[](const K& key) const
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		hash_bucket::HashTable<K, pair<const K,V>, MapKeyOfT,Hash> _ht;
	};
	void test_map()
	{
		unordered_map<string,string> dict;
		dict.Insert(make_pair("sort", "ÅÅĞò"));
		dict.Insert(make_pair("insert", "²åÈë"));
		dict.Insert(make_pair("string", "×Ö·û´®"));
		dict.Insert(make_pair("sort", "ÅÅĞò"));

		for (auto& kv : dict)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;
	}
}
