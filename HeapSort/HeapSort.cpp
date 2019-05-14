// HeapSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
class Heap
{
public:
	Heap(int* datas, int length);
	~Heap();
	void BuildHeap();
	int* Sort();


protected:
	int* _datas;
	int _length;

	virtual void Adjust(int index) = 0;
	int Parent(int index);
	int Left(int index);
	int Right(int index);
};

Heap::Heap(int* datas, int length)
{
	_datas = new int[length + 1];
	_length = length;

	for (int i = 0; i < length; ++i)
	{
		_datas[i + 1] = datas[i];
	}
}

Heap::~Heap()
{
	delete _datas;
}



int* Heap::Sort()
{
	int index = 0;

	int size = _length;

	int* datas = new int[size];

	while (index < size)
	{
		datas[index] = _datas[1];
		_datas[1] = _datas[_length];
		_length--;
		Adjust(1);
		index++;
	}

	return datas;
}

void Heap::BuildHeap()
{
	for (int i = _length / 2; i > 0; --i)
		Adjust(i);
}

int Heap::Parent(int index)
{
	return index / 2;
}

int Heap::Left(int index)
{
	return index * 2;
}

int Heap::Right(int index)
{
	return index * 2 + 1;
}

class MaxHeap : public Heap
{
public:
	MaxHeap(int* datas, int length);
	~MaxHeap();

protected:
	void virtual Adjust(int index);
};

MaxHeap::MaxHeap(int * datas, int length):Heap(datas, length)
{
}

MaxHeap::~MaxHeap()
{
}

void MaxHeap::Adjust(int index)
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


class MinHeap : public Heap
{
public:
	MinHeap(int* datas, int length);
	~MinHeap();

protected:
	void virtual Adjust(int index);
};

MinHeap::MinHeap(int * datas, int length) :Heap(datas, length)
{
}

MinHeap::~MinHeap()
{
}

void MinHeap::Adjust(int index)
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


int* MaxHeapSort(int* datas, int length)
{
	Heap* maxHeap = new MaxHeap(datas, length);
	maxHeap->BuildHeap();
	int* data = maxHeap->Sort();
	delete maxHeap;

	return data;
}

int* MinHeapSort(int* datas, int length)
{
	Heap* minHeap = new MinHeap(datas, length);
	minHeap->BuildHeap();
	int* data = minHeap->Sort();
	delete minHeap;

	return data;
}

//          5
//     13       2
//  25    7   17   20
//8    4 

//          25
//     13       20
//  8    7   17   2
//5    4 

//          20
//     13       17
//  8    7   4   2
//5     
//                       25

//          17
//     13       5
//  8    7   4    2
//                       25 20

//          13
//     8       5
//  2    7   4     
//                       25 20 17

//          8
//     7       5
//  2    4         
//                       25 20 17 13

//          7
//     4       5
//  2               
//                       25 20 17 13 8

//          5
//     4       2        
//                       25 20 17 13 8 7

//          4
//     2              
//                       25 20 17 13 8 7 5

//          2
//                   
//                       25 20 17 13 8 7 5 4

//                       25 20 17 13 8 7 5 4 2


//          5
//     13        2
//  25    7   17   20
//8    4 

//          2
//     4         5
//  13    7   17   20
//8    25 

//          4
//     7         5
//  13    25   17   20
//8      
//						2 

//          5
//     7         8
//  13    25   17   20
//						2 4

//          7
//     13         8
//  20    25   17   
//						2 4 5

//          8
//     13         17
//  20    25   
//						2 4 5 7

//          13
//     20         17
//  25    
//						2 4 5 7 8

//          17
//     20         25
//						2 4 5 7 8 13

//          20
//     25         
//						2 4 5 7 8 13 17

//          25      
//						2 4 5 7 8 13 17 20

//						2 4 5 7 8 13 17 20 25

int main()
{
	int datas[9] = { 5, 13, 2, 25, 7, 17, 20, 8, 4};

	Output(datas, 9);
	int* data1 = MaxHeapSort(datas, 9);
	Output(data1, 9);
	int* data2 = MinHeapSort(datas, 9);
	Output(data2, 9);

	return 0;
}
