// RadixSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cmath>
#include <vector>

void Output(int* datas, int length)
{
	for (int i = 0; i < length; ++i)
		printf("%d ", datas[i]);

	printf("\n");
}

void RadixSort(int* datas, int length, int bit)
{
	std::vector<int> buckets[10];

	for (int i = 0; i < bit; ++i)
	{
		int b = (int)pow(10, i);

		for (int j = 0; j < length; ++j)
		{
			int radix = (datas[j] / b) % 10;
			buckets[radix].push_back(datas[j]);
		}

		int index = 0;
		for (int j = 0; j < 10; ++j)
		{
			for (int k = 0; k < buckets[j].size(); ++k)
			{
				datas[index++] = buckets[j][k];
			}

			buckets[j].clear();
		}
	}
}

//73 22 93 43 55 14 28 65 39 81

// 个位
// 0 :
// 1 : 81
// 2 : 22
// 3 : 73 93 43
// 4 : 14
// 5 : 55 65
// 6 :
// 7 :
// 8 : 28
// 9 : 39

//81 22 73 93 43 14 55 65 28 39

// 十位
// 0 :
// 1 : 14
// 2 : 28
// 3 : 39
// 4 : 43
// 5 : 55
// 6 : 65
// 7 : 73
// 8 : 81
// 9 : 93

//14 28 39 43 55 65 73 81 93
int main()
{
	int datas[10] = { 73, 22, 93, 43, 55, 14, 28, 65, 39, 81};
	Output(datas, 10);
	RadixSort(datas, 10, 2);
	Output(datas, 10);

	return 0;
}
