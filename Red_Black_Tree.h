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
//����д��

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
	//set ���� key
	//map ���� pair
	Ref& operator*()
	{
		return _node->_data;
	}
	Ptr* operator->()
	{
		return &_node->_data;
	}
	//������ �� ������
	//1.��Ϊ�գ������������ҽڵ�
	//2.��Ϊ�գ����ŵ�����·���Һ����Ǹ����ҵ��ĸ�����

	Self& operator--();
	Self& operator++()
	{
		if (_node->_right)
		{
			//��һ������������������ڵ�
			Node* cur = _node->_right;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			//�ҵ�����ڵ��node
			_node = cur;
		}
		else
		{
			//������ �� ������
			//��Ϊ�գ��Һ����Ǹ�������Ǹ�����
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

//ʹ�÷º���������ȡdata�ھ������ݵķ���
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
		//ʹ������ڵ㹹�������
		return iterator(cur);
	}
	const_iterator begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		//ʹ������ڵ㹹�������
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
			//ֱ���õ����͵��ַ���,��ǿ�����ܴ�����ȥdata�����ݵķ��������ǲ���
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
		//���cur�������գ��򴴽��½ڵ�
		cur = new Node(data);
		Node* newnode = cur;
		//�����ڵ����ɫ
		cur->_col = RED;
		//��������keyֵ���ڸ��ڵ��ֵ��������ұ�
		if (kot(parent->_data) < kot(data))
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
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					//��ɫ
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϸ��´���
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						//����
							//			g
							//		p
							// c
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//˫��
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
					//��ɫ
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϴ���
					cur = grandfather;

				}
				else
				{
					//uncle�����ڻ���Ϊ��
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
	//���ڵ�->��ǰ�ڵ�����·���ĺ�ɫ�ڵ������
	bool Check(Node* root,int blacknum,const int refVal)
	{
		if (root == nullptr)
		{
			/*cout << blacknum << endl;*/
			if (blacknum != refVal)
			{
				cout << "���ں�ɫ�ڵ���������ȵ�·��" << endl;
				return false;
			}
			return  true;
		}
		if (root->_col == RED&&root->_parent->_col==RED)
		{
			//���һ���и���
			cout << "�������ĺ�ɫ�ڵ�" << endl;
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
		//�ο�ֵ
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