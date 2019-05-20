// PriorityQueue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();

	bool IsEmpty();

	virtual void Enqueue(int data) = 0;
	int Dequeue();
	int Top();
	virtual void ChangeValueByIndex(int key, int data) = 0;

protected:
	int* _datas;
	int _length;
	int _size;

	virtual void Adjust(int index) = 0;

	void Expand();
	int Parent(int index);
	int Left(int index);
	int Right(int index);
};

PriorityQueue::PriorityQueue()
{
	_datas = new int[8];
	_size = 8;
	_length = 0;
}

PriorityQueue::~PriorityQueue()
{
	delete _datas;
}

int PriorityQueue::Top()
{
	return _datas[1];
}

int PriorityQueue::Dequeue()
{
	if (_length < 1)
		return -1;

	int head = _datas[1];
	_datas[1] = _datas[_length];
	_length--;
	Adjust(1);

	return head;
}

void PriorityQueue::Expand()
{
	int* newDatas = new int[_size * 2];
	memcpy_s(newDatas, _size * 2 * sizeof(int), _datas, _size * sizeof(int));
	delete _datas;

	_size *= 2;
	_datas = newDatas;
}

bool PriorityQueue::IsEmpty()
{
	return _length == 0;
}

int PriorityQueue::Parent(int index)
{
	return index / 2;
}

int PriorityQueue::Left(int index)
{
	return index * 2;
}

int PriorityQueue::Right(int index)
{
	return index * 2 + 1;
}

class MaxPriorityQueue : public PriorityQueue
{
public:
	virtual void Enqueue(int data);
	virtual void ChangeValueByIndex(int key, int data);

protected:
	virtual void Adjust(int index);
};


void MaxPriorityQueue::Enqueue(int data)
{
	if (_length == _size - 1)
	{
		Expand();
	}

	_datas[++_length] = data;

	int index = _length;

	while (index > 1 && _datas[index] > _datas[Parent(index)])
	{
		int temp = _datas[index];
		_datas[index] = _datas[Parent(index)];
		_datas[Parent(index)] = temp;
		index = Parent(index);
	}
}



void MaxPriorityQueue::ChangeValueByIndex(int key, int data)
{
	if (key < 1 || key > _length || _datas[key] > data)
		return;

	_datas[key] = data;

	int index = key;

	while (index > 1 && _datas[index] > _datas[Parent(index)])
	{
		int temp = _datas[index];
		_datas[index] = _datas[Parent(index)];
		_datas[Parent(index)] = temp;
		index = Parent(index);
	}
}

void MaxPriorityQueue::Adjust(int index)
{
	int left = Left(index);
	int right = Right(index);

	int largest = index;

	if (left <= _length && _datas[left] > _datas[index])
	{
		largest = left;
	}

	if (right <= _length && _datas[right] > _datas[largest])
	{
		largest = right;
	}

	if (largest != index)
	{
		int temp = _datas[index];
		_datas[index] = _datas[largest];
		_datas[largest] = temp;

		Adjust(largest);
	}
}

class MinPriorityQueue : public PriorityQueue
{
public:
	virtual void Enqueue(int data);
	virtual void ChangeValueByIndex(int key, int data);

protected:
	virtual void Adjust(int index);
};


void MinPriorityQueue::Enqueue(int data)
{
	if (_length == _size - 1)
	{
		Expand();
	}

	_datas[++_length] = data;

	int index = _length;

	while (index > 1 && _datas[index] < _datas[Parent(index)])
	{
		int temp = _datas[index];
		_datas[index] = _datas[Parent(index)];
		_datas[Parent(index)] = temp;
		index = Parent(index);
	}
}

void MinPriorityQueue::ChangeValueByIndex(int key, int data)
{
	if (key < 1 || key > _length || _datas[key] < data)
		return;

	_datas[key] = data;

	int index = key;

	while (index > 1 && _datas[index] < _datas[Parent(index)])
	{
		int temp = _datas[index];
		_datas[index] = _datas[Parent(index)];
		_datas[Parent(index)] = temp;
		index = Parent(index);
	}
}

void MinPriorityQueue::Adjust(int index)
{
	int left = Left(index);
	int right = Right(index);

	int min = index;

	if (left <= _length && _datas[left] < _datas[index])
	{
		min = left;
	}

	if (right <= _length && _datas[right] < _datas[min])
	{
		min = right;
	}

	if (min != index)
	{
		int temp = _datas[index];
		_datas[index] = _datas[min];
		_datas[min] = temp;

		Adjust(min);
	}
}

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

int main()
{
	int datas[9] = { 5, 13, 2, 25, 7, 17, 20, 8, 4 };

	Output(datas, 9);

	PriorityQueue* maxQueue = new MaxPriorityQueue();
	PriorityQueue* minQueue = new MinPriorityQueue();

	for (int i = 0; i < 9; ++i)
	{
		maxQueue->Enqueue(datas[i]);
		minQueue->Enqueue(datas[i]);
	}

	while (!maxQueue->IsEmpty())
	{
		printf("%d ", maxQueue->Dequeue());
	}

	printf("\n");

	while (!minQueue->IsEmpty())
	{
		printf("%d ", minQueue->Dequeue());
	}

	printf("\n");

	delete minQueue;
	delete maxQueue;

	return 0;
}