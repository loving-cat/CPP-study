#include<iostream>
#include<string>
using namespace std;

////父类
//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name: " << _name <<endl;
//		cout << "_age: " << _age << endl;
//	}
//	Person(string name = "xl", int age=21)
//		:_name(name)
//		,_age(age)
//	{}
//	
////protected://在子类可见（可用）只防外人
////不想被子类继承就私有，在子类不可见（不能用）不仅防外人还能防儿子
//private:
//	string _name;
//	int _age;
//};
//
//class Student : public Person
//{
//public:
//	void func()
//	{
//		//不可见
//		//cout << _name << endl;
//		cout << "void func" << endl;
//	}
//protected:
//	int _stuid;
//};
//class teacher : public Person
//{
//protected:
//	int _jobid;
//};
//
//int main()
//{
//	/*Student one;
//	one.Print();*/
//	double d = 1.1;
//	int i = d;//隐式类型转换
//
//	Student Two;
//	Person p = Two;//天然支持，不存在隐式类型转换的发生
//	Person& rp = Two;//Two子类切出来的部分的别名
//	Person* ptrp = &Two;
//	return 0;
//}


//class Person
//{
//protected:
//	string _name = "xlz";
//	int _num = 111;
//};
//class Student : public Person
//{
//public:
//	void Print()
//		{
//		//子类和父类有同名成员，子类成员将屏蔽父类对同名成员的直接访问，
//		// 这种情况叫 隐藏，也叫重定义,只需要函数名相同就构成  隐藏
//		//在继承体系中最好不要定义同名成员
//			cout << Person::_num << endl;
//			cout << _num << endl;
//
//		}
//protected:
//	int _num = 999;
//};
//class A
//{
//public:
//	void fun()
//	{
//		cout << "func()" << endl;
//	}
//};
//class B : public A
//{
//public:
//	void fun(int i)
//	{
//		A::fun();
//		cout << "func(int i)->" << i << endl;
//	}
//};
//
////A.两个fun构成函数重载  err //函数重载必须在同一个作用域里
////B.两个fun构成隐藏	✓
////C.编译错误
////D.以上说法都不对
//void Test()
//{
//	/*B b;
//	b.fun(10);*/
//	B b;
//	//b.fun();//err
//	b.A::fun();
//};
//int main()
//{
//	Student Three;
//	Three.Print();
//	return 0;
//}


////派生类中的默认成员函数
//class Person
//{
//public:
//	Person(const char* name = "peter")
//		: _name(name)
//	{
//		cout << "Person()" << endl;
//	}
//
//	Person(const Person& p)
//		: _name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//
//	Person& operator=(const Person& p)
//	{
//		cout << "Person operator=(const Person& p)" << endl;
//		if (this != &p)
//			_name = p._name;
//
//		return *this;
//	}
//
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//public:
//	Student(const char* name,int num)
//		:Person(name)//调用父类的构造函数初始化
//		,_num(num)
//	{}
//	Student(const Student& s)//拷贝构造
//		:Person(s)
//		,_num(s._num)
//	{}
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s);
//			_num = s._num;
//		}
//		cout << "Student& operator=(const Student& s)" << endl;
//		return *this;
//	}
//	//析构函数会被处理成Destructor
//	~Student()
//	{
//		//~Person();
//		cout << "~Student()" << endl;
//	}
//	//子类析构函数完成时，会自动调用父类的析构函数，保证先析构子再析构父
//protected:
//	int _num; //学号
//	int* Ptr;
//};
//int main()
//{
//	Student s1("张三",18);
//	Student s2(s1);
//	Person p = s1;//实际调用的是父类的拷贝构造
//	s1 = s2;
//	return 0;
//}


//友元关系不会被继承
//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//void main()
//{
//	Person p;
//	Student s;
//	Display(p, s);
//}

////静态成员 ---继承
//class Person
//{
//public:
//	Person() { ++_count; }
////protected:
//	string _name; // 姓名
//public:
//	static int _count; // 统计人的个数。
//};
//
//int Person::_count = 0;
//
//class Student : public Person
//{
//protected:
//	int _stuNum; // 学号
//};
//
//class Graduate : public Student
//{
//protected:
//	string _seminarCourse; // 研究科目
//};
//void TestPerson()
//{
//	Student s1;
//	Student s2;
//	Student s3;
//	Graduate s4;
//	cout << " 人数 :" << Person::_count << endl;
//	Student::_count = 0;
//	cout << " 人数 :" << Person::_count << endl;
//}
//int main()
//{
//	Person p;
//	Person s;
//	////不在一个地址空间
//	//cout << &(p._name) << endl;	//000000E0E50FFBA8
//	//cout << &(s._name) << endl;	//000000E0E50FFBE8
//	////是同一个值,count 是静态成员
//	//cout << &(p._count) << endl;	//00007FF61D6234C4
//	//cout << &(p._count) << endl;	//00007FF61D6234C4
//
//	Graduate g1;
//	Graduate g2;
//	//子类创建对象就必须要调用父类
//	//可以用对象访问，也可以用类去访问,而且都是同一个
//	cout << Person::_count << endl;
//	cout << Graduate::_count << endl;
//	return 0;
//}

////实现一个不能被继承的类
//class A
//{
// pubilc:
//	static A CreateOBJ()
// {
//		return A();
// }
//	//①把构造函数or析构函数私有，则不能继承
//private:
//	A()
//	{}
//	~A()
//	{}
//};
//class B :public A
//{
//
//};
//
//int main()
//{
//	return 0;
//}

////复杂的菱形继承及菱形虚拟继承
////多继承可能会导致菱形继承
//class Person
//{
//public:
//	string _name; // 姓名
//};
////虚继承 解决数据冗余和二义性
//class Student : virtual public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//void main()
//{
//	// 这样会有二义性无法明确知道访问的是哪一个
//	Assistant a;
//	a._name = "peter";
//	// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
//	a.Student::_name = "xxx";
//	a.Teacher::_name = "yyy";
//	cout << a.Student::_name << endl;
//}
