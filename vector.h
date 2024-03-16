#pragma once
#include<assert.h>
#include<iostream>
#include <vector>
using namespace std;
namespace bit
{
	template<class T>//提供了个模板参数
	class vector
	{
	public:
		typedef T* iterator;

		vector()
		{

		}
		//v2(v1)
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
		iterator start()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator start() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos) const
		{
			assert(pos < size());
			return _start[pos];
		}
		//查询当前大小
		size_t size() const
		{
			return _finish - _start;
		}
		size_t size()
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endofstorage - _start;
		}
		size_t capacity()
		{
			return _endofstorage - _start;
		}
		void reserve(size_t n)//扩容
		{
			if (n > capacity())
			{
				T* tmp = new T[n];//拷贝新空间
				size_t old_size = size();
				memcpy(tmp, _start, size() * sizeof(T));
				delete[] _start;//释放旧空间

				_start = tmp;
				_finish = tmp + old_size;
				_endofstorage = tmp + newCapacity;
			}
		}
		void resize(size_t n, const T& val = T())//T()无参匿名对象
		{
			if (n > size())
			{
				reserve(n);
				//插入
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				//删除
				_finish = _start + n;
			}
		}
		void insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//如果扩容了要更新pos
				pos = _start + len;
			}
			iterator it = _finish - 1;
			while (it >= pos)
			{
				*(it + 1) = *it;
				--it;
			}
			*pos = val;
			++_finish;
		}
		void erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator it = pos + 1;
			while (it < _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
		}
		//尾插
		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				size_t old_size = size();
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;//扩容
				T* tmp = new T[newCapacity];//拷贝新空间
				memcpy(tmp, _start, size() * sizeof(T));
				delete[] _start;//释放旧空间

				_start = tmp;
				_finish = tmp + old_size;
				_endofstorage = tmp + newCapacity;
			}

			*_finish = val;//插入数据
			++_finish;
		}

		void pop_back()
		{
			assert(!empty);
			--_finish;


		}
		bool empty()
		{
			return _start == _finish;
		}
		

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};
}
template<class T>
void print_vector(const vector<T>& v) 
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	typename vector<T>::const_iterator it = v.begin();//加个typename 让编译器知道const_ierator是一个类型，在它实例化后进去拿
	//auto it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector7()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	print_vector(v1);

	vector<double> v2;
	v2.push_back(1.1);
	v2.push_back(2.2);
	v2.push_back(3.3);
	v2.push_back(4.4);
	v2.push_back(5.5);
	print_vector(v2);
}
