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
			if (cur->_key < key)//����ֵ����ԭ��ֵ
			{
				cur = cur->_right;//������
			}
			else if (cur->_key > key)//����ֵС��ԭ��ֵ
			{
				cur = cur->_left;//������
			}
			else
			{
				//����������һ�㲻�������ظ�ֵ��ֱ�ӷ��ش���
				return false;
			}
		}
		//cur�Ǿֲ��������޷���������
		//cur = new Node(key);//����ֵ
		//�����������һ��ֵ��Ÿ��ڵ�parent
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
	//���õķ���---�滻��
	//�����������ڵ� or ����������С�ڵ�
	//				���ҽڵ�					����ڵ�
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
				//��ȴ����ҵ������Կ�ʼɾ��
				//right:��Ϊ���ø��׵���ָ���ҵ��ң�left:��Ϊ���ø��׵���ָ���ҵ���
				//һ�ֿ��ܣ���û����
				//��Ϊ�գ����ҵ��ұ��и����Ҹ��ף��������ұ߱�ɸ�
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
				else if(cur->_right == nullptr)//��Ϊ�գ�������и�������or��ɸ�
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
				{//���Ҷ���Ϊ��
				 //Ĭ������������С�ڵ�(����ڵ�---������ڵ�϶�Ϊ��)
					Node* subLeft = cur->_right;
					Node* parent_Two = cur;
					while (subLeft->_left)
					{
						parent_Two = subLeft;
						subLeft = subLeft->_left;
					}
					swap(cur->_key, subLeft->_key);
					// ɾ������ڵ㣺�������ڵ����丸�ڵ�����ӣ�
					// ����¸��ڵ������Ϊ����ڵ���Һ���
					if (subLeft == parent_Two->_left)
						parent_Two->_left = subLeft->_right;//��ʱsubLeft����ڵ�������ڵ�ֻ���ø��ڵ�ȥ�õ�����ڵ���ҽڵ�
					// ���򣬸��¸��ڵ���Һ���Ϊ����ڵ���Һ��ӣ���ʱsubLeft == parent_Two->right
					else
						parent_Two->_right = subLeft->_right;
				}
				return true;
			}
		}
		return false;
	}
	//������� ����
	//�������ĵݹ鶼��Ҫ����������ֱ�����ޣ�����Ͳ���Ҫ������������
	
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
	//Node*& root�ı��ʾ����ڵݹ��ʱ��,�Ǹ��׽ڵ�-��ָ��or��ָ��ı���
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
			//ɾ��
			//��Ϊ��//�൱����root->right->left
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;
				return true;
			}//��Ϊ��
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;
				return true;
			}//���Ҷ���Ϊ��
			else
			{
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{
					subLeft = subLeft->_left;
				}
				swap(root->_key, subLeft->_key);
				//������ �������Ͳ���������������
				//����ת����������ȥ�ݹ�ɾ������������������������
				return _EraseR(root->_right, key);
			}
		}
	}
	//�ݹ�˼��
	//��root->key��ת���������������������
	//��root->keyС��ת���������������������

	//�޸��ף���ô�����أ�ΪʲôNode* root ->Node*& root���Խ���������⣿
	//����Node*& root�൱��_root����ָ���һ������ȥʹ��
	//��Ϊ�ǵݹ飬����ÿ�������൱�������µ����������ã����һ����Ч��
	bool _InsertR(Node*& root, const K& key)
	{			
		if (root == nullptr)
		{
			root = new Node(key);//��һ���ڵ��൱�ڸ���_root
			return true;
		}
		if (root->_key < key)
			//						����ͬ��
			return _InsertR(root->_right, key);
		else if (root->_key > key)
			//						Node*& root ��ʱ�൱�� root->left����
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
