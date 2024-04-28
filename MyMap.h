#pragma once
#include"Red_Black_Tree.h"
namespace bit_Two
{
	template<class K,class V>
	class map
	{
	public:
		struct MapKeyOfT
		{
			const K& operator() (const pair<K,V>& kv)
			{
				return kv.first;
			}
		};
		//无实例化，不具体，不敢去找
		//对类模板取内嵌类型，加typename就是告诉编译器，这里是类型
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			//first指的是pair的first，seond是迭代器内的
			//迭代器内又有first，second
			//迭代器->second
			return ret.first->second;
		}
		pair<iterator, bool> insert(const pair<K,V>& kv)
		{
			return _t.Insert(kv);
		}
	private:
		RBTree<K, pair<const K, V>,MapKeyOfT> _t;
	};
}