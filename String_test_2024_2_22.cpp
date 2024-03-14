#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;

//void test_string1()
//{
//	string s0;
//	string s1("hello world");
//	string s2(s1);
//	string s3(s1, 5, 3);//�ӵ����λ��ȡ�����ַ�
//	string s4(s1, 5, 10);//�ӵ����λ����ȡ��10���ַ�������10�����ж���ȡ����
//	string s5(s1, 5);//�ӵ������ʼȡ���ж���ȡ����
//
//	cout << s0 << endl;
//	cout << s1 << endl;
//	cout << s2 << endl;
//	cout << s3 << endl;
//	cout << s4 << endl;
//	cout << s5 << endl;
//
//	string s6(10,'#');
//	cout << s6 << endl;
//}

//��������ĵײ�ԭ��
//class string
//{
//public:
//  & ���ٿ�������Ŀ��ֵ�ɶ���д
//	char& operator[](size_t pos)//���������ûɶ�ã�ûɶ�ռ�Ľ�ʡ������Ҫ��pos����˿ɶ���д
//	{
//		return _str[pos];
//	}
//private:
//	char* _str;
//	size_t _size;
//	size_t _capacity;
//};

//int a[10]
//a[i]�ȼ��� *(a+i)
void test_string2() {

	string s1("hello world");
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i]<<"";
		//cout<<s1.operator[](i)<<"";
	}
	cout << endl;
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i]++;//�����޸��ڲ��ַ�����
	}
	cout << endl;
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i] << "";
	}
	cout << endl;
	string s3("hello world");
	s3[0]++;
	cout << s3 << endl;

	const string s2("hello world");
	//s2[0]++;
	cout << s2 << endl;

	cout << s3.size() << endl;//�������鳤��
	cout << s3.capacity() << endl;//���ÿ��ٿռ�

	string::iterator it3 = s3.begin();
	while (it3 != s3.end())//end�����һ�����ݵ���һ��λ��
	{
		cout << *it3 << "";
		++it3;
	}
	cout << endl;

	cout << typeid(it3).name() << endl;//ץ����

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << "";
		++it;
	}
	cout << endl;

	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	list<int>::iterator itt = lt.begin();
	while (itt != lt.end()) {
		cout << *itt << "";
		++itt;
	}
	cout << endl;

	//�ײ���ǵ�����
	//��Χfor
	for (auto e : s3)
	{
		cout << e << "";
	}
	cout << endl;
	for (auto e : v)
	{
		cout << e << "";
	}
	cout << endl;
	for (auto e : lt)
	{
		cout << e << "";
	}
	cout << endl;

}

//����
void test_string3()
{
	string s1("hello world");
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	//�ɶ���д
	string::iterator it2 = s1.begin();
	while (it2 != s1.end())
	{
		*it2 += 3;
		cout << *it2 << " ";

	}
	cout << endl;

	//ֻ��
	const string s3("hello world");
	string::const_iterator it3 = s3.begin();
	while (it3 != s3.end())
	{
		cout << *it3 << " ";
	}
	cout << endl;
}

//������ز��� Capacity
void test_string4() {
	string s1("hello world");
	cout << s1.size() << endl;
	cout << s1.length() << endl;

	cout << s1.max_size() << endl;

	cout << s1.capacity() << endl;

	//�鿴���ݻ���
	string s;
	s.reserve(100);//��ǰ���ռ�

	size_t sz = s.capacity();
	cout << "capacity changed:" << sz << '\n';
	
	cout << "making s grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed:" << sz << '\n';

		}
		
	}
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	cout << s1.size() << endl;
	s1.clear();
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	cout << s1.size() << endl;

	//���ݽӿ�
	s1.shrink_to_fit();
	cout << s1.capacity() << endl;
	cout << s1.size() << endl;

}

void test_string5() {
	string s1("hello worldxxxxxxx");
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.reserve(200);
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
	
	string s2("hello worldxxxxxxx");
	cout << s2.size() << endl;
	cout << s2.capacity() << endl;

	s2.resize(10);
	cout << s2.size() << endl;
	cout << s2.capacity() << endl;
	s2.resize(20);
	cout << s2.size() << endl;
	cout << s2.capacity() << endl;
	s2.resize(100, 'x');
	cout << s2.size() << endl;
	cout << s2.capacity() << endl;
}

//Ԫ�ط��� �쳣
void test_string6()
{
	string s1("hello world");
	cout << s1[5] << endl;
	cout << s1.at(5) << endl;
	s1[15];
	s1.at(15);

}

void test_string7()
{
	//string::append
	/*
	string(1)
		string& append(const string & str);
	substring(2)
		string& append(const string & str, size_t subpos, size_t sublen = npos);
	c - string(3)
		string & append(const char* s);
	buffer(4)
		string& append(const char* s, size_t n);
	fill(5)
		string& append(size_t n, char c);
	range(6)
		template <class InputIterator>   string& append(InputIterator first, InputIterator last);
	initializer list(7)
		string& append(initializer_list<char> il);*/
  /*(1) string
	Appends a copy of str.
	(2) substring
	Appends a copy of a substring of str.The substring is the portion of str that begins at the character position subpos and spans sublen characters(or until the end of str, if either str is too short or if sublen is string::npos).
	(3) c - string
	Appends a copy of the string formed by the null - terminated character sequence(C - string) pointed by s.
	(4) buffer
	Appends a copy of the first n characters in the array of characters pointed by s.
	(5) fill
	Appends n consecutive copies of character c.
	(6) range
	Appends a copy of the sequence of characters in the range[first, last), in the same order.
	(7) initializer list
	Appends a copy of each of the characters in il, in the same order.*/

	string s1("xhello world");
	s1.push_back('!');
	cout << s1 << endl;

	s1.append("hello bit!");
	cout << s1 << endl;

	s1.append(10, 'x');
	cout << s1 << endl;
	string s2("  apple  ");
	s1.append(s2.begin(), s2.end());
	//s1.append(++s2.begin(), --s2.end());//ȡ���ո�
	cout << s1 << endl;


	//operatot+=
	string s3("hello world");
	s3+=' ';
	s3 += "apple";
	cout << s3 << endl;
}

void test_string8()
{
	string s1("xhello world");
	cout << s1 << endl;
	s1.assign("xxxxx");//����
	cout << s1 << endl;
	s1.insert(0, "yyyy");//��0λ�ò���
	cout << s1 << endl;

	s1.erase(5, 3);//ɾ��
	cout << s1 << endl;

	s1.erase();

	string s2("hello world hello bit");
	//s2.replace(5, 1, "%20");//�滻
	//cout << s2 << endl;

	size_t pos = s2.find(' ');
	while (pos != string::npos)
	{

		s2.replace(pos, 1, "%20");
		pos = s2.find(' ');
	}
	cout << s2 << endl;
	//insert/erase/replace
	//�����þ�Ҫ���ã���Ϊ������ҪŲ�����ݣ�Ч�ʲ���
	string s3;
	for (auto ch : s2)
	{
		if (ch != ' ')
		{
			s3 += ch;
		}
		else
		{
			s3 += "20%";
		}
	}
	cout << s3 << endl;
	s2.swap(s3);
	cout << s2 << endl;
}

void test_string9() {
	string s1("hello world");
	string filename("test.cpp");
	//FILE* fout = fopen(filename.c_str(), "r");
}

void test_string10() {
	string s1("file.cpp");
	//�õ��ļ��ĺ�׺
	size_t pos1 = s1.find('.');
	if (pos1 != string::npos)
	{
		string suffix = s1.substr(pos1);
		//string suffix = s1.substr(pos1,s1.size() - pos1);
		cout << suffix << endl;
	}
	else
	{
		cout << "û�к�׺" << endl;
	}
	string url1("https://cplusplus.com/reference/string/string/substr/");
	string protocol, domain, uri;
	size_t i1 = url1.find(':');
	if (i1 != string::npos)
	{
		protocol = url1.substr(0, i1 - 0);
		cout << protocol << endl;
	}
	//���strchar
	size_t i2 = url1.find('/', i1 + 3);
	if (i2 != string::npos)
	{
		domain = url1.substr(i1 + 3, i2 - (i1 + 3));
		cout << domain << endl;

		uri = url1.substr(i2 + 1);
		cout << uri << endl;
	}
	//���strstr
	size_t i3 = url1.find("baidu");
	cout << i3 << endl;
}


//int main()
//{
//	test_string10();
//	return 0;
//}