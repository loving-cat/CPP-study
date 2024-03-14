#define _CRT_SECURE_NO_WARNINGS 1 
#pragma once

#include<iostream>
#include<assert.h>
#include<string.h>

namespace bit
{
	class string {

	public:
		//迭代器指针版本 easy版本
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


		//error写法
		/*string()
			:_str(nullptr)//返回空指针
			,_size(0)
			,_capacity(0)
		{}*/
		/*string()
			:_str(new char[1])
			,_size(0)
			,_capacity(0)
		{

		}*/

		//初始化列表的初始化顺序是按照声明的顺序
		/*string(const char* str)
			:_size(strlen(str))
			, _str(new char[_size + 1])
			, _capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/  

		const char* c_str() const {
			return _str;//接收了上面error写法的空指针
		}
		//传统写法
		string(const string& s)
		{
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		//现代写法
		//常量字符串默认有个\0
		//string(const char* str = '\0')//常量字符串 //不能给nullptr的缺省值
		string(const char* str = "")
			:_size(strlen(str))//调用null值会错误

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
		//拷贝构造传统写法
		//s1=s3;
		string& operator=(const string& s)//s是s3   this是s1
		{
			char* tmp = new char[s._capacity+1];
			strcpy(tmp, s._str);

			delete[] _str;
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;

			return *this;
		}
		//拷贝构造现代写法①   现代写法本质是服用
		string& operator=(const string& s)//s是s3   this是s1
		{
			string ss(s);
			swap(ss);

			return *this;
		}
		//②
		//											s3
		string& operator=(string ss)
		{
			swap(ss);
			return *this;//*this 是 s1
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//遍历
		size_t size() const //不修改成员，普通和const对象都可以调用
		{
			return _size;
		}
		//调用函数访问私有成员
		size_t capacity() const
		{
			return _capacity;
		}
		//可读可写
		char& operator[](size_t pos)//获取pos位置的字符
		{
			assert(pos < _size);
			return _str[pos];//new出来的在堆上，解引用出来的就在堆上
		}
		//只读
		const char& operator[](size_t pos) const//获取pos位置的字符
		{
			assert(pos < _size);
			return _str[pos];//new出来的在堆上，解引用出来的就在堆上
		}
		void resize(size_t n,char ch = '\0')//半缺省
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
				char* tmp = new char[n+1];//多开一个空间给\0标识字符
				strcpy(tmp, _str);
				delete[] _str;//释放low空间
				_str = tmp;//指针指向新空间
				_capacity = n;
			}
		}
		void push_back(char ch)//尾插
		{
			//扩容
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4:2*_capacity);
			}
			_str[_size] = ch;//第一个位置拿到ch
			++_size;//到下一个位置
			_str[_size] = '\0';//第二个位置放入标识符
		}
		void append(const char* str)
		{
			//扩容
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
			//扩容2倍
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			//①
			//int end = _size;
			////从pos位置的字符开始往后挪动，将pos位置空出
			//while (end >= (int)pos)
			//{
			//	_str[end + 1] = _str[end];
			//	--end;//end不会小于0 size_t 所以当pos=0的时候会出错
			//}

			//②
			size_t end = _size+1;
			//从pos位置的字符开始往后挪动，将pos位置空出
			while (end > pos)
			{
				_str[end] = _str[end-1];
				--end;//end不会小于0 size_t 所以当pos=0的时候会出错
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
				//扩容
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
								//溢出风险
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
		// 返回c在string中第一次出现的位置
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

		// 返回子串s在string中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const
		{
			//实践使用KMP算法使用少，不实用
			//效率高的算法----BM字符串匹配

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
				for (size_t i = pos; i < pos + len; ++i)//从len位置开始
				{
					sub += _str[i];
				}
			}
			return sub;
		}

		//  std:: 命名空间能不展开就不展开
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
	



	private://初始化列表的初始化顺序是按照声明的顺序
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

		char buff[128] = { '\0' };//防止扩容代价大，通过buff暂时储存，一段一段进
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
		//越界检查是一种抽查，不一定会查到越界
	}
	void test_string2()
	{
		string s3("hello world");//begin------end  左闭右开的区间
		string::iterator it3 = s3.begin();
		while (it3 != s3.end())
		{
			*it3 -= 3;
			std::cout << *it3 << "";
			++it3;
		}
		std::cout << std::endl;
		for (auto ch : s3)//自动迭代自动++
		{
			std::cout << ch << " ";
		}
		std::cout << std::endl;

		const string s4("xxxx");
		string::const_iterator it4 = s4.begin();
		while (it4 != s4.end())
		{
			//*it3 -= 3;  底层为const 不支持修改
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