#pragma once
#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;

namespace bit
{
	template<class T, class Container = list<T>>//��ʲôֵ����ʲô
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);//β��
		}
		void pop()
		{
			_con.pop_front();//ͷɾ

		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
		const T& front()
		{
			return _con.front();
		}
		const T& back()
		{
			return _con.back();
		}

	private:
		//vector<T> _v
		Container _con;
	};

}

