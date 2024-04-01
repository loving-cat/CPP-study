#pragma once
#include<iostream>
#include<assert.h>

namespace bit {
	template<class T>
	struct List_Node
	{
		List_Node<T>* _next;
		List_Node<T>* _prev;
		T _data;
		List_Node(const T& x = T())
			:_next(nullptr)
			,_prev(nullptr)
			,_data(x)
		{}
	};

	//1.迭代器要么就是原生指针
	//2.迭代器要么就是自定义类型对原生指针的封装，模拟指针的行为
	template<class T,class Ref,class Ptr>//增加一个模板参数，Ref可以传过来T&，const T&;
	struct _List_iterator
	{
		typedef List_Node<T> node;
		typedef _List_iterator<T, Ref,Ptr> self;
		node* _node;

		_List_iterator(node* n)
			:_node(n)
		{}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->prev;
			return tmp;
		}
		bool operator !=(const self& s)
		{
			return _node != s._node;
		}
		bool operator ==(const self& s)
		{
			return _node == s._node;
		}
	};

	/*template<class T>
	struct Const_List_iterator
	{
		typedef List_Node<T> node;
		typedef Const_List_iterator<T> self;
		node* _node;

		_List_iterator(node* n)
			:_node(n)
		{}

		const T& operator*()
		{
			return _node->_data;
		}
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->prev;
			return tmp;
		}
		bool operator !=(const self& s)
		{
			return _node != s._node;
		}
		bool operator ==(const self& s)
		{
			return _node == s._node;
		}

	};*/

	template<class T>
	class List
	{
		typedef List_Node<T> node;//给上面结构体一个别名node
	public:
		typedef _List_iterator<T,T&,T*> iterator;
		typedef _List_iterator<T, const T&,const T*> const_iterator;
		//typedef Const_List_iterator<T> const_iterator;


		iterator begin()
		{
			//iterator it(_head->_next)
			//return it;
			return iterator(_head->_next);//匿名对象
		}
		const_iterator begin() const//const修饰的是_head指针，不是_head指向的数据，可以拷贝
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}

		void empty_init()
		{
			_head = new node;//直接new一个新的结构体
			_head->_next = _head;
			_head->_prev = _head;

			_size = 0;
		}

		List()
		{
			empty_init();
		}
		//lt2(lt1)
		List(const List<T>& lt)
		{
			empty_init();//搞一个哨兵位的头节点，自己拷贝自己
			for (auto& e : it)//由于T可能时string类型，需要在e前面加上& 防止变成拷贝
			{
				push_back(e);
			}
		}

		//链表无法浅拷贝
		// 需要写析构 就需要写深拷贝
		// 不需要析构，一般不需要自己写深拷贝，默认浅拷贝
		void swap(List<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		List<T>& operator=(List<T> lt)
		{
			swap(lt);
			return *this;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		~List()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		//默认构造函数，无需深拷贝

		void push_back(const T& x)
		{
			//node* tail = _head->_prev;//创造了一个tail节点指针出来拿到头节点的prev(前一个)
			//node* new_node = new node(x);
			//tail->_next = new_node;
			//new_node->_prev = tail;
			//new_node->_next = _head;
			//_head->_prev = new_node;
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		void insert(iterator pos,const T& x)
		{
			node* cur = pos._node;
			node* prev = cur->_prev;

			node* NewNode = new node(x);

			prev->_next = NewNode;//cur->_prev->_next = NewNode;
			NewNode->_prev = prev;//NewNode->_prev = cur->_prev->_next;
			NewNode->_next = cur;//NewNode->_next = pos._node;
			cur->_prev = NewNode;//pos._node->_prev = NewNode;
		}
		void erase(iterator pos)
		{
			assert(pos != end());//哨兵位的头节点不能erase
			node* prev = pos._node->_prev;
			node* next = pos._node->_next;

			prev->_next = next;//前一个节点的下一个指向下一个
			next->_prev = prev;
			delete pos._node;
		}

	private:
		node* _head;//调用了上面结构体的ListNode,让_head拥有了next and prev
	};

	void print_list(const List<int>& lt)
	{
		List<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}

	void test_list1()
	{
		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		print_list(lt);

		List<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			(*it) *= 2;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
	struct AA
	{
		int _a1;
		int _a2;
		AA(int a1=0, int a2=0)
			:_a1(a1)
			, _a2(a2)
		{}
	};
	void test_list2()
	{
		List<AA> lt;
		lt.push_back(AA(1, 1));
		lt.push_back(AA(2, 2));
		lt.push_back(AA(3, 3));

		List<AA>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//std::cout << (*it)._a1 <<":"<<(*it)._a2<< std::endl;
			std::cout << it->_a1 << ":" << it->_a2 << std::endl;
			std::cout << it.operator->()->_a1 << ":" << it.operator->()->_a2 << std::endl;
			++it;
			//it++; 
			//it.operator++(0);
			//++it
			//it.operator++();
		}
		std::cout << std::endl;
	}
}

