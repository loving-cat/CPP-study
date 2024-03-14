#define _CRT_SECURE_NO_WARNINGS 1 
#pragma once

#include<iostream>
#include<assert.h>
#include<string.h>

namespace bit
{
	class string {

	public:
		//������ָ��汾 easy�汾
		typedef char* iterator;
		typedef const char* const_iterator;

		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}


		//errorд��
		/*string()
			:_str(nullptr)//���ؿ�ָ��
			,_size(0)
			,_capacity(0)
		{}*/
		/*string()
			:_str(new char[1])
			,_size(0)
			,_capacity(0)
		{

		}*/

		//��ʼ���б�ĳ�ʼ��˳���ǰ���������˳��
		/*string(const char* str)
			:_size(strlen(str))
			, _str(new char[_size + 1])
			, _capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/  

		const char* c_str() const {
			return _str;//����������errorд���Ŀ�ָ��
		}
		//��ͳд��
		string(const string& s)
		{
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		//�ִ�д��
		//�����ַ���Ĭ���и�\0
		//string(const char* str = '\0')//�����ַ��� //���ܸ�nullptr��ȱʡֵ
		string(const char* str = "")
			:_size(strlen(str))//����nullֵ�����

		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
		}
		//�������촫ͳд��
		//s1=s3;
		string& operator=(const string& s)//s��s3   this��s1
		{
			char* tmp = new char[s._capacity+1];
			strcpy(tmp, s._str);

			delete[] _str;
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;

			return *this;
		}
		//���������ִ�д����   �ִ�д�������Ƿ���
		string& operator=(const string& s)//s��s3   this��s1
		{
			string ss(s);
			swap(ss);

			return *this;
		}
		//��
		//											s3
		string& operator=(string ss)
		{
			swap(ss);
			return *this;//*this �� s1
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//����
		size_t size() const //���޸ĳ�Ա����ͨ��const���󶼿��Ե���
		{
			return _size;
		}
		//���ú�������˽�г�Ա
		size_t capacity() const
		{
			return _capacity;
		}
		//�ɶ���д
		char& operator[](size_t pos)//��ȡposλ�õ��ַ�
		{
			assert(pos < _size);
			return _str[pos];//new�������ڶ��ϣ������ó����ľ��ڶ���
		}
		//ֻ��
		const char& operator[](size_t pos) const//��ȡposλ�õ��ַ�
		{
			assert(pos < _size);
			return _str[pos];//new�������ڶ��ϣ������ó����ľ��ڶ���
		}
		void resize(size_t n,char ch = '\0')//��ȱʡ
		{
			if (n < _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				reserve(n);
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n+1];//�࿪һ���ռ��\0��ʶ�ַ�
				strcpy(tmp, _str);
				delete[] _str;//�ͷ�low�ռ�
				_str = tmp;//ָ��ָ���¿ռ�
				_capacity = n;
			}
		}
		void push_back(char ch)//β��
		{
			//����
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4:2*_capacity);
			}
			_str[_size] = ch;//��һ��λ���õ�ch
			++_size;//����һ��λ��
			_str[_size] = '\0';//�ڶ���λ�÷����ʶ��
		}
		void append(const char* str)
		{
			//����
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		void copy_on_write()
		{

		}
		void insert(size_t pos, char ch)
		{
			copy_on_write();
			assert(pos <= _size);
			//����2��
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			//��
			//int end = _size;
			////��posλ�õ��ַ���ʼ����Ų������posλ�ÿճ�
			//while (end >= (int)pos)
			//{
			//	_str[end + 1] = _str[end];
			//	--end;//end����С��0 size_t ���Ե�pos=0��ʱ������
			//}

			//��
			size_t end = _size+1;
			//��posλ�õ��ַ���ʼ����Ų������posλ�ÿճ�
			while (end > pos)
			{
				_str[end] = _str[end-1];
				--end;//end����С��0 size_t ���Ե�pos=0��ʱ������
			}
			_str[pos] = ch;
			++_size;
		}

		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				//����
				reserve(_size + len);
			}
			size_t end = _size + len;//15
			while (end > pos+len-1)
			{
				_str[end] = _str[end - len];
				end--;
			}
			strncpy(_str + pos, str, len);
			_size += len;
		}

		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);	
								//�������
			/*if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}*/
			if (len == npos || len>=_size-pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}
		// ����c��string�е�һ�γ��ֵ�λ��
		size_t find(char c, size_t pos = 0) const
		{
			assert(pos < _size);
			for (int i = pos; i < _size; ++i)
			{
				if (_str[i] == c)
				{
					return i;
				}
			}
			return npos;
		}

		// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
		size_t find(const char* s, size_t pos = 0) const
		{
			//ʵ��ʹ��KMP�㷨ʹ���٣���ʵ��
			//Ч�ʸߵ��㷨----BM�ַ���ƥ��

			assert(pos < _size);
			const char* p = strstr(_str + pos, s);
			if (p)
			{
				return p - _str;
			}
			else
			{
				return npos;
			}

		}
		void clear()
		{
			_size = 0;
			_str[0] = '\0';
		}
		string substr(size_t pos = 0, size_t len = npos)
		{
			string sub;
			//if (len == npos || len >= _size - pos)
			if(len >= _size-pos)
			{
				for (size_t i = pos; i < _size; ++i)
				{
					sub += _str[i];
				}
			}
			else
			{
				for (size_t i = pos; i < pos + len; ++i)//��lenλ�ÿ�ʼ
				{
					sub += _str[i];
				}
			}
			return sub;
		}

		//  std:: �����ռ��ܲ�չ���Ͳ�չ��
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
	



	private://��ʼ���б�ĳ�ʼ��˳���ǰ���������˳��
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		static const int npos = -1;
	};
	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		/*for (size_t i = 0; i < s.size(); i++)
		{
			out << s[i];
		} */

		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();
		/*char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;*/

		char buff[128] = { '\0' };//��ֹ���ݴ��۴�ͨ��buff��ʱ���棬һ��һ�ν�
		size_t i = 0;
		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			if (i < 127)
			{
				buff[i++] = ch;
			}
			else
			{
				s += buff;
				i = 0;
				buff[i++] = ch;
			}
			ch = in.get();
		}
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
	}

	std::istream& getline(std::istream& in, string& s)
	{
		s.clear();
		char ch;
		ch = in.get();
		while (ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
	void swap(string& x, string& y)
	{
		x.swap(y);
	}
	bool operator==(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret == 0;
	}
	bool operator<(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret < 0;
	}

	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}

	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
	const int string::npos = -1;
	void test_string1() {
		string s1("hello world");
		string s2;

		for (size_t i = 0; i < s1.size(); ++i)
		{
			s1[i]++;
		}
		std::cout << std::endl;

		for (size_t i = 0; i < s1.size(); ++i)
		{
			std::cout << s1[i] << "";
		}
		std::cout << std::endl;

		const string s3("xxxxx");
		for (size_t i = 0; i < s3.size(); ++i)
		{
			//s3[i]++;
			std::cout << s3[i] << "";
		}
		std::cout << std::endl;
		//Խ������һ�ֳ�飬��һ����鵽Խ��
	}
	void test_string2()
	{
		string s3("hello world");//begin------end  ����ҿ�������
		string::iterator it3 = s3.begin();
		while (it3 != s3.end())
		{
			*it3 -= 3;
			std::cout << *it3 << "";
			++it3;
		}
		std::cout << std::endl;
		for (auto ch : s3)//�Զ������Զ�++
		{
			std::cout << ch << " ";
		}
		std::cout << std::endl;

		const string s4("xxxx");
		string::const_iterator it4 = s4.begin();
		while (it4 != s4.end())
		{
			//*it3 -= 3;  �ײ�Ϊconst ��֧���޸�
			std::cout << *it4 << "";
			++it4;
		}
		std::cout << std::endl;
		for (auto ch : s4)
		{
			std::cout << ch << " ";
		}
		std::cout << std::endl;
	}
	void test_string3() {
		string s1("hello world");
		s1.insert(6,"xxx");
	}
}