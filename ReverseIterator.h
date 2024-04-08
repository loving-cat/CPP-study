#pragma once
#include<assert.h>
//所有容器的反向迭代器
//迭代器适配器
namespace bit
{
	//vector<T>::iterator
	//list<T>::iterator
	template<class Iterator, class Ref,class Ptr >
	class ReverseIterator
	{
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;
		Iterator _it;
		ReverseIterator(Iterator it)
			:_it(it)
		{}
		Ref operator*()
		{
			Iterator tmp = _it;
			return *(--tmp);
		}
		Ptr operator->()
		{
			return &(operator*());
		}
		Self& operator++()
		{
			return --_it;
		}
		Self& operator--()
		{
			return ++_it;
		}
		bool operator!=(const Self& s)
		{
			return _it != s.it;
		}
	};
}


