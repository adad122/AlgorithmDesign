// DS_Vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <vector>

template <typename T>
class DS_Vector
{
public:
	DS_Vector();
	DS_Vector(const DS_Vector& that);
	DS_Vector& operator = (const DS_Vector& that);
	~DS_Vector();

	class iterator
	{
		template <typename T>
		friend class DS_Vector;

		DS_Vector* p; //指向的DS_Vector
		int index; //当前表示的DS_Vector中的节点

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
		friend class DS_Vector;

		DS_Vector* p; //指向的DS_Vector
		int index; //当前表示的DS_Vector中的节点

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
	int resize(int size, T value = T());
	int capacity();
	bool empty();
	int shrink_to_fit();

	T& operator [] (const int index);
	T& at(int index);
	T& front();
	T& back();


	void push_back(T data);
	void pop_back();
	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
	void clear();

protected:
	T* m_datas; //数据
	int m_size; //大小
	int m_capacity; //容积

	void _copy(const DS_Vector& that);
	void _expand();
};


template<typename T>
DS_Vector<T>::DS_Vector()
{
	m_datas = new T[8];
	m_size = 0;
	m_capacity = 8;
}

template<typename T>
DS_Vector<T>::DS_Vector(const DS_Vector & that)
{
	_copy(that);
}

template<typename T>
DS_Vector<T> & DS_Vector<T>::operator=(const DS_Vector & that)
{
	if (this != that)
	{
		delete m_datas;
		_copy(that);
	}

	return *this;
}

template<typename T>
DS_Vector<T>::~DS_Vector()
{
	delete m_datas;
}

template<typename T>
DS_Vector<T>::iterator::iterator()
{
	p = NULL;
	index = -1;
}

template<typename T>
bool DS_Vector<T>::iterator::operator!=(const iterator & that)
{
	return p != that.p || index != that.index;
}

template<typename T>
typename DS_Vector<T>::iterator & DS_Vector<T>::iterator::operator+(const int step)
{
	assert(p && index + step < p->size());
	index += step;
	return *this;
}

template<typename T>
typename DS_Vector<T>::iterator & DS_Vector<T>::iterator::operator-(const int step)
{
	assert(p && index - step >= 0);
	index -= step;
	return *this;
}

template<typename T>
typename DS_Vector<T>::iterator & DS_Vector<T>::iterator::operator++()
{
	assert(p && index < p->size());
	index++;
	return *this;
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::iterator::operator++(int)
{
	assert(p && index < p->size());
	iterator it = *this;
	index++;
	return it;
}

template<typename T>
typename DS_Vector<T>::iterator & DS_Vector<T>::iterator::operator--()
{
	assert(p && index > 0);
	index--;
	return *this;
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::iterator::operator--(int)
{
	assert(p && index > 0);
	iterator it = *this;
	index--;
	return it;
}

template<typename T>
T & DS_Vector<T>::iterator::operator*()
{
	assert(p && index >= 0 && index < p->size());
	return p->at(index);
}

template<typename T>
T * DS_Vector<T>::iterator::operator->()
{
	assert(p && index >= 0 && index < p->size());
	return &(p->at(index));
}

template<typename T>
DS_Vector<T>::reverse_iterator::reverse_iterator()
{
	p = NULL;
	index = -1;
}

template<typename T>
bool DS_Vector<T>::reverse_iterator::operator!=(const reverse_iterator & that)
{
	return p != that.p || index != that.index;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator & DS_Vector<T>::reverse_iterator::operator+(const int step)
{
	assert(p && index - step >= 0);
	index -= step;
	return *this;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator & DS_Vector<T>::reverse_iterator::operator-(const int step)
{
	assert(p && index + step < p->size());
	index += step;
	return *this;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator & DS_Vector<T>::reverse_iterator::operator++()
{
	assert(p && index >= 0);
	index--;
	return *this;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator DS_Vector<T>::reverse_iterator::operator++(int)
{
	assert(p && index >= 0);
	reverse_iterator it = *this;
	index--;
	return it;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator & DS_Vector<T>::reverse_iterator::operator--()
{
	assert(p && index < p->size() - 1);
	index++;
	return *this;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator DS_Vector<T>::reverse_iterator::operator--(int)
{
	assert(p && index < p->size() - 1);
	reverse_iterator it = *this;
	index++;
	return it;
}

template<typename T>
T & DS_Vector<T>::reverse_iterator::operator*()
{
	assert(p && index >= 0 && index < p->size());
	return p->at(index);
}

template<typename T>
T * DS_Vector<T>::reverse_iterator::operator->()
{
	assert(p && index >= 0 && index < p->size());
	return &(p->at(index));
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::begin()
{
	iterator it;
	it.p = this;
	it.index = 0;
	return it;
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::end()
{
	iterator it;
	it.p = this;
	it.index = m_size;
	return it;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator DS_Vector<T>::rbegin()
{
	reverse_iterator it;
	it.p = this;
	it.index = m_size - 1;
	return it;
}

template<typename T>
typename DS_Vector<T>::reverse_iterator DS_Vector<T>::rend()
{
	reverse_iterator it;
	it.p = this;
	it.index = -1;
	return it;
}

template<typename T>
int DS_Vector<T>::size()
{
	return m_size;
}

template<typename T>
int DS_Vector<T>::resize(int size, T value = T())
{
	if (size < m_size)
		m_size = size
	else
	{
		for (int i = 0; i < size - m_size; ++i)
		{
			push_back(value);
		}

		m_size = size;
	}
	return m_size;
}

template<typename T>
int DS_Vector<T>::capacity()
{
	return m_capacity;
}

template<typename T>
bool DS_Vector<T>::empty()
{
	return m_size == 0;
}

template<typename T>
int DS_Vector<T>::shrink_to_fit()
{
	if (m_capacity == m_size)
		return;

	m_capacity = m_size;
	T* newDatas = new T[m_capacity];
	memcpy_s(newDatas, sizeof(T) * m_capacity, m_datas, sizeof(T) * m_capacity / 2);
	m_datas = newDatas;

	return m_capacity;
}

template<typename T>
T& DS_Vector<T>::operator[](const int index)
{
	assert(index >=0 && index < m_size);
	return m_datas[index];
}

template<typename T>
T& DS_Vector<T>::at(int index)
{
	assert(index >= 0 && index < m_size);
	return m_datas[index];
}

template<typename T>
T& DS_Vector<T>::front()
{
	return m_datas[0];
}

template<typename T>
T& DS_Vector<T>::back()
{
	return m_datas[m_size - 1];
}

template<typename T>
void DS_Vector<T>::push_back(T data)
{
	insert(end(), data);
}

template<typename T>
void DS_Vector<T>::pop_back()
{
	if(empty())
		return;

	--m_size;
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::insert(iterator & it, T data)
{
	_expand();
	for (int i = m_size; i > it.index; --i)
	{
		m_datas[i] = m_datas[i - 1];
	}

	m_datas[it.index] = data;
	m_size++;

	it.index = 0;
	it.p = NULL;

	return it;
}

template<typename T>
typename DS_Vector<T>::iterator DS_Vector<T>::erase(iterator & it)
{
	for (int i = it.index; i < m_size - 1; ++i)
	{
		m_datas[i] = m_datas[i + 1];
	}

	m_size--;

	it.index = 0;
	it.p = NULL;


	return it;
}

template<typename T>
void DS_Vector<T>::clear()
{
	m_size = 0;
}

template<typename T>
void DS_Vector<T>::_copy(const DS_Vector & that)
{
	if (this == &that)
		return;


	m_datas = new T[that.m_capacity];

	for (int i = 0; i < that.m_size; ++i)
	{
		m_datas[i] = that.m_datas[i];
	}

	m_size = that.m_size;
	m_capacity = that.m_capacity;
}

template<typename T>
void DS_Vector<T>::_expand()
{
	if (m_size + 1 < m_capacity)
		return;

	T* newDatas = new T[m_capacity * 2];
	memcpy_s(newDatas, sizeof(T) * m_capacity * 2, m_datas, sizeof(T) * m_capacity);

	m_capacity *= 2;
	delete m_datas;
	m_datas = newDatas;
}

void OutputVector(std::vector<int>& vec)
{
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		printf("%d ", *it);
	}
}

void OutputDSVector(DS_Vector<int>& vec)
{
	for (DS_Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		printf("%d ", *it);
	}
}

void OutputVectorReverse(std::vector<int>& vec)
{
	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
	{
		printf("%d ", *it);
	}
}

void OutputDSVectorReverse(DS_Vector<int>& vec)
{
	for (DS_Vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
	{
		printf("%d ", *it);
	}
}

int main()
{
	int datas[10] = { 1,2,3,4,5,6,7,8,9,0 };

	std::vector<int> vector1;
	DS_Vector<int> ds_vector1;

	for (int i = 0; i < 10; ++i)
	{
		vector1.push_back(datas[i]);
		ds_vector1.push_back(datas[i]);
	}

	printf("Vector1:");
	OutputVector(vector1);
	printf("\n");

	printf("DS_Vector1:");
	OutputDSVector(ds_vector1);
	printf("\n");

	std::vector<int> vector2 = vector1;
	DS_Vector<int> ds_vector2 = ds_vector1;

	printf("Vector2:");
	OutputVector(vector2);
	printf("\n");

	printf("DS_Vector2:");
	OutputDSVector(ds_vector2);
	printf("\n");

	vector2.erase(vector2.begin() + 1);
	vector2.insert(vector2.begin() + 2, 11);
	vector2.pop_back();

	printf("Vector2:");
	OutputVector(vector2);
	printf("\n");

	ds_vector2.erase(ds_vector2.begin() + 1);
	ds_vector2.insert(ds_vector2.begin() + 2, 11);
	ds_vector2.pop_back();


	printf("DS_Vector2:");
	OutputDSVector(ds_vector2);
	printf("\n");

	printf("Vector2 Reverse:");
	OutputVectorReverse(vector2);
	printf("\n");

	printf("DS_Vector2 Reverse:");
	OutputDSVectorReverse(ds_vector2);
	printf("\n");

	return 0;
}