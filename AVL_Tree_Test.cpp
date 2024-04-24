#include<iostream>
#include"AVL_Tree.h"
#include<vector>
using namespace std;

int main()
{
	//int a[] = {16,3,7,11,9,26,18,14,15};
	/*int a[] = { 4,2,6,1,3,5,15,7,16,14 };

	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e,e));
	}
	t.InOrder();
	cout << t.IsBalance() << endl;*/
	const int N = 30;
	vector<int> v;
	v.reserve(N);
	//srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand());
		cout << v.back() << endl;
	}

	AVLTree<int, int> t;
	for (auto e : v)
	{
		if (e == 14604)
		{
			int x = 0;
		}

		t.Insert(make_pair(e, e));
		cout << "Insert:" << e << "->" << t.IsBalance() << endl;
	}

	cout << t.IsBalance() << endl;


	return 0;
}