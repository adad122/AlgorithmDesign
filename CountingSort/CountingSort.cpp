// CountingSort.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

void CountingSort(int* inputData, int* outputData, int k, int length)
{
	int* counts = new int[k];

	for (int i = 0; i < k; ++i)
	{
		counts[i] = 0;
	}

	for (int i = 0; i < length; ++i)
	{
		counts[inputData[i]]++;
	}

	for (int i = 1; i < k; ++i)
	{
		counts[i] = counts[i - 1] + counts[i];
	}

	for (int i = 0; i < length; ++i)
	{
		if (counts[inputData[i]] > 0)
		{
			outputData[counts[inputData[i]] - 1] = inputData[i];
			counts[inputData[i]]--;
		}
	}

	delete counts;
}

//i 6 0 0 1 3 4 6 1 3 2
//o 
//c 

//i 6 0 0 1 3 4 6 1 3 2
//o 
//c 0 1 2 3 4 5 6
//  2 2 1 2 1 0 2

//i 6 0 0 1 3 4 6 1 3 2
//o 
//c 0 1 2 3 4 5 6
//  2 4 5 7 8 8 10

//i 6 0 0 1 3 4 6 1 3 2
//o                   6
//c 0 1 2 3 4 5 6
//  2 4 5 7 8 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o   0               6
//c 0 1 2 3 4 5 6
//  1 4 5 7 8 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0               6
//c 0 1 2 3 4 5 6
//  0 4 5 7 8 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0   1           6
//c 0 1 2 3 4 5 6
//  0 3 5 7 8 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0   1     3     6
//c 0 1 2 3 4 5 6
//  0 3 5 6 8 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0   1     3 4   6
//c 0 1 2 3 4 5 6
//  0 3 5 6 7 8 9

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0   1     3 4 6 6
//c 0 1 2 3 4 5 6
//  0 3 5 6 7 8 8

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0 1 1     3 4 6 6
//c 0 1 2 3 4 5 6
//  0 2 5 6 7 8 8

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0 1 1   3 3 4 6 6
//c 0 1 2 3 4 5 6
//  0 2 5 5 7 8 8

//i 6 0 0 1 3 4 6 1 3 2
//o 0 0 1 1 2 3 3 4 6 6
//c 0 1 2 3 4 5 6
//  0 2 4 5 7 8 8

int main()
{
	int datas[10] = { 6, 0, 0, 1, 3, 4, 6, 1, 3, 2 };
	int outputDats[10];

	int k = datas[0];

	for (int i = 0; i < 10; ++i)
	{
		if (k < datas[i])
		{
			k = datas[i];
		}
	}

	Output(datas, 10);
	CountingSort(datas, outputDats, k + 1, 10);
	Output(outputDats, 10);

	return 0;
}