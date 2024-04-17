#include<iostream>
using namespace std;

//多态，不同的调用不同的结果
//多态的条件
//1.虚函数重写
//2.父类的指针或者引用去调用

//虚函数重写
//继承关系中父子的两个虚函数，要求有三同 （函数名/参数/返回值）才能构成虚函数重写
//virtual 只能修饰成员
//三同（函数名/参数/返回值）的例外：协变->返回值可以不同，但是必须是父子类关系的指针或引用
//派生类重写的虚函数函数可以不加virtual
//class Person {
//public:
//	//virtual Person* BuyTicket()
//
//	virtual void BuyTicket() 
//	{ 
//		cout << "买票-全价" << endl; 
//	}
//	virtual ~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//};
//class Student : public Person {
//public:
//	//virtual Student* BuyTicket()
//	/*void BuyTicket()
//	{
//
//	}*/
//	virtual void BuyTicket() 
//	{ 
//		cout << "买票-半价" << endl; 
//	}
//	~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//	/*注意：在重写基类虚函数时，派生类的虚函数在不加virtual关键字时，虽然也可以构成重写(因
//	为继承后基类的虚函数被继承下来了在派生类依旧保持虚函数属性),但是该种写法不是很规范，不建议
//	这样使用*/
//	/*void BuyTicket() { cout << "买票-半价" << endl; }*/
//};
//void Func(Person& p)//父类的引用
//{
//	p.BuyTicket();
//}
//int main()
//{
//	/*Person ps;
//	Student st;
//	Func(ps);
//	Func(st);*/
//
//	Person* p = new Person;
//	//析构函数是虚函数，才能正确调用析构函数
//	//p->destrutor()+operator delete(p)
//	delete p;
//	p = new Student;
//	//p->destrutor()+operator delete(p)
//	delete p;
//	return 0;
//}

//抽象类
//class Car
//{
//public:
	//纯虚函数
	//1.间接强制去派生类去重写
	//2.抽象类-不能实例化对象，必须重写
//virtual void Drive() = 0;
//};
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-操控" << endl;
//	}
//};
//void func(Car& ptr)
//{
//	ptr.Drive();
//}
//void Test()
//{
//	Car* pBenz = new Benz;
//	pBenz->Drive();
//	Car* pBMW = new BMW;
//	pBMW->Drive();
//}
//int main()
//{
//	Benz b;
//	BMW C;
//	Test();
//	func(b);
//	func(C);
//	return 0;
//}

//打印虚表
typedef void (*VFUNC)();
//void PrintVFT(VFUNC a[])
void PrintVFT(VFUNC * a)
{
	//linux下的话要写死，因为linux里面没有00 00 00 00，有多少个写多少个
	for (size_t i = 0; a[i] != 0; ++i)
	{
		printf("[%d]:%p\n", i, a[i]);
	}
	printf("\n");
}
int main()
{
	void(*f1)();
	VFUNC f2;
	
	return 0;
}