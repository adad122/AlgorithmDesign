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
	void _delete_adjust(RBNode<T> *t);
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
//
//(1) 每个节点或者是黑色，或者是红色。
//(2) 根节点是黑色。
//(3) 每个叶子节点是黑色。[注意：这里叶子节点，是指为空的叶子节点！]
//(4) 如果一个节点是红色的，则它的子节点必须是黑色的。
//(5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。
//
template<typename T>
void RBTree<T>::_adjust(RBNode<T>* t)
{
	while (t->parent->color == RB_RED)
	{
		// 父左&&叔右
		if (t->parent == t->parent->parent->left)
		{
			//1. 父红&&叔红
			//父黑
			//叔黑
			//爷红
			//观察点上浮至爷节点
			if (t->parent->parent->right->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->right->color = RB_BLACK;
				t = t->parent->parent;
				t->color = RB_RED;
			}
			else if (t->parent != NIL && t->parent->parent != NIL)
			{
				//2. 父红叔黑&&子位于父右边
				//观察点上浮
				//观察点左旋
				if (t == t->parent->right)
				{
					t = t->parent;
					_left_rotate(t);
				}

				//3. 父红叔黑&&子位于父左边
				//父黑
				//爷红
				//爷右旋
				t->parent->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				_right_rotate(t->parent->parent);
			}
		}
		// 父右&&叔左
		else
		{
			//1. 父红&&叔红
			//父黑
			//叔黑
			//爷红
			//观察点上浮到爷节点
			if (t->parent->parent->left->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->left->color = RB_BLACK;
				t = t->parent->parent;
				t->color = RB_RED;
			}
			else if(t->parent != NIL && t->parent->parent != NIL)
			{

				//2. 父红叔黑&&子位于父左边
				//观察点上浮
				//观察点右旋
				if (t == t->parent->left)
				{
					t = t->parent;
					_right_rotate(t);
				}

				//3. 父红叔黑&&子位于父右边
				//父黑
				//爷红
				//爷左旋
				t->parent->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				_left_rotate(t->parent->parent);
			}
		}
	}

	root->color = RB_BLACK;
}

template<typename T>
void RBTree<T>::_delete_adjust(RBNode<T>* t)
{
	while (t != root && t->color == RB_BLACK)
	{
		//位于左边
		if (t == t->parent->left)
		{
			RBNode<T>* p = t->parent->right;
			//1. 兄弟红
			//兄黑
			//父红
			//父左旋
			//重定位新兄弟
			if (p->color == RB_RED)
			{
				p->color = RB_BLACK;
				t->parent->color = RB_RED;
				_left_rotate(t->parent);
				p = t->parent->right;
			}

			//2. 兄弟黑&&兄弟左孩黑&&兄弟右孩黑
			//兄弟红
			//观察点上浮
			if (p->left->color == RB_BLACK && p->right->color == RB_BLACK)
			{
				p->color = RB_RED;
				t = t->parent;
			}
			else
			{
				//3. 兄弟黑&&兄弟左孩红&&兄弟右孩黑
				//兄弟左孩黑
				//兄弟红
				//兄弟右旋
				//重新定位新兄弟
				if (p->right->color == RB_BLACK)
				{
					p->left->color = RB_BLACK;
					p->color = RB_RED;
					_right_rotate(p);
					p = t->parent->right;
				}

				//4. 兄弟黑&&兄弟右孩红
				//兄弟染父色
				//父黑
				//右孩黑
				//父左旋
				//所有操作结束
				p->color = t->parent->color;
				t->parent->color = RB_BLACK;
				p->right->color = RB_BLACK;
				_left_rotate(t->parent);

				t = root;
			}
		}
		//位于右边
		else
		{
			RBNode<T>* p = t->parent->left;
			//1. 兄弟红
			//兄黑
			//父红
			//父右旋
			//重定位新兄弟
			if (p->color == RB_RED)
			{
				p->color = RB_BLACK;
				t->parent->color = RB_RED;
				_right_rotate(t->parent);
				p = t->parent->left;
			}
			//2. 兄弟黑&&兄弟左孩黑&&兄弟右孩黑
			//兄弟红
			//观察点上浮
			if (p->left->color == RB_BLACK && p->right->color == RB_BLACK)
			{
				p->color = RB_RED;
				t = t->parent;
			}
			else
			{
				//3. 兄弟黑&&兄弟右孩红&&兄弟左孩黑
				//兄弟右孩黑
				//兄弟红
				//兄弟左旋
				//重新定位新兄弟
				if (p->left->color == RB_BLACK)
				{
					p->right->color = RB_BLACK;
					p->color = RB_RED;
					_left_rotate(p);
					p = t->parent->left;
				}

				//4. 兄弟黑&&兄弟左孩红
				//兄弟染父色
				//父黑
				//左孩黑
				//父右旋
				//所有操作结束
				p->color = t->parent->color;
				t->parent->color = RB_BLACK;
				p->left->color = RB_BLACK;
				_right_rotate(t->parent);

				t = root;
			}
		}
	}

	t->color = RB_BLACK;
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
	RBNode<T>* node = _search(root, x);

	if (node != NIL)
	{
		RBNode<T>* q = NIL;
		RBNode<T>* p = NIL;

		int origin_color = node->color;

		if (node->left != NIL && node->right != NIL)
		{
			p = node->right;

			while (p->left != NIL)
			{
				p = p->left;
			}

			origin_color = p->color;

			q = p->right;

			if (p->parent != node)
			{
				_transplant(p, p->right);
				p->right = node->right;
				node->right->parent = p;
			}
			else
			{
				q->parent = p;
			}
			
			_transplant(node, p);
			p->left = node->left;
			node->left->parent = p;

			p->color = node->color;
		}
		else if(node->left != NIL || node->right != NIL)
		{
			q = p = node->left != NIL ? node->left : node->right;
			_transplant(node, p);
		}

		Cut(node);
		delete node;

		if (origin_color == RB_BLACK)
		{
			_delete_adjust(q);
		}

		return true;
	}

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

	rbTree.Delete(6);
	rbTree.InorderTraversal(rbTree.root);
	printf("\n");

	rbTree.Delete(9);
	rbTree.InorderTraversal(rbTree.root);
	printf("\n");

	rbTree.Delete(4);
	rbTree.InorderTraversal(rbTree.root);
	printf("\n");

	return 0;
}