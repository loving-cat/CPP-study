#pragma once
#include<assert.h>
#include<iostream>
using namespace std;
//节点结构
//三叉链 K----key   ,  V----- value 
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;//_kv.first 是 K---key,_kv.second 是 V---value

	int _bf;//balance factor 平衡因子

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};
//树结构
template<class K, class V>
class AVLTree
{
	//给AVLTreeNode<K,V> 一个Node别名
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
		//如果cur遍历到空，则创建新节点
		cur = new Node(kv);
		//如果插入的key值大于父节点的值，则插入右边
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			//让当前节点的父亲指针指向父亲，认父
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//AVL的插入，管控平衡
		//----------------------------------------------------------------
		while (parent)//更新到根
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
				//往上走
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//出现问题
				//旋转调整
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
				//1.旋转让这颗子树平衡
				//2.旋转降低了这颗子树的高度，恢复到插入前一样的高度，所以对上一层没有影响，不用继续更新
				break;
			}//如果代码走到这里就是错误,插入之前，平衡因子就出问题了
			else
			{
				assert(false);
			}
		}
		//----------------------------------------------------------------
		return true;
	}
	//旋转节点，所以要传节点过去
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//问题 
		//1.根没处理
		//2.parent没处理
		/*parent->_right = subRL;
		subR->_left = parent;*/

		//如果_root!=parent 那么就代表在这个子问题中的父节点上面还有个根
		//创建一个节点记录

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
		}//子问题解决
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
			//subRL自己就是新增
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			//subRL的左子树新增
			parent->_bf = 0;
			subR->_bf = 1;

			subRL->_bf = 0;

		}
		else if (bf == 1)
		{
			//subRL的右子树新增
			parent->_bf = -1;
			subR->_bf = 0;

			subRL->_bf = 0;

		}
		else
		{
			assert(false);
		}
	}
	//左右双旋
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
			cout << root->_kv.first << "平衡因子异常" << endl;
			return false;
		}
		return abs(rightHeight - leftHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);

	}
private:
	Node* _root = nullptr;

};
