// QuickSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

int _QuickSort(int* datas, int p, int r)
{
	int mid = p - 1;

	for (int i = p; i < r; ++i)
	{
		if (datas[i] <= datas[r])
		{
			mid++;

			if (mid != i)
			{
				int temp = datas[mid];
				datas[mid] = datas[i];
				datas[i] = temp;
			}
		}
	}

	mid++;

	int temp = datas[mid];
	datas[mid] = datas[r];
	datas[r] = temp;

	return mid;
}

void QuickSort(int* datas, int p, int r)
{
	if (r > p)
	{
		int mid = _QuickSort(datas, p, r);
		QuickSort(datas, p, mid - 1);
		QuickSort(datas, mid + 1, r);
	}
}

int Random(int min, int max)
{
	return min + rand() % (max - min);
}

int _QuickSortRandomPivot(int* datas, int p, int r)
{
	int index = Random(p, r);

	int temp = datas[index];
	datas[index] = datas[r];
	datas[r] = temp;

	return _QuickSort(datas, p, r);
}

void QuickSortRandomPivot(int* datas, int p, int r)
{
	if (r > p)
	{
		int mid = _QuickSortRandomPivot(datas, p, r);
		QuickSortRandomPivot(datas, p, mid - 1);
		QuickSortRandomPivot(datas, mid + 1, r);
	}
}

//2, 8, 7, 1, 3, 5, 6, 4

//2, 8, 7, 1, 3, 5, 6, 4
//2, 8, 7, 1, 3, 5, 6, 4
//2, 8, 7, 1, 3, 5, 6, 4
//2, 1, 7, 8, 3, 5, 6, 4
//2, 1, 3, 8, 7, 5, 6, 4
//2, 1, 3, (4), 7, 5, 6, 8

//2, 1, 3, (4), 7, 5, 6, 8
//2, 1, (3), (4), 7, 5, 6, (8)

//2, 1, (3), (4), 7, 5, 6, (8)
//(1), (2), (3), (4), (5), (6), (7), (8)


int main()
{
	srand(int(time(0)));

	int datas[8] = { 2, 8, 7, 1, 3, 5, 6, 4 };

	Output(datas, 8);
	QuickSortRandomPivot(datas, 0, 7);
	Output(datas, 8);

	return 0;
}