#pragma once
#include<iostream>
using namespace std;
template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
	BSTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};
	
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)//插入值大于原有值
			{
				cur = cur->_right;//往右走
			}
			else if (cur->_key > key)//插入值小于原有值
			{
				cur = cur->_left;//往左走
			}
			else
			{
				//搜索二叉树一般不允许有重复值，直接返回错误
				return false;
			}
		}
		//cur是局部变量，无法链接起来
		//cur = new Node(key);//插入值
		//解决方案，用一个值存放父节点parent
		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}
	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	//可用的方法---替换法
	//左子树的最大节点 or 右子树的最小节点
	//				最右节点					最左节点
	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//相等代表找到，可以开始删除
				//right:左为空让父亲的左指向我的右，left:左为空让父亲的右指向我的右
				//一种可能，根没父亲
				//左为空，把我的右边托付给我父亲，或者让右边变成根
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
				}
				else if(cur->_right == nullptr)//右为空，把左边托付给父亲or变成根
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
				}
				else
				{//左右都不为空
				 //默认找右树的最小节点(最左节点---他的左节点肯定为空)
					Node* subLeft = cur->_right;
					Node* parent_Two = cur;
					while (subLeft->_left)
					{
						parent_Two = subLeft;
						subLeft = subLeft->_left;
					}
					swap(cur->_key, subLeft->_key);
					// 删除替代节点：如果替代节点是其父节点的左孩子，
					// 则更新父节点的左孩子为替代节点的右孩子
					if (subLeft == parent_Two->_left)
						parent_Two->_left = subLeft->_right;//此时subLeft替代节点是最左节点只能让父节点去拿到替代节点的右节点
					// 否则，更新父节点的右孩子为替代节点的右孩子，此时subLeft == parent_Two->right
					else
						parent_Two->_right = subLeft->_right;
				}
				return true;
			}
		}
		return false;
	}
	//中序遍历 有序
	//二叉树的递归都需要参数，可以直接套娃，外面就不需要传参数调用了
	
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool FindR(const K& key)
	{
		return _FindR(_root,key);
	}
	bool InsertR(const K& key)
	{
		return _Insert(_root,key);
	}
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}
private:
	//Node*& root的本质就是在递归的时候,是父亲节点-左指针or右指针的别名
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
			return false;
		if (root->_key < key)
			return _EraseR(root->_right, key);
		else if (root->_key > key)
			return _EraseR(root->_left, key);
		else
		{
			//删除
			//左为空//相当于是root->right->left
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;
				return true;
			}//右为空
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;
				return true;
			}//左右都不为空
			else
			{
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{
					subLeft = subLeft->_left;
				}
				swap(root->_key, subLeft->_key);
				//交换后 整个树就不是搜索二叉树了
				//可以转换成在子树去递归删除（子树还是搜索二叉树）
				return _EraseR(root->_right, key);
			}
		}
	}
	//递归思想
	//比root->key大，转换成右子树插入的子问题
	//比root->key小，转换成左子树插入的子问题

	//无父亲，怎么链接呢，为什么Node* root ->Node*& root可以解决链接问题？
	//由于Node*& root相当于_root左右指针的一个别名去使用
	//因为是递归，所以每次引用相当于是在新的作用域引用，最后一次生效了
	bool _InsertR(Node*& root, const K& key)
	{			
		if (root == nullptr)
		{
			root = new Node(key);//第一个节点相当于给了_root
			return true;
		}
		if (root->_key < key)
			//						与下同理
			return _InsertR(root->_right, key);
		else if (root->_key > key)
			//						Node*& root 此时相当于 root->left别名
			return _InsertR(root->_left, key);
		else
			return false;
	}
	bool _FindR(Node* root,const K& key)
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _FindR(root->_right,key);
		}
		else if(root->_key>key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return true;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
private:

	Node* _root = nullptr;
};
