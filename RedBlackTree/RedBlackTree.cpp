// RedBlackTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <math.h>

#define RB_RED 0
#define RB_BLACK 1

//红黑树结点
template <typename T>
struct RBNode
{
	T data;
	RBNode<T> *left;
	RBNode<T> *right;
	RBNode<T> *parent;
	int color; //颜色

	RBNode<T>(const T theData, RBNode<T>* nil) : data(theData), left(nil), right(nil), parent(nil), color(RB_RED) {}
};

//R-B Tree
template <typename T>
class RBTree
{ 
public:
	RBNode<T> *NIL;
	RBTree<T>();
	~RBTree<T>();
	RBNode<T> *root;
	//插入结点
	void Insert(T x);
	//删除结点
	bool Delete(T x);
	//查找是否存在给定值的结点
	bool Contains(RBNode<T> *t, const T x);
	//中序遍历
	void InorderTraversal(RBNode<T> *t);
	//前序遍历
	void PreorderTraversal(RBNode<T> *t);
private:
	//求树的高度
	int GetHeight(RBNode<T> *t);
	void _erase(RBNode<T>*& t);
	void _transplant(RBNode<T> *p, RBNode<T> *q);
	RBNode<T> * Cut(RBNode<T> * p);
	RBNode<T> * _search(RBNode<T> * p, const T data);
	void _left_rotate(RBNode<T> *t);
	void _right_rotate(RBNode<T> *t);
	void _adjust(RBNode<T> *t);
};



template<typename T>
RBTree<T>::RBTree()
{
	NIL = new RBNode<T>(0, NULL);
	NIL->color = RB_BLACK;
	root = NIL;
}

template<typename T>
RBTree<T>::~RBTree()
{
	_erase(root);
}

template<typename T>
void RBTree<T>::_erase(RBNode<T>*& t)
{
	if (t != NIL)
	{
		_erase(t->left);
		_erase(t->right);
		delete t;
	}
}

template<typename T>
void RBTree<T>::_transplant(RBNode<T> *p, RBNode<T> *q)
{
	if (p == NIL)
		return;

	if (p->parent == NIL)
		root = q;
	else if (p == p->parent->left)
		p->parent->left = q;
	else
		p->parent->right = q;

	if (q != NIL)
		q->parent = p->parent;
}

template<typename T>
RBNode<T>* RBTree<T>::Cut(RBNode<T>* p)
{
	if (p == NIL)
		return NIL;

	if (p->parent != NIL)
	{
		RBNode<T>* parent = p->parent;

		if (parent->left == p)
			parent->left = NIL;
		else if (parent->right == p)
			parent->right = NIL;
	}

	return p;
}

template<typename T>
RBNode<T>* RBTree<T>::_search(RBNode<T>* p, const T data)
{
	RBNode<T>* q = p;

	while (q != NIL && q->data != data)
	{
		if (q->data > data)
			q = q->left;
		else
			q = q->right;
	}

	return q;
}

template<typename T>
void RBTree<T>::_left_rotate(RBNode<T>* t)
{
	if (t == NIL || t->right == NIL)
		return;

	RBNode<T>* p = t->right;
	Cut(p);

	_transplant(t, p);

	t->right = p->left;

	if (p->left != NIL)
		p->left->parent = t;

	p->left = t;
	t->parent = p;
}

template<typename T>
void RBTree<T>::_right_rotate(RBNode<T>* t)
{
	if (t == NIL || t->left == NIL)
		return;

	RBNode<T>* p = t->left;
	Cut(p);

	_transplant(t, p);

	t->left = p->right;

	if (p->right != NIL)
		p->right->parent = t;

	p->right = t;
	t->parent = p;
}

template<typename T>
void RBTree<T>::_adjust(RBNode<T>* t)
{
	while (t->parent->color == RB_RED)
	{
		// 父左叔右
		if (t->parent == t->parent->parent->left)
		{
			//父红叔红
			if (t->parent->parent->right->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->right->color = RB_BLACK;
				t = t->parent->parent;
				t->color = RB_RED;
			}
			else if (t->parent != NIL && t->parent->parent != NIL)
			{
				//父红叔黑
				//子位于父右边，左旋
				if (t == t->parent->right)
				{
					t = t->parent;
					_left_rotate(t);
				}

				t->parent->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				_right_rotate(t->parent->parent);
			}
		}
		// 父右叔左
		else
		{
			//父红叔红
			if (t->parent->parent->left->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->left->color = RB_BLACK;
				t = t->parent->parent;
				t->color = RB_RED;
			}
			else if(t->parent != NIL && t->parent->parent != NIL)
			{

				//父红叔黑
				//子位于父左边，右旋
				if (t == t->parent->left)
				{
					t = t->parent;
					_right_rotate(t);
				}

				t->parent->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				_left_rotate(t->parent->parent);
			}
		}
	}

	root->color = RB_BLACK;
}

template<typename T>
int RBTree<T>::GetHeight(RBNode<T>* t)
{
	if (t != NIL)
	{
		int left = GetHeight(t->left);
		int right = GetHeight(t->right);

		return (left > right ? left : right) + 1;
	}

	return 0;
}


template<typename T>
void RBTree<T>::Insert(T x)
{
	RBNode<T>* p = root;
	RBNode<T> * q = NIL;

	while (p != NIL)
	{
		q = p;
		if (x > p->data)
			p = p->right;
		else if (x < p->data)
			p = p->left;
		else
			return;
	}

	RBNode<T>* node = new RBNode<T>(x, NIL);

	if(q == NIL)
	{
		root = node;
	}
	else if(x > q->data)
		q->right = node;
	else
		q->left = node;

	node->parent = q;

	_adjust(node);
}

template<typename T>
bool RBTree<T>::Delete(T x)
{
	return false;
}

template<typename T>
void RBTree<T>::InorderTraversal(RBNode<T>* t)
{
	if (t != NIL)
	{
		InorderTraversal(t->left);
		printf("%d ", t->data);
		InorderTraversal(t->right);
	}
}

template<typename T>
void RBTree<T>::PreorderTraversal(RBNode<T>* t)
{
	if (t != NIL)
	{
		printf("%d ", t->data);
		InorderTraversal(t->left);
		InorderTraversal(t->right);
	}
}

template<typename T>
bool RBTree<T>::Contains(RBNode<T>* t, const T x)
{
	return _search(t, x) != NIL;
}

int main()
{
	int datas[10] = { 3,2,1,4,5,6,10,9,8,7 };

	RBTree<int> rbTree;

	for (int i = 0; i < 10; ++i)
		rbTree.Insert(datas[i]);

	rbTree.InorderTraversal(rbTree.root);

	printf("\n");

	return 0;
}