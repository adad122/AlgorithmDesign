// MergeSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

void Merge(int* datas, int p, int q, int r)
{
	int n1 = q + 1 - p;
	int n2 = r - q;

	int* leftDatas = new int[n1];

	for (int i = 0; i < n1; ++i)
	{
		leftDatas[i] = datas[p + i];
	}

	int* rightDatas = new int[n2];

	for (int i = 0; i < n2; ++i)
	{
		rightDatas[i] = datas[q + 1 + i];
	}

	int index1 = 0, index2 = 0;

	for (int i = p; i <= r; ++i)
	{
		if (index2 >= n2 || (leftDatas[index1] < rightDatas[index2] && index1 < n1))
		{
			datas[i] = leftDatas[index1];
			index1++;
		}
		else if(index1 >= n1 || (rightDatas[index2] < leftDatas[index1] && index2 < n2))
		{
			datas[i] = rightDatas[index2];
			index2++;
		}
	}
}

void MergeSort(int* datas, int p, int r)
{
	if (r > p)
	{
		int q = (r + p) / 2;
		MergeSort(datas, p, q);
		MergeSort(datas, q + 1, r);
		Merge(datas, p, q, r);
	}
}

//5 2 4 6 1 3
//5 2 4 6 1 3
//2 5 4 1 6 3
//2 4 5 1 3 6
//1 2 3 4 5 6

int main()
{
	int datas[6] = { 5, 2, 4, 6, 1, 3 };

	Output(datas, 6);
	MergeSort(datas, 0, 5);
	Output(datas, 6);

	return 0;
}