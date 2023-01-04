#pragma once

namespace BList
{
	//–°B µœ÷
	struct Node
	{
		struct Node* next;
		struct Node* prev;
		int val;
	};

	struct List
	{
		struct Node* head;
		struct Node* tail;
	};

	int min = 1;
}