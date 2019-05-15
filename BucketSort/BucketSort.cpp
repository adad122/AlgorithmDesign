// BucketSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cmath>

class Bucket
{
public:
	Bucket();
	~Bucket();
	void InsertData(int data);
	void ClearDatas();
	int* GetSortedDatas();
	int GetLength();

private:
	int* _datas;
	int _length;
	int _size;
	bool sorted;
	void DoInsertionSort();
	void Expand();
};

Bucket::Bucket()
{
	_datas = new int[8];
	_length = 0;
	_size = 8;
	sorted = false;
}

Bucket::~Bucket()
{
	delete _datas;
}

void Bucket::InsertData(int data)
{
	if (_length == _size - 1)
	{
		Expand();
	}

	_datas[_length++] = data;
	sorted = false;
}

void Bucket::ClearDatas()
{
	_length = 0;
	sorted = false;
}

int * Bucket::GetSortedDatas()
{
	DoInsertionSort();
	return _datas;
}

int Bucket::GetLength()
{
	return _length;
}

void Bucket::DoInsertionSort()
{
	if (sorted)
		return;

	for (int i = 1; i < _length; ++i)
	{
		int n = _datas[i];

		int j = i - 1;

		while (j >= 0 && _datas[j] > n)
		{
			_datas[j + 1] = _datas[j];
			j--;
		}

		_datas[j + 1] = n;
	}
	sorted = true;
}

void Bucket::Expand()
{
	int* newDatas = new int[_size * 2];
	memcpy_s(newDatas, _size * 2 * 4, _datas, _size * 4);
	delete _datas;

	_size *= 2;
	_datas = newDatas;
}

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

void BucketSort(int* datas, int length, int high)
{
	Bucket buckets[10];

	int b = (int)pow(10, high - 1);

	for (int j = 0; j < length; ++j)
	{
		int radix = (datas[j] / b) % 10;
		buckets[radix].InsertData(datas[j]);
	}

	int index = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (buckets[i].GetLength() > 0)
		{
			int* sortedDatas = buckets[i].GetSortedDatas();

			for (int j = 0; j < buckets[i].GetLength(); ++j)
			{
				datas[index++] = sortedDatas[j];
			}

			buckets[i].ClearDatas();
		}
	}
}

//29 25 3 49 9 37 21 43

// 0 : 3 9
// 1 : 29 25 21
// 2 : 
// 3 : 37
// 4 : 49 43
// 5 : 
// 6 : 
// 7 : 
// 8 : 
// 9 : 

// 0 : 3 9
// 1 : 21 25 29
// 2 : 
// 3 : 37
// 4 : 43 49
// 5 : 
// 6 : 
// 7 : 
// 8 : 
// 9 : 

//3 9 21 25 29 37 43 49
int main()
{
	int datas[8] = { 29, 25, 3, 49, 9, 37, 21, 43};
	Output(datas, 8);
	BucketSort(datas, 8, 2);
	Output(datas, 8);

    return 0;
}

