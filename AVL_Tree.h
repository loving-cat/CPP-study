#pragma once
#include<assert.h>
#include<iostream>
using namespace std;
//�ڵ�ṹ
//������ K----key   ,  V----- value 
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;//_kv.first �� K---key,_kv.second �� V---value

	int _bf;//balance factor ƽ������

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};
//���ṹ
template<class K, class V>
class AVLTree
{
	//��AVLTreeNode<K,V> һ��Node����
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}

		}
		//���cur�������գ��򴴽��½ڵ�
		cur = new Node(kv);
		//��������keyֵ���ڸ��ڵ��ֵ��������ұ�
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			//�õ�ǰ�ڵ�ĸ���ָ��ָ���ף��ϸ�
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//AVL�Ĳ��룬�ܿ�ƽ��
		//----------------------------------------------------------------
		while (parent)//���µ���
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				//������
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//��������
				//��ת����
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				//1.��ת���������ƽ��
				//2.��ת��������������ĸ߶ȣ��ָ�������ǰһ���ĸ߶ȣ����Զ���һ��û��Ӱ�죬���ü�������
				break;
			}//��������ߵ�������Ǵ���,����֮ǰ��ƽ�����Ӿͳ�������
			else
			{
				assert(false);
			}
		}
		//----------------------------------------------------------------
		return true;
	}
	//��ת�ڵ㣬����Ҫ���ڵ��ȥ
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//���� 
		//1.��û����
		//2.parentû����
		/*parent->_right = subRL;
		subR->_left = parent;*/

		//���_root!=parent ��ô�ʹ���������������еĸ��ڵ����滹�и���
		//����һ���ڵ��¼

		parent->_right = subRL;
		subR->_left = parent;

		Node* parentParent = parent->_parent;

		parent->_parent = subR;
		if (subRL)
			subRL->_parent = parent;
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}//��������
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
		parent->_bf = subR->_bf = 0;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;
			subL->_parent = parentParent;
		}
		subL->_bf = parent->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 0)
		{
			//subRL�Լ���������
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			//subRL������������
			parent->_bf = 0;
			subR->_bf = 1;

			subRL->_bf = 0;

		}
		else if (bf == 1)
		{
			//subRL������������
			parent->_bf = -1;
			subR->_bf = 0;

			subRL->_bf = 0;

		}
		else
		{
			assert(false);
		}
	}
	//����˫��
	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (rightHeight - leftHeight != root->_bf)
		{
			cout << root->_kv.first << "ƽ�������쳣" << endl;
			return false;
		}
		return abs(rightHeight - leftHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);

	}
private:
	Node* _root = nullptr;

};
