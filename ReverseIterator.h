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
			return *(--tmp);//访问前一个位置
		}
		Ptr operator->()
		{
			//return _it.operator->();
			return &(operator*());
		}
		Self& operator++()
		{
			 --_it;
			 return *this;
		}
		Self& operator--()
		{
			++_it;
			return *this;

		}
		bool operator!=(const Self& s)
		{
			return _it != s.it;
		}
	};
}


