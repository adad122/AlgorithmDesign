// DS_List.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <list>

template <typename T>
class DS_List
{
public:
	DS_List();
	DS_List(const DS_List& that);
	DS_List& operator = (const DS_List& that);
	~DS_List();

	struct _node
	{
		T data;
		_node* pre;
		_node* next;
	};

	class iterator
	{
		template <typename T>
		friend class DS_List;

		DS_List* p; //指向的DS_List
		_node* cur; //当前表示的DS_List中的节点

	public:
		iterator();
		bool operator != (const iterator& that);

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
		friend class DS_List;

		DS_List* p; //指向的DS_List
		_node* cur; //当前表示的DS_List中的节点

	public:
		reverse_iterator();
		bool operator != (const reverse_iterator& that);

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
	int empty();

	T& operator [] (const int index);
	T& at(int index);
	T& front();
	T& back();

	void push_front(T data);
	void pop_front();
	void push_back(T data);
	void pop_back();

	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
	void clear();

protected:
	_node* m_head;
	_node* m_rear;
	int m_size; //大小

	void _copy(const DS_List& that);
	void _clear();

};

template<typename T>
DS_List<T>::DS_List()
{
	m_head = new _node;
	m_rear = new _node;

	m_head->next = m_rear;
	m_rear->pre = m_head;
	m_size = 0;
}

template<typename T>
DS_List<T>::DS_List(const DS_List & that)
{
	m_head = new _node;
	m_rear = new _node;

	m_head->next = m_rear;
	m_rear->pre = m_head;
	m_size = 0;

	_copy(that);
}

template<typename T>
DS_List<T> & DS_List<T>::operator=(const DS_List & that)
{
	if (this != &that)
	{
		_clear();
		_copy(that);
	}

	return *this;
}

template<typename T>
DS_List<T>::~DS_List()
{
	_clear();
	delete m_head;
	delete m_rear;
}

template<typename T>
void DS_List<T>::_copy(const DS_List & that)
{
	_node* p = that.m_head->next;
	_node* q = m_head;
	
	while (p != that.m_rear)
	{
		_node* n = new _node;
		n->data = p->data;

		q->next = n;
		n->pre = q;
		q = n;

		p = p->next;
	}

	q->next = m_rear;
	m_rear->pre = q;
	m_size = that.m_size;
}

template<typename T>
void DS_List<T>::_clear()
{
	_node* p = m_head->next;
	_node* q;
	while (p != m_rear)
	{
		q = p;
		p = p->next;
		delete q;
	}

	m_head->next = m_rear;
	m_rear->pre = m_head;

	m_size = 0;
}

template<typename T>
int DS_List<T>::size()
{
	return m_size;
}

template<typename T>
int DS_List<T>::empty()
{
	return m_size == 0;
}

template<typename T>
T & DS_List<T>::operator[](const int index)
{
	return at(index);
}

template<typename T>
T & DS_List<T>::at(int index)
{
	assert(index >= 0 && index < m_size);

	int i = 0;
	*node p = m_head->next;

	while (i < index)
	{
		p = p->next;
	}

	return p->data;
}

template<typename T>
T & DS_List<T>::front()
{
	assert(m_size > 0);
	return m_head->next->data;
}

template<typename T>
T & DS_List<T>::back()
{
	assert(m_size > 0);
	return m_rear->pre->data;
}

template<typename T>
void DS_List<T>::push_front(T data)
{
	_node* p = new _node;
	p->data = data;

	_node* q = m_head->next;
	q->pre = p;

	p->next = q;
	p->pre = m_head;

	m_head->next = p;

	m_size++;
}

template<typename T>
void DS_List<T>::pop_front()
{
	if (m_size <= 0)
		return;

	_node* p = m_head->next;
	_node* q = p->next;
	m_head->next = q;
	q->pre = m_head;

	delete p;
	m_size--;
}

template<typename T>
void DS_List<T>::push_back(T data)
{
	_node* p = new _node;
	p->data = data;

	_node* q = m_rear->pre;
	q->next = p;

	p->pre = q;
	p->next = m_rear;

	m_rear->pre = p;

	m_size++;
}

template<typename T>
void DS_List<T>::pop_back()
{
	if (m_size <= 0)
		return;

	_node* p = m_rear->pre;
	_node* q = p->pre;
	m_rear->pre = q;
	q->next = m_rear;

	delete p;
	m_size--;
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::insert(iterator & it, T data)
{
	assert(this == it.p && it.cur != m_head);

	_node* p = it.cur;
	_node* q = p->pre;

	_node* n = new _node;
	n->data = data;
	n->pre = q;
	n->next = p;

	q->next = n;
	p->pre = n;

	it.cur = NULL;
	it.p = NULL;
	return it;
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::erase(iterator & it)
{
	assert(this == it.p && it.cur != m_head && it.cur != m_rear);

	_node* p = it.cur->pre;
	_node* q = it.cur->next;

	p->next = q;
	q->pre = p;

	delete it.cur;

	it.cur = NULL;
	it.p = NULL;
	return it;
}

template<typename T>
void DS_List<T>::clear()
{
	_clear();
}

template<typename T>
DS_List<T>::iterator::iterator()
{
	p = NULL;
	cur = NULL;
}

template<typename T>
bool DS_List<T>::iterator::operator!=(const iterator & that)
{
	return p != that.p || cur != that.cur;
}

template<typename T>
typename DS_List<T>::iterator & DS_List<T>::iterator::operator++()
{
	assert(p && cur->next != p->m_rear);
	cur = cur->next;
	return *this;
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::iterator::operator++(int)
{
	assert(p && cur != p->m_rear);
	iterator it = *this;
	cur = cur->next;
	return it;
}

template<typename T>
typename DS_List<T>::iterator & DS_List<T>::iterator::operator--()
{
	assert(p && cur->pre != p->m_head);
	cur = cur->pre;
	return *this;
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::iterator::operator--(int)
{
	assert(p && cur->pre != p->m_head);
	iterator it = *this;
	cur = cur->pre;
	return it;
}

template<typename T>
T & DS_List<T>::iterator::operator*()
{
	assert(p && cur);
	return cur->data;
}

template<typename T>
T * DS_List<T>::iterator::operator->()
{
	assert(p && cur);
	return &(cur->data);
}

template<typename T>
DS_List<T>::reverse_iterator::reverse_iterator()
{
	p = NULL;
	cur = NULL;
}

template<typename T>
bool DS_List<T>::reverse_iterator::operator!=(const reverse_iterator & that)
{
	return p != that.p || cur != that.cur;
}

template<typename T>
typename DS_List<T>::reverse_iterator & DS_List<T>::reverse_iterator::operator++()
{
	assert(p && cur != p->m_head);
	cur = cur->pre;
	return *this;
}

template<typename T>
typename DS_List<T>::reverse_iterator DS_List<T>::reverse_iterator::operator++(int)
{
	assert(p && cur != p->m_head);
	reverse_iterator it = *this;
	cur = cur->pre;
	return it;
}

template<typename T>
typename DS_List<T>::reverse_iterator & DS_List<T>::reverse_iterator::operator--()
{
	assert(p && cur->next != p->m_rear);
	cur = cur->next;
	return *this;
}

template<typename T>
typename DS_List<T>::reverse_iterator DS_List<T>::reverse_iterator::operator--(int)
{
	assert(p && cur->next != p->m_rear);
	reverse_iterator it = *this;
	cur = cur->next;
	return it;
}

template<typename T>
T & DS_List<T>::reverse_iterator::operator*()
{
	assert(p && cur);
	return cur->data;
}

template<typename T>
T * DS_List<T>::reverse_iterator::operator->()
{
	assert(p && cur);
	return &(cur->data);
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::begin()
{
	iterator it;
	it.p = this;
	it.cur = m_head->next;
	return it;
}

template<typename T>
typename DS_List<T>::iterator DS_List<T>::end()
{
	iterator it;
	it.p = this;
	it.cur = m_rear;
	return it;
}

template<typename T>
typename DS_List<T>::reverse_iterator DS_List<T>::rbegin()
{
	reverse_iterator it;
	it.p = this;
	it.cur = m_rear->pre;
	return it;
}

template<typename T>
typename DS_List<T>::reverse_iterator DS_List<T>::rend()
{
	reverse_iterator it;
	it.p = this;
	it.cur = m_head;
	return it;
}

void OutputList(std::list<int>& ls)
{
	for (std::list<int>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		printf("%d ", *it);
	}
}

void OutputDSList(DS_List<int>& ls)
{
	for (DS_List<int>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		printf("%d ", *it);
	}
}

void OutputListReverse(std::list<int>& ls)
{
	for (std::list<int>::reverse_iterator it = ls.rbegin(); it != ls.rend(); ++it)
	{
		printf("%d ", *it);
	}
}

void OutputDSListReverse(DS_List<int>& ls)
{
	for (DS_List<int>::reverse_iterator it = ls.rbegin(); it != ls.rend(); ++it)
	{
		printf("%d ", *it);
	}
}


int main()
{
	int datas[10] = { 1,2,3,4,5,6,7,8,9,0 };

	std::list<int> list1;
	DS_List<int> ds_list1;

	for (int i = 0; i < 10; ++i)
	{
		list1.push_back(datas[i]);
		ds_list1.push_back(datas[i]);
	}

	printf("List1:");
	OutputList(list1);
	printf("\n");

	printf("DS_List1:");
	OutputDSList(ds_list1);
	printf("\n");

	std::list<int> list2 = list1;
	DS_List<int> ds_list2 = ds_list1;

	printf("List2:");
	OutputList(list2);
	printf("\n");

	printf("DS_List2:");
	OutputDSList(ds_list2);
	printf("\n");

	list2.erase(list2.begin());
	list2.insert(list2.begin(), 11);
	list2.pop_back();

	printf("List2:");
	OutputList(list2);
	printf("\n");

	ds_list2.erase(ds_list2.begin());
	ds_list2.insert(ds_list2.begin(), 11);
	ds_list2.pop_back();


	printf("DS_List2:");
	OutputDSList(ds_list2);
	printf("\n");

	printf("List2 Reverse:");
	OutputListReverse(list2);
	printf("\n");

	printf("DS_List2 Reverse:");
	OutputDSListReverse(ds_list2);
	printf("\n");

	return 0;
}