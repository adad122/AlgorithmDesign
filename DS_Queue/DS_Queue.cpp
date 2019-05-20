// DS_Queue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>

template <typename T>
class DS_Queue
{
public:
	DS_Queue();
	DS_Queue(const DS_Queue& that);
	DS_Queue& operator = (const DS_Queue& that);
	~DS_Queue();


	int size();
	bool empty();


	T& front();
	T& back();
	void push(T data);
	void pop();

protected:
	T* m_datas; //数据
	int m_head; //头
	int m_rear; //尾
	int m_capacity; //容积
	int m_size; //容积

	void _copy(const DS_Queue& that);
	void _expand();
};

template<typename T>
void DS_Queue<T>::_copy(const DS_Queue & that)
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
	m_head = that.m_head;
	m_rear = that.m_rear;
}

template<typename T>
void DS_Queue<T>::_expand()
{
	if (m_rear + 1 == m_head && m_size + 1 == m_capacity)
	{

		T* newDatas = new T[m_capacity * 2];
		int head = m_head;
		int index = 0;
		while (head % m_capacity != m_rear)
		{
			newDatas[index++] = m_datas[head++ % m_capacity];
		}

		m_capacity *= 2;
		m_head = 0;
		m_rear = m_size;
		delete m_datas;
		m_datas = newDatas;
	}
}

template<typename T>
DS_Queue<T>::DS_Queue()
{
	m_size = m_head = m_rear = 0;
	m_capacity = 8;
	m_datas = new T[m_capacity];
}

template<typename T>
DS_Queue<T>::DS_Queue(const DS_Queue & that)
{
	_copy(that);
}

template<typename T>
DS_Queue<T> & DS_Queue<T>::operator=(const DS_Queue & that)
{
	if (this != &that)
	{
		delete m_datas;
		_copy(that);
	}
	return *this;
}

template<typename T>
DS_Queue<T>::~DS_Queue()
{
	delete m_datas;
}

template<typename T>
int DS_Queue<T>::size()
{
	return m_size;
}

template<typename T>
bool DS_Queue<T>::empty()
{
	return m_size == 0;
}

template<typename T>
T & DS_Queue<T>::front()
{
	if (empty())
		return *(new T());

	return m_datas[m_head % m_capacity];
}

template<typename T>
T & DS_Queue<T>::back()
{
	if (empty())
		return *(new T());

	return m_datas[m_rear % m_capacity];
}

template<typename T>
void DS_Queue<T>::push(T data)
{
	_expand();
	m_datas[m_rear++] = data;
	m_rear = m_rear % m_capacity;
	m_size++;
}

template<typename T>
void DS_Queue<T>::pop()
{
	if (!empty())
	{
		m_head = ++m_head % m_capacity;
		m_size--;
	}
}

//[-,-,-,-,-,-,-,-]
// h
// r
//[1,-,-,-,-,-,-,-] push(1)
// h
//   r
//[1,2,3,4,5,6,7,-] push(2) push(3) push(4) push(5) push(6) push(7)
// h
//               r
//[-,-,3,4,5,6,7,-] pop() pop()
//     h
//               r
//[9,10,3,4,5,6,7,8] push(8) push(9) push(10)
//      h
//      r
//[3,4,5,6,7,8,9,10,11,-,-,-,-,-,-] push(11) _expand() 
// h
//                     r
int main()
{
	std::queue<int> queue;
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.push(4);
	queue.push(5);
	queue.push(6);
	queue.push(7);

	queue.pop();
	queue.pop();

	queue.push(8);
	queue.push(9);
	queue.push(10);
	queue.push(11);
	queue.push(12);
	queue.push(13);
	queue.pop();

	printf("queue:\n");
	while (!queue.empty())
	{
		printf("%d ", queue.front());
		queue.pop();
	}


	DS_Queue<int> ds_queue;
	ds_queue.push(1);
	ds_queue.push(2);
	ds_queue.push(3);
	ds_queue.push(4);
	ds_queue.push(5);
	ds_queue.push(6);
	ds_queue.push(7);

	ds_queue.pop();
	ds_queue.pop();

	ds_queue.push(8);
	ds_queue.push(9);
	ds_queue.push(10);
	ds_queue.push(11);
	ds_queue.push(12);
	ds_queue.push(13);
	ds_queue.pop();

	printf("\nDS_Queue:\n");
	while (!ds_queue.empty())
	{
		printf("%d ", ds_queue.front());
		ds_queue.pop();
	}

	return 0;
}
