// BubbleSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

int* BubbleSort(int* datas, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = i; j < length; ++j)
		{
			if (datas[i] > datas[j])
			{
				int temp = datas[j];
				datas[j] = datas[i];
				datas[i] = temp;
			}
		}
	}

	return datas;
}



int* BubbleSort2(int* datas, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - 1 - i; ++j)
		{
			if (datas[j] > datas[j + 1])
			{
				int temp = datas[j];
				datas[j] = datas[j + 1];
				datas[j+1] = temp;
			}
		}
	}

	return datas;
}

int* BubbleSort3(int* datas, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		bool swaped = false;

		for (int j = 0; j < length - 1 - i; ++j)
		{
			if (datas[j] > datas[j + 1])
			{
				int temp = datas[j];
				datas[j] = datas[j + 1];
				datas[j + 1] = temp;
				swaped = true;
			}
		}

		if (!swaped)
			break;
	}

	return datas;
}

//5, 2, 4, 6, 1, 3
//1, 5, 4, 6, 2, 3
//1, 2, 5, 6, 4, 3
//1, 2, 3, 6, 5, 4
//1, 2, 3, 4, 6, 5
//1, 2, 3, 4, 5, 6


int main()
{
	int datas[6] = { 5, 2, 4, 6, 1, 3 };

	Output(datas, 6);
	BubbleSort3(datas, 6);
	Output(datas, 6);

	return 0;
}