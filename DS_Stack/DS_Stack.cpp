// DS_Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>

template <typename T>
class DS_Stack
{
public:
	DS_Stack();
	DS_Stack(const DS_Stack& that);
	DS_Stack& operator = (const DS_Stack& that);
	~DS_Stack();


	int size();
	bool empty();


	T& top();
	void push(T data);
	void pop();

protected:
	T* m_datas; //数据
	int m_size; //大小
	int m_capacity; //容积

	void _copy(const DS_Stack& that);
	void _expand();
};

template<typename T>
void DS_Stack<T>::_copy(const DS_Stack & that)
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
void DS_Stack<T>::_expand()
{
	if (m_size + 1 < m_capacity)
		return;

	T* newDatas = new T[m_capacity * 2];
	memcpy_s(newDatas, sizeof(T) * m_capacity * 2, m_datas, sizeof(T) * m_capacity);

	m_capacity *= 2;
	delete m_datas;
	m_datas = newDatas;
}

template<typename T>
DS_Stack<T>::DS_Stack()
{
	m_capacity = 8;
	m_size = 0;
	m_datas = new T[m_capacity];
}

template<typename T>
DS_Stack<T>::DS_Stack(const DS_Stack & that)
{
	_copy(that);
}

template<typename T>
DS_Stack<T> & DS_Stack<T>::operator=(const DS_Stack & that)
{
	if (this != &that)
	{
		delete m_datas;
		_copy(that);
	}
	return *this;
}

template<typename T>
DS_Stack<T>::~DS_Stack()
{
	delete m_datas;
}

template<typename T>
int DS_Stack<T>::size()
{
	return m_size;
}

template<typename T>
bool DS_Stack<T>::empty()
{
	return m_size == 0;
}

template<typename T>
T & DS_Stack<T>::top()
{
	return m_datas[m_size];
}

template<typename T>
void DS_Stack<T>::push(T data)
{
	_expand();
	m_datas[++m_size] = data;
}

template<typename T>
void DS_Stack<T>::pop()
{
	if (empty())
		return;

	m_size--;
}

int main()
{
	std::stack<int> stack1;
	DS_Stack<int> ds_stack1;

	for (int i = 0; i < 10; ++i)
	{
		stack1.push(i);
		ds_stack1.push(i);
	}

	printf("stack1 top: %d\n", stack1.top());
	printf("ds_stack1 top: %d\n", ds_stack1.top());

	std::stack<int> stack2 = stack1;
	DS_Stack<int> ds_stack2 = ds_stack1;

	stack2.pop();
	stack2.pop();
	stack2.push(11);

	ds_stack2.pop();
	ds_stack2.pop();
	ds_stack2.push(11);

	printf("stack2:\n");
	while (!stack2.empty())
	{
		printf("%d ", stack2.top());
		stack2.pop();
	}

	printf("\nds_stack2:\n");
	while (!ds_stack2.empty())
	{
		printf("%d ", ds_stack2.top());
		ds_stack2.pop();
	}

	return 0;
}