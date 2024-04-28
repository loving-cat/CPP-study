#pragma once
//
#include<iostream>
#include<assert.h>

enum Colour
{
	RED,
	BLACK
};
  
//template<class K,class V>
//struct RBTreeNode
//{
//	RBTreeNode<K, V>* _left;
//	RBTreeNode<K, V>* _right;
//	RBTreeNode<K, V>* _parent;
//	pair<K, V> _kv;
//	Colour _col;
//	RBTreeNode(const pair<K,V>& kv)
//		:_left(nullptr)
//		,_right(nullptr)
//		,_parent(nullptr)
//		,_kv(kv)
//		,_col(RED)
//	{}
//};
//泛型写法

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	//pair<K, V> _kv;
	T _data;
	Colour _col;
	RBTreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(RED)
	{}
};

template<class T,class Ref,class Ptr>
struct _TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef _TreeIterator<T, Ref, Ptr> Self;
	Node* _node;

	_TreeIterator(Node* node)
		:_node(node)
	{}
	//set 就是 key
	//map 就是 pair
	Ref& operator*()
	{
		return _node->_data;
	}
	Ptr* operator->()
	{
		return &_node->_data;
	}
	//右子树 根 左子树
	//1.左不为空，左子树的最右节点
	//2.左为空，沿着到根的路径找孩子是父亲右的哪个祖先

	Self& operator--();
	Self& operator++()
	{
		if (_node->_right)
		{
			//下一个就是右子树的最左节点
			Node* cur = _node->_right;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			//找到最左节点给node
			_node = cur;
		}
		else
		{
			//左子树 根 右子树
			//右为空，找孩子是父亲左的那个祖先
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
};

//使用仿函数进行拿取data内具体数据的方法
//Set->RBTree<K,K,SetKeyOfT> _t;
//Map->RBTree<K,pair<const K,T>,MapKeyOfT> _t
template<class K, class T,class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef _TreeIterator<T,T&,T*> iterator;
	typedef _TreeIterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		//使用最左节点构造迭代器
		return iterator(cur);
	}
	const_iterator begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		//使用最左节点构造迭代器
		return const_iterator(cur);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	const_iterator end() const
	{
		return const_iterator(nullptr);
	}
	//pair<iterator,bool> Insert(const T& data)
	pair<Node*,bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(_root,true);
		}
		Node* parent = nullptr;
		Node* cur = _root;
		KeyOfT kot;
		while (cur)
		{
			//直接拿到类型的字符串,勉强算是能处理拿去data内数据的方法，但是不好
			/*if (typeid(cur->_data).name == K)
			{

			}*/
			
			if (kot(cur->_data)< kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(_root, false);
			}
		}
		//如果cur遍历到空，则创建新节点
		cur = new Node(data);
		Node* newnode = cur;
		//新增节点给红色
		cur->_col = RED;
		//如果插入的key值大于父节点的值，则插入右边
		if (kot(parent->_data) < kot(data))
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
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					//变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续向上更新处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						//单旋
							//			g
							//		p
							// c
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						//			g
						//		p
						//			c
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;

					}
					break;
				}
			}
			else //parent == grandfather->_right
			{
				//			g
				//		u		p
				//					c
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					//变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续往上处理
					cur = grandfather;

				}
				else
				{
					//uncle不存在或者为黑
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//			g
						//		u		p
						//			c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
				}
			}
		}
		_root->_col = BLACK;
		//----------------------------------------------------------------
		return make_pair(newnode, true);
	}
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
	}
	void InOrder()
	{
		return _InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << endl;
		_InOrder(root->_right);
	}
	//根节点->当前节点这条路径的黑色节点的数量
	bool Check(Node* root,int blacknum,const int refVal)
	{
		if (root == nullptr)
		{
			/*cout << blacknum << endl;*/
			if (blacknum != refVal)
			{
				cout << "存在黑色节点数量不相等的路径" << endl;
				return false;
			}
			return  true;
		}
		if (root->_col == RED&&root->_parent->_col==RED)
		{
			//红的一定有父亲
			cout << "有连续的红色节点" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			++blacknum;
		}
		return Check(root->_left,blacknum,refVal)
			&& Check(root->_right,blacknum,refVal);
	}
	bool IsBalance()
	{
		if (_root == nullptr)
			return true;
		if (_root->_col == RED)
			return false;
		//参考值
		int refVal = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++refVal;
			}
			cur = cur->_left;
		}
		int balcknum = 0;
		return Check(_root,balcknum,refVal);
	}
	int Height()
	{
		return _Height(_root);
	}
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

	}
	size_t Size()
	{
		return _Size(_root);
	}
	size_t _Size(Node* root)
	{
		if (root == nullptr)
			return 0;
		return _Size(root->_left)
			+ _Size(root->_right) + 1;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
				return cur;
		}
		return NULL;
	}
private:
	Node* _root = nullptr;
};