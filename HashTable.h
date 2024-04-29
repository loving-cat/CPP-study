#pragma once
#include<vector>
#include<set>

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
//ƫ�ػ�
template<>
struct HashFunc<string>
{
	size_t operator()(const string& key)
	{
		//BKDR
		size_t hash = 0;
		for (auto e : key)//��������ASCII��ֵ
		{
			hash *= 31;
			hash += e;
		}
		return hash;
	}
};
namespace open
{
	//״̬
	enum Status
	{
		EMPTY,
		EXIST,//����
		DELETE
	};
	template<class K, class V>
	struct HashData//����
	{
		pair<K, V> _kv;
		Status _s; //״̬
	};

	
	//struct HashFuncString
	//{
	//	size_t operator()(const string& key)
	//	{
	//		//BKDR
	//		size_t hash = 0;
	//		for (auto e: key)//��������ASCII��ֵ
	//		{
	//			hash *= 31;
	//			hash += e;
	//		}
	//		return hash;
	//	}
	//};

	//class Person
	//{
	//	//����
	//	//�༶
	//	//רҵ 
	//	//ֱ��������ת��Ϊascii����� ���Ψһ 
	//};

	template<class K, class V,class Hash = HashFunc<K>>
	class HashTable//��ϣ��
	{
	public:
		HashTable()
		{
			_tables.resize(10);
		}
		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			//�������ӣ��غ����ӣ�  -- > ���ݸ���/�ռ��С
			//��������0.7������  int/int �ò���0.7  ���ֽ������ ��һ��ǿתdouble �ڶ��� ��_n*10
			if (_n * 10 / _tables.size() == 7)
			{
				//�����¿ռ�
				size_t newSize = _tables.size() * 2;
				HashTable<K, V, Hash> newHT;
				//���±�ʹ���¿ռ�
				newHT._tables.resize(newSize);
				//�����ɱ�
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._s == EXIST)
					{
						newHT.Insert(_tables[i]._kv);
					}
				}
				_tables.swap(newHT._tables);
			}
			Hash hf;
			//����̽��
			size_t hashi = hf(kv.first) % _tables.size();
			while (_tables[hashi]._s == EXIST)
			{
				hashi++;
				hashi %= _tables.size();
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._s = EXIST;
			++_n;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			Hash hf;

			size_t hashi = hf(key) %  _tables.size();
			while (_tables[hashi]._s != EMPTY)
			{
				if (_tables[hashi]._s == EXIST && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}
				hashi++;
				hashi %= _tables.size();
			}
			return NULL;
		}
		//αɾ����
		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_s = DELETE;
				--_n;
				return true;
			}
			else
				return false;
		}
		void Print()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._s == EXIST)
					//printf("[%d]->%d\n", i, _tables[i]._kv.first);
					cout << "[" << i << "]->" << _tables[i]._kv.first << ":" << _tables[i]._kv.second << endl;
				else if (_tables[i]._s == EMPTY)
					printf("[%d]->\n", i);
				else
					printf("[%d]->D\n", i);
			}
		}
	private:
		vector<HashData<K,V>> _tables;
		size_t  _n = 0; // �洢�Ĺؼ��ָ���
	};
	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 4,14,24,34,5,7,1 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(3, 3));
		ht.Insert(make_pair(3, 3));

		ht.Insert(make_pair(-3, -3));
		ht.Erase(-3);

		ht.Print();
		ht.Insert(make_pair(23, 10));
		ht.Print();

	}
	void TestHT2()
	{
		string arr[] = { "�㽶","���","ƻ��","����","���","ƻ��","����" };
		//HashTable<string, int,HashFuncString> ht;
		HashTable<string, int> ht;

		for (auto& e : arr)
		{
			HashData<string, int>* ret = ht.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				ht.Insert(make_pair(e, 1));
			}
		}
		ht.Print();
	}
}
namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _data;

		//��std����һ���İ��ղ���˳�����Ļ�
		//��Ҫ
		//HashNode<T>* _linknext;
		//HashNode<T>* _linkprev;

		HashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{}
	};

	//ǰ������
	template<class K, class T,class KeyOfT, class Hash>
	class HashTable;

	//��������װ
	template<class K,class T,  class Ref, class Ptr,class KeyOfT,class Hash>
	struct _HTIterator
	{
		typedef HashNode<T> Node;
		typedef _HTIterator<K, T, Ref,Ptr,KeyOfT, Hash> Self;
		const HashTable<K, T, KeyOfT, Hash>* _pht;
		//vector<Node*>* _ptb;
		Node* _node;
		//����1����¼��ǰ������Ͱ
		size_t _hashi;
		_HTIterator(Node* node, HashTable<K, T, KeyOfT, Hash>* pht,size_t hashi)
			:_node(node)
			,_pht(pht)
			,_hashi(hashi)
		{}

		//maybe
		_HTIterator(Node* node, const HashTable<K, T, KeyOfT, Hash>* pht, size_t hashi)
			:_node(node)
			, _pht(pht)
			, _hashi(hashi)
		{}
		Self& operator++()
		{
			if (_node->_next)
			{
				//��ǰͰ���нڵ��ߵ���һ���ڵ�
				_node = _node->_next;
			}
			else
			{
				//��ǰͰ�����ˣ�ȥ��һ��Ͱ
				//����2 �ֳ�����
				/*KeyOfT kot;
				Hash hf;
				size_t hashi =hf(kot(_node->_data)) % _pht._tables.size();*/
				++_hashi;
				//Ѱ�Ҳ�Ϊ�յ�Ͱ
				while (_hashi < _pht->_tables.size())
				{
					//�ҵ���Ϊ�յ�Ͱ��
					if (_pht->_tables[_hashi])
					{
						//����һ��
						_node = _pht->_tables[_hashi];
						break;
					}
					++_hashi;
				}
				if (_hashi == _pht->_tables.size())
				{
					_node = nullptr;
				}


			}
			return *this;
		}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
	};


	//�ڶ���ģ�������ʲô����ʲô����ʽ���
	//unordered_set -> HashTable<K,K>
	//unordered_map -> HashTable<K,pair<K,V>>
	template<class K, class T,class KeyOfT,class Hash>
	class HashTable
	{
		typedef HashNode<T> Node;

		template<class K, class T, class Ref,class Ptr,class KeyOfT, class Hash>
		friend struct _HTIterator;
	public:
		typedef _HTIterator<K, T, T&,T*,KeyOfT, Hash> iterator;
		typedef _HTIterator<K, T, const T&, const T*, KeyOfT, Hash>const_iterator;

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this, i);
				}
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr, this, -1);
		}
		//this-> const HashTable<K,T,KeyOfT,Hash>
		const_iterator begin() const  //const ���ε��������this
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return const_iterator(_tables[i], this, i);
				}
			}
			return end();
		}
		//this-> const HashTable<K,T,KeyOfT,Hash>
		const_iterator end() const
		{
			return const_iterator(nullptr, this, -1);
		}
		HashTable()
		{
			_tables.resize(10);
		}
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
		pair<iterator,bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator it = Find(kot(data));
			//����������ֵû�в���ɹ�
			if (it!=end())
				return make_pair(it,false);
			Hash hf;
			//�������� ���ŵ�1
			if (_n == _tables.size())
			{
				//...
				//	//�����¿ռ�
				//size_t newSize = _tables.size() * 2;
				//HashTable<K, V> newHT;
				////���±�ʹ���¿ռ�
				//newHT._tables.resize(newSize);
				////�����ɱ�
				//for (size_t i = 0; i < _tables.size(); ++i)
				//{
				//	Node* cur = _tables[i];
				//	while (cur)
				//	{
				//		newHT.Insert(cur->_kv);
				//		cur = cur->_next;
				//	}
				//}
				//_tables.swap(newHT._tables);
			
				vector<Node*> newTables;
				newTables.resize(_tables.size() * 2, nullptr);
				//�����ɱ�
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						//Ų����ӳ����±�
						size_t hash_i =hf(kot(cur->_data)) % newTables.size();
						cur->_next = newTables[i];
						newTables[i] = cur;
						cur = next;

					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);//�ײ�ָ�뽻��
			}
			size_t hash_i = hf(kot(data)) %  _tables.size();
			Node* newnode = new Node(data);
			//ͷ��
			newnode->_next = _tables[hash_i];
			_tables[hash_i] = newnode;
			++_n;
			return make_pair(iterator(newnode,this,hash_i),true);
		}
		iterator Find(const K& key)
		{
			Hash hf;
			KeyOfT kot;
			size_t hash_i = hf(key) % _tables.size();
			Node* cur = _tables[hash_i];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur,this,hash_i);
				}
				cur = cur->_next;
			}
			return end();
		}
		bool Erase(const K& key)
		{
			Hash hf;
			size_t hash_i = hf(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hash_i];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_tables[hash_i] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;

					}
					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
		void Some()
		{
			size_t bucketSize = 0;
			size_t maxBucketLen = 0;
			size_t sum = 0;
			double averageBucketLen = 0;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					++bucketSize;
				}

				size_t bucketLen = 0;
				while (cur)
				{
					++bucketLen;
					cur = cur->_next;
				}
				sum += bucketLen;
				if (bucketLen > maxBucketLen)
				{
					maxBucketLen = bucketLen;
				}
			}
			averageBucketLen = (double)sum / (double)bucketSize;
			printf("%d\n", bucketSize); 
			printf("%d\n", maxBucketLen);
			printf("%d\n", averageBucketLen);

		}
	private:
		vector<Node*> _tables;
		size_t _n;

		list<T> _linklist;
	};

	//template<class K, class V>
	//class HashTable
	//{
	//	typedef HashNode<K, V> Node;

	//private:
	//	//union bucket
	//	//{
	//	//	forwad_list<pair<K, V>> _lt;
	//	//	set<pair<K, V>> _rbtree;
	//	//	size_t len = 0;//����8���ŵ������
	//	//};
	//	//vector<bucket> _tables;
	//	//vector<forwad_list<pair<K, V>>> _tables;

	//	vector<Node*> _tables;
	//	size_t _n;
	//};

	//void TestHT1()
	//{
	//	HashTable<int, int> ht;
	//	int a[] = { 4,14,24,34,5,7,1,15,25,3 };
	//	for (auto e : a)
	//	{
	//		ht.Insert(make_pair(e, e));
	//	}
	//	ht.Insert(make_pair(13, 13));
	//	cout << ht.Find(4) << endl;
	//	ht.Erase(4);
	//	cout << ht.Find(4) << endl;

	//}
	//void TestHT2()
	//{
	//	string arr[] = { "�㽶","���","ƻ��","����","���","ƻ��","����" };
	//	//HashTable<string, int,HashFuncString> ht;
	//	HashTable<string, int> ht;

	//	for (auto& e : arr)
	//	{
	//		HashNode<string, int>* ret = ht.Find(e);
	//		if (ret)
	//		{
	//			ret->_kv.second++;
	//		}
	//		else
	//		{
	//			ht.Insert(make_pair(e, 1));
	//		}
	//	}
	//}
}