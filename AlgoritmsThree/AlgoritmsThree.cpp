// AlgoritmsThree.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

void NonRecursiveQuickSort(int *arr, int length)
{
	const int m = 200;
	int low[m], high[m], s = 0, min, max, i, j, temp, med;
	low[0] = 0;
	high[0] = length - 1;
	do
	{
		min = low[s];
		max = high[s];
		s--;
		do
		{
			i = min;
			j = max;
			temp = arr[(min + max) / 2];
			do
			{
				while (arr[i] < temp)
					i++;
				while (temp < arr[j])
					j--;
				if (i <= j)
				{
					med = arr[i];
					arr[i] = arr[j];
					arr[j] = med;
					i++;
					j--;
				}
			} while (i <= j);
			if (i < max)
			{
				s++;
				low[s] = i;
				high[s] = max;
			}
			max = j;
		} while (min < max);
	} while (s >= 0);
}

int main()
{
	setlocale(LC_CTYPE, "");
	int rootValue = rand();
	Tree<int>* root= new Tree<int>(rootValue);
	int n;
	cout << "¬ведите размер дерева" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int value = rand();
		root->Insert(value);
	}
	int width = 1;
	Tree<int>::SetWidh(width, *root);
	Tree<int>::PrintLeft(root, width);
	Tree<int>* path = root->GetMaxPathRoot();
	int left = Tree<int>::Height(path->left);
	int right = Tree<int>::Height(path->right);
	int* s = Tree<int>::StorePath(*path, left, right);
	if (s != 0)
	{
		int height = left + right + 1;
		NonRecursiveQuickSort(s, height);
		int median = s[height % 2 + 1];

	}
	int search;
	cin>>search;
    return 0;
}

