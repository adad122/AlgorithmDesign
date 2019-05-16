// HalfSearch.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int HalfSearch(int* datas, int length, int data)
{
	int low = 0;
	int high = length - 1;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (data < datas[mid])
		{
			high = mid - 1;
		}
		else if (data > datas[mid])
		{
			low = mid + 1;
		}
		else
			return mid;
	}

	return -1;
}

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

//14 22 28 39 43 55 65 73 81 93 (5)
// l           m              h

//14 22 28 39
// l  m    h

//14
// l  
// h
// m

int main()
{
	int datas[10] = { 14, 22, 28, 39, 43, 55, 65, 73, 81, 93 };

	Output(datas, 10);
	printf("14 Index = %d\n", HalfSearch(datas, 10, 14));
	printf("65 Index = %d\n", HalfSearch(datas, 10, 65));
	printf("11 Index = %d\n", HalfSearch(datas, 10, 11));

    return 0;
}

