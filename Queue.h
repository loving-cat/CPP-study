#pragma once


//�����ռ� -- �����ռ���,ֻӰ��ʹ�ã���Ӱ����������

namespace  AQueue
{
		//СAʵ��
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