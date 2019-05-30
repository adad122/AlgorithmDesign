// DS_Set.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <set>
#include <assert.h>

#define RB_RED 0
#define RB_BLACK 1

//红黑树结点
template <typename T>
struct SET_NODE
{
	T data;
	SET_NODE<T> *left;
	SET_NODE<T> *right;
	SET_NODE<T> *parent;
	int color; //颜色

	SET_NODE<T>(const T theData, SET_NODE<T>* nil) : data(theData), left(nil), right(nil), parent(nil), color(RB_RED) {}
};

template <typename T>
class DS_Set
{
public:
	DS_Set();
	DS_Set(const DS_Set& that);
	DS_Set& operator = (const DS_Set& that);
	~DS_Set();

	class iterator
	{
		template <typename T>
		friend class DS_Set;

		DS_Set* p; //指向的DS_Set
		int index; //当前表示的DS_Set中的节点

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator + (const int step);
		iterator& operator - (const int step);

		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		T& operator * ();
		T* operator -> ();
	};

	class reverse_iterator
	{
		template <typename T>
		friend class DS_Set;

		DS_Set* p; //指向的DS_Set
		int index; //当前表示的DS_Set中的节点

	public:
		reverse_iterator();
		bool operator != (const reverse_iterator& that);
		reverse_iterator& operator + (int);
		reverse_iterator& operator - (int);

		reverse_iterator& operator ++ ();
		reverse_iterator operator ++ (int);
		reverse_iterator& operator -- ();
		reverse_iterator operator -- (int);
		T& operator * ();
		T* operator -> ();
	};



	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	int size();
	bool empty();

	iterator find(const T& val) const;

	iterator insert(const T& data);
	iterator erase(const T& val);
	void clear();

protected:
	SET_NODE<T> *NIL;
	SET_NODE<T> *root;

	void _copy(const DS_Set& that);
	SET_NODE<T> * _copy(SET_NODE<T> *p, SET_NODE<T> *q);

	int _getHeight(SET_NODE<T> *t);
	int _getSize(SET_NODE<T> *t);
	void _erase(SET_NODE<T>*& t);
	void _transplant(SET_NODE<T> *p, SET_NODE<T> *q);
	SET_NODE<T> * Cut(SET_NODE<T> * p);
	SET_NODE<T> * _search(SET_NODE<T> * p, const T data);
	void _left_rotate(SET_NODE<T> *t);
	void _right_rotate(SET_NODE<T> *t);
	void _adjust(SET_NODE<T> *t);
	void _delete_adjust(SET_NODE<T> *t);
	SET_NODE<T>* _predecessor(T data);
	SET_NODE<T>* _successor(T data);
	SET_NODE<T>* _maximum(SET_NODE<T> * p);
	SET_NODE<T>* _minimum(SET_NODE<T> * p);
};

template<typename T>
DS_Set<T>::DS_Set()
{
	NIL = new SET_NODE<T>(T(), NULL);
	NIL->color = RB_BLACK;
	root = NIL;
}

template<typename T>
DS_Set<T>::DS_Set(const DS_Set & that)
{
	_copy(that);
}

template<typename T>
DS_Set<T> & DS_Set<T>::operator=(const DS_Set & that)
{
	if (this != &that)
	{
		_erase(root);
		_copy(that);
	}

	return *this;
}

template<typename T>
DS_Set<T>::~DS_Set()
{
	_erase(root);
}

template<typename T>
typename DS_Set<T>::iterator DS_Set<T>::begin()
{
	return iterator();
}

template<typename T>
typename DS_Set<T>::iterator DS_Set<T>::end()
{
	return iterator();
}

template<typename T>
typename DS_Set<T>::reverse_iterator DS_Set<T>::rbegin()
{
	return reverse_iterator();
}

template<typename T>
typename DS_Set<T>::reverse_iterator DS_Set<T>::rend()
{
	return reverse_iterator();
}

template<typename T>
int DS_Set<T>::size()
{
	return _getSize(root);
}

template<typename T>
bool DS_Set<T>::empty()
{
	return root == NIL;
}

template<typename T>
typename DS_Set<T>::iterator DS_Set<T>::find(const T & val) const
{
	return iterator();
}

template<typename T>
typename DS_Set<T>::iterator DS_Set<T>::insert(const T & data)
{
	SET_NODE<T>* p = root;
	SET_NODE<T>* q = p;

	while (p != NIL)
	{
		q = p;
		if (data > p->data)
			p = p->right;
		else if (data < p->data)
			p = p->left;
		else
		{
			return iterator();
		}
	}

	SET_NODE<T>* node = new SET_NODE<T>(data, NIL);

	if(q == NIL)
	{
		root = node;
	}
	else if (data < q->data)
		q->left = node;
	else
		q->right = node;

	node->parent = q;

	_adjust(node);
}

template<typename T>
typename DS_Set<T>::iterator DS_Set<T>::erase(const T & val)
{
	SET_NODE<T>* p = _search(val);

	if (p == NIL)
	{
		return iterator();
	}

	SET_NODE<T>* q = NIL;
	int origin_color = p->color;

	if (p->left != NIL && p->right != NIL)
	{
		SET_NODE<T>* t = p->right;

		while (t->left)
		{
			t = t->left;
		}

		origin_color = t->color;
		q = t->right;

		if(t->parent != p)
		{
			_transplant(t, t->right);
			t->right = p->right;
			p->right->parent = t;
		}
		else
		{
			q->parent = t;
		}

		_transplant(p, t);
		t->left = p->left;
		p->left->parent = t;

		t->color = p->color;
	}
	else
	{
		q = p->left ? p->left : p->right;
		_transplant(p, q);
	}

	delete p;
	
	if (origin_color == RB_BLACK)
		_delete_adjust(q);

	return iterator();
}

template<typename T>
void DS_Set<T>::clear()
{
	_erase(root);
}

template<typename T>
void DS_Set<T>::_copy(const DS_Set & that)
{
	root = new SET_NODE<T>(that->root->data, NIL);
	root->left = _copy(that->root->left, root);
	root->right = _copy(that->root->right, root);
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_copy(SET_NODE<T>* p, SET_NODE<T>* q)
{
	if (p != NIL)
	{
		SET_NODE<T>* node = new SET_NODE<T>(p->data, NIL);
		node->left = _copy(p->left, node);
		node->right = _copy(p->right, node);
		node->parent = q;
	}
}

template<typename T>
int DS_Set<T>::_getHeight(SET_NODE<T>* t)
{
	if (t != NIL)
	{
		int left = _getHeight(t->left);
		int right = _getHeight(t->right);

		return left > right ? left : right;
	}

	return 0;
}

template<typename T>
int DS_Set<T>::_getSize(SET_NODE<T>* t)
{
	if (t == NIL)
		return 0;

	return _getSize(t->left) + _getSize(t->right) + 1;
}

template<typename T>
void DS_Set<T>::_erase(SET_NODE<T>*& t)
{
	if (t != NIL)
	{
		_erase(t->left);
		_erase(t->right);
		delete t;
	}
}

template<typename T>
void DS_Set<T>::_transplant(SET_NODE<T>* p, SET_NODE<T>* q)
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
SET_NODE<T>* DS_Set<T>::Cut(SET_NODE<T>* p)
{
	if (p == NULL)
		return NULL;

	if (p->parent != NULL)
	{
		_Node * parent = p->parent;

		if (parent->left == p)
			parent->left = NULL;
		else if (parent->right == p)
			parent->right = NULL;
	}

	return p;
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_search(SET_NODE<T>* p, const T data)
{
	SET_NODE<T>* q = p;
	while (p)
	{
		q = p;
		if (data > p->data)
			p = p->right;
		else if (data < p->data)
			p = p->left;
		else
			break;
	}

	return q;
}

template<typename T>
void DS_Set<T>::_left_rotate(SET_NODE<T>* t)
{
	if (t == NIL || t->right == NIL)
		return;

	SET_NODE<T>* right = t->right;
	Cut(right);
	_transplant(t, right);

	t->right = right->left;

	if (right->left != NIL)
		right->left->parent = t;

	right->left = t;
	t->parent = right;
}

template<typename T>
void DS_Set<T>::_right_rotate(SET_NODE<T>* t)
{
	if (t == NIL || t->left == NIL)
		return;

	SET_NODE<T>* left = t->left;
	Cut(left);
	_transplant(t, left);

	t->left = left->right;

	if (left->right != NIL)
		left->right->parent = t;

	left->right = t;
	t->parent = left;
}

template<typename T>
void DS_Set<T>::_adjust(SET_NODE<T>* t)
{
	while (t->parent->color == RB_RED)
	{
		if(t->parent = t->parent->parent->left)
		{
			if (t->parent->parent->right->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->right->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				t = t->parent->parent;
			}
			else if(t->parent != NIL && t->parent->parent != NIL)
			{
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
		else
		{
			if(t->parent->parent->left->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->left->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				t = t->parent->parent;
			}
			else if (t->parent != NIL && t->parent->parent != NIL)
			{
				if (t = t->parent->left)
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
void DS_Set<T>::_delete_adjust(SET_NODE<T>* t)
{
	while (t != root && t->color == RB_BLACK)
	{
		if (t = t->parent->left)
		{
			SET_NODE<T>* p = t->parent->right;

			if (p->color == RB_RED)
			{
				p->color = RB_BLACK;
				t->parent->color = RB_RED;
				_left_rotate(t->parent);
				p = t->parent->right;
			}

			if (p->color == RB_BLACK && p->left->color == RB_BLACK && p->right->color == RB_BLACK)
			{
				p->color = RB_RED;
				t = t->parent;
			}
			else
			{
				if (p->left->color == RB_RED)
				{
					p->left->color = RB_BLACK;
					p->color = RB_RED;
					_right_rotate(p);
					p = p->parent;
				}

				p->color = p->parent->color;
				p->right->color = RB_BLACK;
				p->parent->color = RB_BLACK;
				_left_rotate(p->parent);

				t = root;
			}
		}
		else
		{
			SET_NODE<T>* p = t->parent->left;

			if (p->color == RB_RED)
			{
				p->color = RB_BLACK;
				t->parent->color = RB_RED;
				_right_rotate(t->parent);
				p = t->parent->left;
			}

			if (p->color == RB_BLACK && p->left->color == RB_BLACK && p->right->color == RB_BLACK)
			{
				p->color = RB_RED;
				t = t->parent
			}
			else
			{
				if (p->right->color == RB_RED)
				{
					p->right->color = RB_BLACK;
					p->color = RB_RED;
					_left_rotate(p);
					p = p->parent;
				}

				p->color = p->parent->color;
				p->parent->color = RB_BLACK;
				p->left->color = RB_BLACK;
				_right_rotate(p->parent);

				t = root;
			}
		}
	}

	t->color = RB_BLACK;
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_predecessor(T data)
{
	SET_NODE<T>* node = _search(data);

	if (node == NIL)
	{
		return NULL;
	}

	if (node->left)
		return _maximum(node->left);

	SET_NODE<T>* p = node->parent;
	
	while(p != NIL && node == p->left)
	{
		node = p;
		p = p->parent
	}

	return p != NIL ? p : NULL;
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_successor(T data)
{
	SET_NODE<T>* node = _search(data);

	if (node == NIL)
	{
		return NULL;
	}

	if (node->right)
		return _minimum(node->right);

	SET_NODE<T>* p = node->parent;

	while (p != NIL && node == p->right)
	{
		node = p;
		p = p->parent;
	}

	return p != NIL ? p : NULL;
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_maximum(SET_NODE<T>* p)
{
	while (p->right)
	{
		p = p->right;
	}

	return p == NIL ? NULL : p;
}

template<typename T>
typename SET_NODE<T>* DS_Set<T>::_minimum(SET_NODE<T>* p)
{
	while (p->left)
	{
		p = p->left;
	}

	return p == NIL ? NULL : p;
}


int main()
{
	DS_Set<int> ds_set1;
	std::set<int> set1;
	return 0;
}
