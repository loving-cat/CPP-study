#include<iostream>
using namespace std;

//��̬����ͬ�ĵ��ò�ͬ�Ľ��
//��̬������
//1.�麯����д
//2.�����ָ���������ȥ����

//�麯����д
//�̳й�ϵ�и��ӵ������麯����Ҫ������ͬ ��������/����/����ֵ�����ܹ����麯����д
//virtual ֻ�����γ�Ա
//��ͬ��������/����/����ֵ�������⣺Э��->����ֵ���Բ�ͬ�����Ǳ����Ǹ������ϵ��ָ�������
//��������д���麯���������Բ���virtual
//class Person {
//public:
//	//virtual Person* BuyTicket()
//
//	virtual void BuyTicket() 
//	{ 
//		cout << "��Ʊ-ȫ��" << endl; 
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
//		cout << "��Ʊ-���" << endl; 
//	}
//	~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//	/*ע�⣺����д�����麯��ʱ����������麯���ڲ���virtual�ؼ���ʱ����ȻҲ���Թ�����д(��
//	Ϊ�̳к������麯�����̳������������������ɱ����麯������),���Ǹ���д�����Ǻܹ淶��������
//	����ʹ��*/
//	/*void BuyTicket() { cout << "��Ʊ-���" << endl; }*/
//};
//void Func(Person& p)//���������
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
//	//�����������麯����������ȷ������������
//	//p->destrutor()+operator delete(p)
//	delete p;
//	p = new Student;
//	//p->destrutor()+operator delete(p)
//	delete p;
//	return 0;
//}

//������
//class Car
//{
//public:
	//���麯��
	//1.���ǿ��ȥ������ȥ��д
	//2.������-����ʵ�������󣬱�����д
//virtual void Drive() = 0;
//};
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-����" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-�ٿ�" << endl;
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

//��ӡ���
typedef void (*VFUNC)();
//void PrintVFT(VFUNC a[])
void PrintVFT(VFUNC * a)
{
	//linux�µĻ�Ҫд������Ϊlinux����û��00 00 00 00���ж��ٸ�д���ٸ�
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