// SelectionSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

int* SelectionSort(int* datas, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		int index = i;

		for (int j = i; j < length - 1; ++j)
		{
			if (datas[index] > datas[j])
			{
				index = j;
			}
		}

		if (index != i)
		{
			int temp = datas[index];
			datas[index] = datas[i];
			datas[i] = temp;
		}
	}
	return datas;
}

//5 2 4 6 1 3
//1 2 4 6 5 3
//1 2 4 6 5 3
//1 2 3 6 5 4
//1 2 3 4 5 6
//1 2 3 4 5 6

int main()
{
	int datas[6] = { 5, 2, 4, 6, 1, 3 };

	Output(datas, 6);
	SelectionSort(datas, 6);
	Output(datas, 6);

	return 0;
}