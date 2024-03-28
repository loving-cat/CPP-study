#pragma once
#include<assert.h>
#include<iostream>
#include <vector>
using namespace std;
namespace bit
{
	template<class T>//�ṩ�˸�ģ�����
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_itertor;
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
		//��ģ��ĳ�Ա���������Ǻ���ģ��
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)//�൱��begin ������first,end������last
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		//�������д��ģ��Ϳ��Ը�������ʹ��
		//vector<int> v2(v1.begin(), v1.end());
		//vector<int> v3(str.begin(),str.end());


		//       unsigned int      signed int  �ᵼ�� vector<int> v1(10,1);��ʼ����������
		vector(size_t n, const T& val = T())//��0��ʼ���Ļ���һЩstring���͵��޷���ʼ��
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		//v1=v3
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		
		//C++ 11
		//vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};
		vector(initializer_list<T> il)//�ײ��ǵ�����������ʹ�÷�Χfor
		{
			reserve(il.size());
			for (auto& e : il)
			{
				std::cout << e << " ";
			}
			std::cout << std::endl;
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
		const_itertor start() const
		{
			return _start;
		}
		const_itertor end() const
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
		//��ѯ��ǰ��С
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void reserve(size_t n)//����
		{
			if (n > capacity())
			{
				T* tmp = new T[n];//�����¿ռ�
				size_t old_size = size();
				memcpy(tmp, _start, size() * sizeof(T));
				delete[] _start;//�ͷžɿռ�

				_start = tmp;
				_finish = tmp + old_size;
				_endofstorage = tmp + n;
			}
		}
		void resize(size_t n, const T& val = T())//T()�޲���������
		{
			if (n > size())
			{
				reserve(n);
				//����
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				//ɾ��
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
				//���������Ҫ����pos
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
		//β��
		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//size_t old_size = size();
				//size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;//����

				//T* tmp = new T[newCapacity];//�����¿ռ�
				//memcpy(tmp, _start, size() * sizeof(T));
				//delete[] _start;//�ͷžɿռ�

				//_start = tmp;
				//_finish = tmp + old_size;
				//_endofstorage = tmp + newCapacity;
			}

			*_finish = val;//��������
			++_finish;
		}

		void pop_back()
		{
			/*assert(!empty);
			--_finish;*/
			erase(--end());

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

	typename vector<T>::const_iterator it = v.begin();//�Ӹ�typename �ñ�����֪��const_ierator��һ�����ͣ�����ʵ�������ȥ��
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
void test_vector8()
{
	auto x = { 1,2,3,4,5,6,7,8,9,10 };
	cout << typeid(x).name() << endl;
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };
	for (auto e : v1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	initializer_list<int> y = { 1,2,3,4,5,6,7 };

	//�������Ĺ��캯������ʽ����ת��
	string str = "11111";//����+��������-> �Ż� ֱ�ӹ���
	const string& str1 = "11111";//������ʱ�������õ�����ʱ����
	vector<string> v;
	v.push_back(str);
}

void Test_vector9()
{
	int i = 1;
	//C++ 11
	int j = { 1 };
	int k{ 1 };
}
