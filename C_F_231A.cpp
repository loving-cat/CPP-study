#include<iostream>


int main()
{
	int n = 0;
	std::cin >> n;
	int a, b, c,num = 0;
	//int tt = 0;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a >> b >> c;
		if (a && b || a && c || b && c)
			num++;
	}
	std::cout << num << std::endl;

	return 0;
}