#pragma once


//命名空间 -- 命名空间域,只影响使用，不影响生命周期

namespace  AQueue
{
		//小A实现
		struct Node
		{
			struct Node* next;
			int val;
		};
		struct Queue
		{
			struct Node* head;
			struct Node* tail;
		};
		int min = 0;
		void QueueInit(struct Queue* arr)
		{

		}
		void QueuePush(struct Queue* arr, int n)
		{

		}
}