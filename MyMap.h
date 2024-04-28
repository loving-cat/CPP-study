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
		//��ʵ�����������壬����ȥ��
		//����ģ��ȡ��Ƕ���ͣ���typename���Ǹ��߱�����������������
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
			//firstָ����pair��first��seond�ǵ������ڵ�
			//������������first��second
			//������->second
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