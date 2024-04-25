#pragma once
#include<iostream>
#include<assert.h>

enum Colour
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Colour _col;
	RBTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{}
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
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
		cur->_col
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
		//----------------------------------------------------------------
		return true;
	}
private:
	Node* _root = nullptr;
};