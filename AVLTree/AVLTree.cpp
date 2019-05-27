// AVLTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>

//平衡二叉树结点
template <typename T>
struct AvlNode
{
	T data;
	AvlNode<T> *left;
	AvlNode<T> *right;
	AvlNode<T> *parent;
	int BF; //平衡因子

	AvlNode<T>(const T theData) : data(theData), left(NULL), right(NULL), parent(NULL), BF(0) {}
};

//AvlTree
template <typename T>
class AvlTree
{
public:
	AvlTree<T>();
	~AvlTree<T>();
	AvlNode<T> *root;
	//插入结点
	void Insert(T x);
	//删除结点
	bool Delete(T x);
	//查找是否存在给定值的结点
	bool Contains(AvlNode<T> *t, const T x);
	//中序遍历
	void InorderTraversal(AvlNode<T> *t);
	//前序遍历
	void PreorderTraversal(AvlNode<T> *t);
	//最小值结点
	AvlNode<T> *FindMin(AvlNode<T> *t) const;
	//最大值结点
	AvlNode<T> *FindMax(AvlNode<T> *t) const;
private:
	//求树的高度
	int GetHeight(AvlNode<T> *t);
	//单旋转 左左节点右旋
	AvlNode<T> *LL_R(AvlNode<T> *t);
	//单旋转 右右节点左旋
	AvlNode<T> *RR_L(AvlNode<T> *t);
	//双旋转 右左节点右+左旋
	AvlNode<T> *RL_RL(AvlNode<T> *t);
	//双旋转 左右节点左+右旋
	AvlNode<T> *LR_LR(AvlNode<T> *t);

	void _erase(AvlNode<T>*& t);
	void _transplant(AvlNode<T> *p, AvlNode<T> *q);
	void _updateBF(AvlNode<T> *t);
	AvlNode<T> * Cut(AvlNode<T> * p);
	AvlNode<T> * _search(AvlNode<T> * p, const T data);
	void _adjust(AvlNode<T> *t);
};

template<typename T>
AvlTree<T>::AvlTree()
{
	root = NULL;
}

template<typename T>
AvlTree<T>::~AvlTree()
{
	_erase(root);
}

template<typename T>
void AvlTree<T>::_erase(AvlNode<T>*& t)
{
	if (t)
	{
		_erase(t->left);
		_erase(t->right);
		delete t;
	}
}

template<typename T>
void AvlTree<T>::_transplant(AvlNode<T> *p, AvlNode<T> *q)
{
	if (p == NULL)
		return;

	if (p->parent == NULL)
		root = q;
	else if (p == p->parent->left)
		p->parent->left = q;
	else
		p->parent->right = q;

	if (q != NULL)
		q->parent = p->parent;
}

template<typename T>
void AvlTree<T>::_updateBF(AvlNode<T>* t)
{
	if (t == NULL)
		return;

	t->BF = GetHeight(t->left) - GetHeight(t->right);
	_updateBF(t->left);
	_updateBF(t->right);
}

template<typename T>
AvlNode<T>* AvlTree<T>::Cut(AvlNode<T>* p)
{
	if (p == NULL)
		return NULL;

	if (p->parent != NULL)
	{
		AvlNode<T>* parent = p->parent;

		if (parent->left == p)
			parent->left = NULL;
		else if (parent->right == p)
			parent->right = NULL;
	}

	return p;
}

template<typename T>
AvlNode<T>* AvlTree<T>::_search(AvlNode<T>* p, const T data)
{
	AvlNode<T>* q = p;
	while (q && q->data != data)
	{
		if (q->data > data)
			q = q->left;
		else
			q = q->right;
	}

	return q;
}

template<typename T>
void AvlTree<T>::_adjust(AvlNode<T>* p)
{
	AvlNode<T>* q = p ? (p->left ? p->left : p->right) : NULL;

	while (p && abs(p->BF) < 2)
	{
		q = p;
		p = p->parent;
	}

	if (p)
	{
		//LLL------R
		//    2  p
		//  x    q
		// x
		if (p->BF == 2 && q->BF >= 0)
		{
			LL_R(q);
		}
		//RRR------L
		//-2      p
		//  x    q
		//    x
		else if (p->BF == -2 && q->BF <= 0)
		{
			RR_L(q);
		}
		//LLR------LR
		//    2    p
		//  -x     q
		//    x
		else if (p->BF == 2 && q->BF < 0)
		{
			LR_LR(q);
		}
		//RRL-------RL
		//    -2     p
		//       x   q
		//     x
		else if (p->BF == -2 && q->BF > 0)
		{
			RL_RL(q);
		}

		_updateBF(root);
	}
}

template<typename T>
void AvlTree<T>::Insert(T x)
{
	AvlNode<T>* parent = NULL;

	AvlNode<T>* p = root;

	while (p)
	{
		parent = p;

		if (x > p->data)
			p = p->right;
		else if (x < p->data)
			p = p->left;
		else
			return;
	}

	AvlNode<T>* node = new AvlNode<T>(x);

	if (parent == NULL)
	{
		root = node;
		return;
	}

	node->parent = parent;

	if (x > parent->data)
		parent->right = node;
	else
		parent->left = node;

	_updateBF(root);

	//回溯检索最小不平衡子树
	p = node->parent;
	_adjust(node->parent);
}

template<typename T>
bool AvlTree<T>::Delete(T x)
{
	AvlNode<T>* node = _search(root, x);

	if (node)
	{
		AvlNode<T>* p = NULL;

		if(node->left == NULL && node->right == NULL)
		{
			Cut(node);

			p = node->parent;

			if (node == root)
			{
				root = NULL;
			}
		}
		else if (node->left != NULL && node->right != NULL)
		{
			//左高找前驱
			if (node->BF > 0)
			{
				AvlNode<T>* q = node->left;

				while (q->right)
				{
					q = q->right;
				}

				p = q;

				if (q->parent != node)
				{
					p = q->parent;
					_transplant(q, q->left);
					q->left = node->left;
					node->left->parent = q;
				}

				_transplant(node, q);
				q->right = node->right;
				node->right->parent = q;
			}
			//右高找后继
			else
			{
				AvlNode<T>* q = node->right;

				while (q->left)
				{
					q = q->left;
				}

				p = q;

				if (q->parent != node)
				{
					p = q->parent;
					_transplant(q, q->right);
					q->right = node->right;
					node->right->parent = q;
				}

				_transplant(node, q);
				q->left = node->left;
				node->left->parent = q;
			}
		}
		else
		{
			AvlNode<T>* q = node->left ? node->left : node->right;
			_transplant(node, q);
			p = q;
		}

		delete(node);

		_updateBF(root);
		_adjust(p);
	}

	return false;
}

template<typename T>
bool AvlTree<T>::Contains(AvlNode<T>* t, const T x)
{
	return _search(t, x) != NULL;
}

template<typename T>
void AvlTree<T>::InorderTraversal(AvlNode<T>* t)
{
	if (t)
	{
		InorderTraversal(t->left);
		printf("%d ", t->data);
		InorderTraversal(t->right);
	}
}

template<typename T>
void AvlTree<T>::PreorderTraversal(AvlNode<T>* t)
{
	if (t)
	{
		printf("%d ", t->data);
		InorderTraversal(t->left);
		InorderTraversal(t->right);
	}
}

template<typename T>
AvlNode<T>* AvlTree<T>::FindMin(AvlNode<T>* t) const
{
	AvlNode<T>* p = t;
	while (p)
	{
		p = p->left;
	}

	return p;
}

template<typename T>
AvlNode<T>* AvlTree<T>::FindMax(AvlNode<T>* t) const
{
	AvlNode<T>* p = t;
	while (p)
	{
		p = p->right;
	}

	return p;
}

template<typename T>
int AvlTree<T>::GetHeight(AvlNode<T>* t)
{
	if (t)
	{
		int left = GetHeight(t->left);
		int right = GetHeight(t->right);

		return (left > right ? left : right) + 1;
	}

	return 0;
}

template<typename T>
AvlNode<T>* AvlTree<T>::LL_R(AvlNode<T>* t)
{
	AvlNode<T>* p = t->parent;
	Cut(t);

	_transplant(p, t);
	
	if (t->right)
	{
		p->left = t->right;
		t->right->parent = p;
	}
	
	t->right = p;
	p->parent = t;

	return t;
}

template<typename T>
AvlNode<T>* AvlTree<T>::RR_L(AvlNode<T>* t)
{
	AvlNode<T>* p = t->parent;
	Cut(t);

	_transplant(p, t);

	if (t->left)
	{
		p->right = t->left;
		t->left->parent = p;
	}
	
	t->left = p;
	p->parent = t;

	return t;
}

template<typename T>
AvlNode<T>* AvlTree<T>::RL_RL(AvlNode<T>* t)
{
	return RR_L(LL_R(t->left));
}

template<typename T>
AvlNode<T>* AvlTree<T>::LR_LR(AvlNode<T>* t)
{
	return LL_R(RR_L(t->right));
}

//{3, 2, 1, 4, 5, 6, 10, 9, 8, 7}

int main()
{
	int datas[10] = { 3,2,1,4,5,6,10,9,8,7 };

	AvlTree<int> avlTree;
	for (int i = 0; i < 10; ++i)
		avlTree.Insert(datas[i]);

	avlTree.InorderTraversal(avlTree.root);

	if (avlTree.Contains(avlTree.root, 4))
	{
		printf("4 exsit.\n");
		avlTree.Delete(4);
	}
	else
	{
		printf("4 not exsit.\n");
	}

	avlTree.InorderTraversal(avlTree.root);

	printf("\n");
	avlTree.Delete(6);
	avlTree.InorderTraversal(avlTree.root);

	printf("\n");
	avlTree.Delete(8);
	avlTree.InorderTraversal(avlTree.root);

	printf("\n");

	avlTree.Delete(7);
	avlTree.Delete(10);
	avlTree.Delete(9);

	avlTree.InorderTraversal(avlTree.root);

	printf("\n");

	return 0;
}


