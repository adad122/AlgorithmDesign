// InsertionSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

int* InsertionSort(int* datas, int length)
{
	for (int i = 1; i < length; ++i)
	{
		int n = datas[i];

		int j = i - 1;

		while (j >= 0 && datas[j] > n)
		{
			datas[j + 1] = datas[j];
			j--;
		}

		datas[j + 1] = n;
	}

	return datas;
}

//5 2 4 6 1 3
//2 5 4 6 1 3
//2 4 5 6 1 3 
//2 4 5 6 1 3
//1 2 4 5 6 3
//1 2 3 4 5 6

int main()
{
	int datas[6] = {5, 2, 4, 6, 1, 3};

	Output(datas, 6);
	InsertionSort(datas, 6);
	Output(datas, 6);

    return 0;
}

