// DS_Map.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>

#include <assert.h>

#define RB_RED 0
#define RB_BLACK 1

template <typename T1, typename T2>
struct DS_PAIR
{
	T1 first;
	T2 second;
	DS_PAIR<T1, T2>(const T1& key, const T2& val) : first(key), second(val) {}
};

//红黑树结点
template <typename T1, typename T2>
struct SET_NODE
{
	DS_PAIR<T1, T2> pair;
	SET_NODE<T1, T2> *left;
	SET_NODE<T1, T2> *right;
	SET_NODE<T1, T2> *parent;
	int color; //颜色

	SET_NODE<T1, T2>(const T1& key, const T2& val, SET_NODE<T1, T2>* nil) : pair(key, val), left(nil), right(nil), parent(nil), color(RB_RED) {}
};



template <typename T1, typename T2>
class DS_Map
{
public:
	DS_Map();
	DS_Map(const DS_Map& that);
	DS_Map& operator = (const DS_Map& that);
	~DS_Map();

	class iterator
	{
		template <typename T1, typename T2>
		friend class DS_Map;

		DS_Map<T1, T2>* p; //指向的DS_Map
		SET_NODE<T1, T2> * cur; //当前表示的DS_Map中的节点

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator + (const int step);
		iterator& operator - (const int step);

		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		DS_PAIR<T1,T2>& operator * ();
		DS_PAIR<T1,T2>* operator -> ();
	};

	class reverse_iterator
	{
		template <typename T1, typename T2>
		friend class DS_Map;

		DS_Map<T1, T2>* p; //指向的DS_Map
		SET_NODE<T1, T2> * cur; //当前表示的DS_Map中的节点

	public:
		reverse_iterator();
		bool operator != (const reverse_iterator& that);
		reverse_iterator& operator + (int);
		reverse_iterator& operator - (int);

		reverse_iterator& operator ++ ();
		reverse_iterator operator ++ (int);
		reverse_iterator& operator -- ();
		reverse_iterator operator -- (int);
		DS_PAIR<T1,T2>& operator * ();
		DS_PAIR<T1,T2>* operator -> ();
	};



	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	int size();
	bool empty();

	T2& operator [] (const T1& key);
	T2& at(const T1& key);

	iterator find(const T1& key);

	iterator insert(const DS_PAIR<T1,T2>& pair);
	iterator erase(const T1& key);
	void clear();

protected:
	SET_NODE<T1, T2> *NIL;
	SET_NODE<T1, T2> *root;

	void _copy(const DS_Map& that);
	SET_NODE<T1, T2> * _copy(SET_NODE<T1, T2> *p, SET_NODE<T1, T2> *q, SET_NODE<T1, T2>* thatNIL);

	int _getHeight(SET_NODE<T1, T2> *t);
	int _getSize(SET_NODE<T1, T2> *t);
	void _erase(SET_NODE<T1, T2>*& t);
	void _transplant(SET_NODE<T1, T2> *p, SET_NODE<T1, T2> *q);
	SET_NODE<T1, T2> * Cut(SET_NODE<T1, T2> * p);
	SET_NODE<T1, T2> * _search(SET_NODE<T1, T2> * p, const T1& key);
	void _left_rotate(SET_NODE<T1, T2> *t);
	void _right_rotate(SET_NODE<T1, T2> *t);
	void _adjust(SET_NODE<T1, T2> *t);
	void _delete_adjust(SET_NODE<T1, T2> *t);
	SET_NODE<T1, T2>* _predecessor(T1 key);
	SET_NODE<T1, T2>* _successor(T1 key);
	SET_NODE<T1, T2>* _maximum(SET_NODE<T1, T2> * p);
	SET_NODE<T1, T2>* _minimum(SET_NODE<T1, T2> * p);
};

template <typename T1, typename T2>
DS_Map<T1, T2>::DS_Map()
{
	NIL = new SET_NODE<T1, T2>(T1(), T2(), NULL);
	NIL->color = RB_BLACK;
	root = NIL;
}

template <typename T1, typename T2>
DS_Map<T1, T2>::DS_Map(const DS_Map & that)
{
	NIL = new SET_NODE<T1, T2>(T1(), T2(), NULL);
	NIL->color = RB_BLACK;
	_copy(that);
}

template <typename T1, typename T2>
DS_Map<T1, T2> & DS_Map<T1, T2>::operator=(const DS_Map & that)
{
	if (this != &that)
	{
		_erase(root);
		_copy(that);
	}

	return *this;
}

template <typename T1, typename T2>
DS_Map<T1, T2>::~DS_Map()
{
	_erase(root);
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::begin()
{
	iterator it;
	it.p = this;
	it.cur = _minimum(root);
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::end()
{
	iterator it;
	it.p = this;
	it.cur = NULL;
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator DS_Map<T1, T2>::rbegin()
{
	reverse_iterator it;
	it.p = this;
	it.cur = _maximum(root);
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator DS_Map<T1, T2>::rend()
{
	reverse_iterator it;
	it.p = this;
	it.cur = NULL;
	return it;
}

template <typename T1, typename T2>
int DS_Map<T1, T2>::size()
{
	return _getSize(root);
}

template <typename T1, typename T2>
bool DS_Map<T1, T2>::empty()
{
	return root == NIL;
}

template<typename T1, typename T2>
T2 & DS_Map<T1, T2>::operator[](const T1 & key)
{
	SET_NODE<T1, T2>* node = _search(root, key);

	if (node == NIL)
	{
		iterator it = insert(DS_PAIR<T1, T2>(key, T2()));
		return it.cur->pair.second;
	}

	return at(key);
}

template<typename T1, typename T2>
T2 & DS_Map<T1, T2>::at(const T1 & key)
{
	SET_NODE<T1, T2>* node = _search(root, key);
	return node->pair.second;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::find(const T1& key)
{
	SET_NODE<T1, T2>* p = _search(root, key);

	iterator it;
	it.p = this;
	it.cur = p == NIL ? NULL : p;
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::insert(const DS_PAIR<T1, T2>& pair)
{
	SET_NODE<T1, T2>* p = root;
	SET_NODE<T1, T2>* q = p;

	while (p != NIL)
	{
		q = p;
		if (pair.first > p->pair.first)
			p = p->right;
		else if (pair.first < p->pair.first)
			p = p->left;
		else
		{
			iterator it;
			it.p = this;
			it.cur = p;
			return it;
		}
	}

	SET_NODE<T1, T2>* node = new SET_NODE<T1, T2>(pair.first, pair.second, NIL);

	if (q == NIL)
	{
		root = node;
	}
	else if (pair.first < q->pair.first)
		q->left = node;
	else
		q->right = node;

	node->parent = q;

	_adjust(node);

	iterator it;
	it.p = this;
	it.cur = node;
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::erase(const T1& key)
{
	SET_NODE<T1, T2>* p = _search(root, key);

	if (p == NIL)
	{
		return end();
	}

	SET_NODE<T1, T2>* q = NIL;
	int origin_color = p->color;

	if (p->left != NIL && p->right != NIL)
	{
		SET_NODE<T1, T2>* t = p->right;

		while (t->left != NIL)
		{
			t = t->left;
		}

		origin_color = t->color;
		q = t->right;

		if (t->parent != p)
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
	else if (p->left != NIL || p->right != NIL)
	{
		q = p->left != NIL ? p->left : p->right;
		_transplant(p, q);
	}

	delete p;

	if (origin_color == RB_BLACK)
		_delete_adjust(q);

	iterator it;
	it.p = this;
	it.cur = q;
	return it;
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::clear()
{
	_erase(root);
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_copy(const DS_Map & that)
{
	root = new SET_NODE<T1, T2>(that.root->pair.first, that.root->pair.second, NIL);
	root->left = _copy(that.root->left, root, that.NIL);
	root->right = _copy(that.root->right, root, that.NIL);
}

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_copy(SET_NODE<T1, T2>* p, SET_NODE<T1, T2>* q, SET_NODE<T1, T2>* thatNIL)
{
	if (p != thatNIL)
	{
		SET_NODE<T1, T2>* node = new SET_NODE<T1, T2>(p->pair.first, p->pair.second, NIL);
		node->left = _copy(p->left, node, thatNIL);
		node->right = _copy(p->right, node, thatNIL);
		node->parent = q;
		return node;
	}

	return NIL;
}

template <typename T1, typename T2>
int DS_Map<T1, T2>::_getHeight(SET_NODE<T1, T2>* t)
{
	if (t != NIL)
	{
		int left = _getHeight(t->left);
		int right = _getHeight(t->right);

		return left > right ? left : right;
	}

	return 0;
}

template <typename T1, typename T2>
int DS_Map<T1, T2>::_getSize(SET_NODE<T1, T2>* t)
{
	if (t == NIL)
		return 0;

	return _getSize(t->left) + _getSize(t->right) + 1;
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_erase(SET_NODE<T1, T2>*& t)
{
	if (t != NIL)
	{
		_erase(t->left);
		_erase(t->right);
		delete t;
	}
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_transplant(SET_NODE<T1, T2>* p, SET_NODE<T1, T2>* q)
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

template <typename T1, typename T2>
SET_NODE<T1, T2>* DS_Map<T1, T2>::Cut(SET_NODE<T1, T2>* p)
{
	if (p == NIL)
		return NIL;

	if (p->parent != NIL)
	{
		SET_NODE<T1, T2>* parent = p->parent;

		if (parent->left == p)
			parent->left = NIL;
		else if (parent->right == p)
			parent->right = NIL;
	}

	return p;
}

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_search(SET_NODE<T1, T2>* p, const T1& key)
{
	SET_NODE<T1, T2>* q = p;
	while (p != NIL)
	{
		q = p;
		if (key > p->pair.first)
			p = p->right;
		else if (key < p->pair.first)
			p = p->left;
		else
			break;
	}

	return q;
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_left_rotate(SET_NODE<T1, T2>* t)
{
	if (t == NIL || t->right == NIL)
		return;

	SET_NODE<T1, T2>* right = t->right;
	Cut(right);
	_transplant(t, right);

	t->right = right->left;

	if (right->left != NIL)
		right->left->parent = t;

	right->left = t;
	t->parent = right;
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_right_rotate(SET_NODE<T1, T2>* t)
{
	if (t == NIL || t->left == NIL)
		return;

	SET_NODE<T1, T2>* left = t->left;
	Cut(left);
	_transplant(t, left);

	t->left = left->right;

	if (left->right != NIL)
		left->right->parent = t;

	left->right = t;
	t->parent = left;
}

template <typename T1, typename T2>
void DS_Map<T1, T2>::_adjust(SET_NODE<T1, T2>* t)
{
	while (t->parent->color == RB_RED)
	{
		if (t->parent == t->parent->parent->left)
		{
			if (t->parent->parent->right->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->right->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				t = t->parent->parent;
			}
			else if (t->parent != NIL && t->parent->parent != NIL)
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
			if (t->parent->parent->left->color == RB_RED)
			{
				t->parent->color = RB_BLACK;
				t->parent->parent->left->color = RB_BLACK;
				t->parent->parent->color = RB_RED;
				t = t->parent->parent;
			}
			else if (t->parent != NIL && t->parent->parent != NIL)
			{
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

template <typename T1, typename T2>
void DS_Map<T1, T2>::_delete_adjust(SET_NODE<T1, T2>* t)
{
	while (t != root && t->color == RB_BLACK)
	{
		if (t == t->parent->left)
		{
			SET_NODE<T1, T2>* p = t->parent->right;

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
			SET_NODE<T1, T2>* p = t->parent->left;

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
				t = t->parent;
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

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_predecessor(T1 key)
{
	SET_NODE<T1, T2>* node = _search(root, key);

	if (node == NIL)
	{
		return NULL;
	}

	if (node->left != NIL)
		return _maximum(node->left);

	SET_NODE<T1, T2>* p = node->parent;

	while (p != NIL && node == p->left)
	{
		node = p;
		p = p->parent;
	}

	return p != NIL ? p : NULL;
}

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_successor(T1 key)
{
	SET_NODE<T1, T2>* node = _search(root, key);

	if (node == NIL)
	{
		return NULL;
	}

	if (node->right != NIL)
		return _minimum(node->right);

	SET_NODE<T1, T2>* p = node->parent;

	while (p != NIL && node == p->right)
	{
		node = p;
		p = p->parent;
	}

	return p != NIL ? p : NULL;
}

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_maximum(SET_NODE<T1, T2>* p)
{
	while (p != NIL && p->right != NIL)
	{
		p = p->right;
	}

	return p == NIL ? NULL : p;
}

template <typename T1, typename T2>
typename SET_NODE<T1, T2>* DS_Map<T1, T2>::_minimum(SET_NODE<T1, T2>* p)
{
	while (p != NIL && p->left != NIL)
	{
		p = p->left;
	}

	return p == NIL ? NULL : p;
}

template <typename T1, typename T2>
DS_Map<T1, T2>::iterator::iterator()
{
	p = NULL;
	cur = NULL;
}

template <typename T1, typename T2>
bool DS_Map<T1, T2>::iterator::operator!=(const iterator & that)
{
	return p != that.p || cur != that.cur;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator & DS_Map<T1, T2>::iterator::operator++()
{
	assert(p && cur);
	SET_NODE<T1, T2>* next = p->_successor(cur->pair.first);
	cur = next;
	return *this;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::iterator::operator++(int)
{
	assert(p && cur);
	SET_NODE<T1, T2>* next = p->_successor(cur->pair.first);
	iterator it = *this;
	cur = next;
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator & DS_Map<T1, T2>::iterator::operator--()
{
	assert(p && cur);
	SET_NODE<T1, T2>* pre = p->_predecessor(cur->pair.first);
	cur = pre;
	return *this;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::iterator DS_Map<T1, T2>::iterator::operator--(int)
{
	assert(p && cur);
	SET_NODE<T1, T2>* pre = p->_predecessor(cur->pair.first);
	iterator it = *this;
	cur = pre;
	return it;
}

template <typename T1, typename T2>
DS_PAIR<T1, T2> & DS_Map<T1, T2>::iterator::operator*()
{
	assert(p && cur);
	return cur->pair;
}

template <typename T1, typename T2>
DS_PAIR<T1, T2> * DS_Map<T1, T2>::iterator::operator->()
{
	assert(p && cur);
	return &(cur->pair);
}

template <typename T1, typename T2>
DS_Map<T1, T2>::reverse_iterator::reverse_iterator()
{
	p = NULL;
	cur = NULL;
}

template <typename T1, typename T2>
bool DS_Map<T1, T2>::reverse_iterator::operator!=(const reverse_iterator & that)
{
	return p != that.p || cur != that.cur;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator & DS_Map<T1, T2>::reverse_iterator::operator++()
{
	assert(p && cur);
	SET_NODE<T1, T2>* pre = p->_predecessor(cur->pair.first);
	cur = pre;
	return *this;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator DS_Map<T1, T2>::reverse_iterator::operator++(int)
{
	assert(p && cur);
	SET_NODE<T1, T2>* pre = p->_predecessor(cur->pair.first);
	reverse_iterator it = *this;
	cur = pre;
	return it;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator & DS_Map<T1, T2>::reverse_iterator::operator--()
{
	assert(p && cur);
	SET_NODE<T1, T2>* next = p->_successor(cur->pair.first);
	cur = next;
	return *this;
}

template <typename T1, typename T2>
typename DS_Map<T1, T2>::reverse_iterator DS_Map<T1, T2>::reverse_iterator::operator--(int)
{
	assert(p && cur);
	SET_NODE<T1, T2>* next = p->_successor(cur->pair.first);
	reverse_iterator it = *this;
	cur = next;
	return it;
}

template <typename T1, typename T2>
DS_PAIR<T1, T2> & DS_Map<T1, T2>::reverse_iterator::operator*()
{
	assert(p && cur);
	return cur->pair;
}

template <typename T1, typename T2>
DS_PAIR<T1, T2> * DS_Map<T1, T2>::reverse_iterator::operator->()
{
	assert(p && cur);
	return &(cur->pair);
}

int main()
{
	std::map<int, int> map1;
	DS_Map<int, int> ds_map1;

	int datas[10] = { 3,2,1,4,5,6,10,9,8,7 };

	map1[1] = 100;
	ds_map1[1] = 100;

	for (int i = 0; i < 10; ++i)
	{
		map1.insert(std::pair<int, int>(i, datas[i]));
		ds_map1.insert(DS_PAIR<int, int>(i, datas[i]));
	}

	printf("std::map: ");

	for (std::map<int, int>::iterator it = map1.begin(); it != map1.end(); ++it)
	{
		printf("%d(%d) ", it->first, it->second);
	}

	printf("\nDS_Map: ");

	for (DS_Map<int, int>::iterator it = ds_map1.begin(); it != ds_map1.end(); ++it)
	{
		printf("%d(%d) ", it->first, it->second);
	}

	printf("\n");

	printf("std::map[1]: %d\n", map1.at(1));
	printf("nDS_Map[1]: %d\n", ds_map1.at(1));

	map1[1] = 2;
	ds_map1[1] = 2;

	printf("std::map[1]: %d\n", map1.at(1));
	printf("nDS_Map[1]: %d\n", ds_map1.at(1));

	std::map<int, int> map2 = map1;
	DS_Map<int, int> ds_map2 = ds_map1;

	map2.erase(3);
	map2.erase(5);

	ds_map2.erase(3);
	ds_map2.erase(5);

	printf("std::map: ");

	for (std::map<int, int>::reverse_iterator it = map2.rbegin(); it != map2.rend(); ++it)
	{
		printf("%d(%d) ", it->first, it->second);
	}

	printf("\nDS_Map: ");

	for (DS_Map<int, int>::reverse_iterator it = ds_map2.rbegin(); it != ds_map2.rend(); ++it)
	{
		printf("%d(%d) ", it->first, it->second);
	}

	printf("\n");

    return 0;
}

