// AlgoritmsThree.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;


int main()
{
	int rootValue = rand();
	Tree<int>* root= new Tree<int>(rootValue);
	for (int i = 0; i < 9; i++)
	{
		int value = rand();
		root->Insert(value);
	}
	int width = 1;
	Tree<int>::SetWidh(width, *root);
	Tree<int>::Print(*root);
	Tree<int>* path = root->GetMaxPathRoot();
	int search;
	cin >> search;
    return 0;
}

