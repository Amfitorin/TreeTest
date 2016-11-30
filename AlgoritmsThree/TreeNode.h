#pragma once
#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <queue>;
template<class T> class Tree
{

public:
	struct TreePath
	{
		Tree* root;
		int height;
		int left;
		int right;
	} path;

	Tree(Tree& parent);
	Tree(T& value);
	Tree(T& value, int& height);
	~Tree();
	void CreateLeft(const T& value);
	void CreateRight(const T& value);
	void SetValue(const T& value);
	void SetLeft(Tree& element);
	void SetRight(Tree& element);
	void Insert(T& element);
	static void PrintNode(int& space, Tree& root);
	static void Print(Tree& root);
	static void PrintLeft( Tree* root, int& h );
	static void SetWidh(int& space, Tree& root);
	static int GetWidth(int& width, Tree& root);
	static int Height(Tree* root);
	void MaxPath( Tree* root, TreePath& maxPath );
	Tree<T>* GetMaxPathRoot();
	static int CheckPath( Tree& root, int& left, int& right );
	static T* StorePath(Tree& root, int& left, int& right);
	Tree* left;
	Tree* right;
	T value;

private:
	int width;
	int height;
	Tree* prev;
};

template <class T>
Tree<T>::Tree(Tree& parent)
{
	prev = &parent;
	this->height = 0;
}

template <class T>
Tree<T>::Tree(T& value)
{
	this->value = value;
	this->height = 0;
}

template<class T>
inline Tree<T>::Tree(T & value, int & height)
{
	this->value = value;
	this->height = height;
}

template <class T>
Tree<T>::~Tree()
{
	if (left) delete left;
	if (right) delete right;
}

template <class T>
void Tree<T>::CreateLeft(const T& value)
{
	Tree* child = new Tree(*this);
	child->SetValue(value);
	left = child;
}

template <class T>
void Tree<T>::CreateRight(const T& value)
{
	Tree* child = new Tree(*this);
	child->SetValue(value);
	right = child;
}

template <class T>
void Tree<T>::SetValue(const T& value)
{
	this->value = value;
}

template <class T>
void Tree<T>::SetLeft(Tree & element)
{
	element.prev = this;
	this->left = &element;
}

template <class T>
void Tree<T>::SetRight(Tree & element)
{
	element.prev = this;
	this->right = &element;
}

template<class T>
void Tree<T>::Insert(T & element)
{
	Tree* child = new Tree(element, height);
	Tree* root = this;
	while (true)
	{
		int height = root->height + 1;
		if (element > root->value)
			if (root->right)
			{
				root = root->right;
				continue;
			}
			else
			{
				child->height = height;
				root->SetRight(*child);
				break;
			}
		if (element < root->value)
			if (root->left)
			{
				root = root->left;
				continue;
			}
			else
			{
				child->height = height;
				root->SetLeft(*child);
				break;
			}
	}
}

template<class T>
inline void Tree<T>::PrintNode(int& space, Tree& root)
{
	cout << cout.width(6 * space ) << root.value;
}

template<class T>
inline void Tree<T>::Print( Tree& root)
{
	queue<Tree*> tree;
	tree.push(&root);
	int height = 0;
	Tree* temp;
	int lastwidth = 0;
	int widht = 0;
	while (!tree.empty())
	{
		temp = tree.front();
		tree.pop();
		if (temp->height > height)
		{
			cout << endl;
			lastwidth = 0;
			height = temp->height;
		}
		widht = temp->width - lastwidth;
		PrintNode(widht, *temp);
		lastwidth = temp->width;
		if (temp->left != NULL)
			tree.push(temp->left);
		if (temp->right != NULL)
			tree.push(temp->right);
	}
}

template<class T>
inline void Tree<T>::PrintLeft(Tree* root, int & h)
{
	if (root != 0)
	{
		int i = h + 3;
		PrintLeft(root->left, i);
		cout << cout.width(h) << root->value<<endl;
		PrintLeft(root->right, i );
	}
}

template<class T>
inline void Tree<T>::SetWidh(int & space, Tree & root)
{
	int width = 0;
	int split = space;
	if (root.left != NULL)
	{
		width = GetWidth(width, *root.left);
		split += width;
		SetWidh(space, *root.left);
	}
	root.width = split;
	if (root.right != NULL)
	{
		split++;
		SetWidh(split, *root.right);
	}
}

template<class T>
inline int Tree<T>::GetWidth(int & width, Tree & root)
{
	width += 1;
	if (root.left != NULL)
		width = GetWidth(width, *root.left);
	if (root.right != NULL)
		width = GetWidth(width, *root.right);
	return width;
}

template<class T>
inline int Tree<T>::Height(Tree * root)
{
	int l = 0, r = 0, result;
	if (root != 0)
	{
		l = Height(root->left);
		r = Height(root->right);
		if (l > r)
			result = l + 1;
		else
			result = r + 1;
	}
	else
		result = 0;
	return result;
}

template<class T>
inline void Tree<T>::MaxPath(Tree* root, TreePath& maxPath)
{
	if (root)
	{
		int leftHeight = Height(root->left);
		int rightHeight = Height(root->right);
		int height;
		if ( leftHeight == rightHeight)
			height = leftHeight + rightHeight;
		else
			height = leftHeight + rightHeight + 1;
		if (!maxPath.root || maxPath.height < leftHeight + rightHeight + 1)
		{
			maxPath.root = root;
			maxPath.height = height;
			maxPath.left = leftHeight;
			maxPath.right = rightHeight;
		}
		else if ( maxPath.height == height )
		{
			int firstPath = CheckPath( *maxPath.root, maxPath.left, maxPath.right);
			int secondPath = CheckPath( *root, leftHeight, rightHeight);
			if ( secondPath < firstPath)
			{
				maxPath.root = root;
				maxPath.height = height;
				maxPath.left = leftHeight;
				maxPath.right = rightHeight;	
			}
		}
		MaxPath(root->left, maxPath);
		MaxPath(root -> right, maxPath);
	}
}
template<class T>
inline Tree<T>* Tree<T>::GetMaxPathRoot()
{
	path.root = this;
	path.left = Height(this->left);
	path.right = Height( this -> right );
	path.height =  path.left + path.right + 1;
	MaxPath(this, path);
	return path.root;
}
template<class T>
inline int Tree<T>::CheckPath( Tree& root, int& left, int& right )
{
	int rightParent = 0;
	int leftParent = 0;
	int rightChild = 0;
	int leftChild = 0;
	if (left == right)
	{
		Tree<T>* tempRoot;
		int temp = left-1;
		if (temp >= 0)
		{
			tempRoot = root.left;
			if (temp == 1)
				leftParent = tempRoot->value;
			while (temp > 0)
			{
				if (Height(tempRoot->left) >= Height(tempRoot->right))
					tempRoot = tempRoot->left;
				else
					tempRoot = tempRoot->right;
				temp--;
				if (temp == 1)
					leftParent = tempRoot->value;
			}
			leftChild = tempRoot->value;
		}
		temp = right -1 ;
		if (temp >= 0)
		{
			tempRoot = root.right;
			if (temp == 1)
				rightParent = tempRoot->value;
			while (temp > 0)
			{
				if (Height(tempRoot->left) >= Height(tempRoot->right))
					tempRoot = tempRoot->left;
				else
					tempRoot = tempRoot->right;
				temp--;
				if (temp == 1)
					rightParent = tempRoot->value;
			}
			rightChild = tempRoot->value;
		}
		return min( leftParent + rightChild, rightParent+leftChild);
	}
	else
	{
		Tree<T>* tempRoot;
		int temp = left-1;
		if (temp >= 0)
		{
			tempRoot = root.left;
			while (temp > 0)
			{
				if (Height(tempRoot->left) >= Height(tempRoot->right))
					tempRoot = tempRoot->left;
				else
					tempRoot = tempRoot->right;
				temp--;
			}
			leftChild = tempRoot->value;
		}
		temp = right-1;
		if (temp >= 0)
		{
			tempRoot = root.right;
			while (temp > 0)
			{
				if (Height(tempRoot->left) >= Height(tempRoot->right))
					tempRoot = tempRoot->left;
				else
					tempRoot = tempRoot->right;
				temp--;
			}
			rightChild = tempRoot->value;
		}
		return rightChild + leftChild;
	}	
}
template<class T>
inline T* Tree<T>::StorePath(Tree & root, int & left, int & right)
{
	int height = left == right ? left + right : left + right + 1;
	if (height % 2 == 0)
	{
		cout << endl << "К сожалению медиану вычмслить невозможно, количество вершин четное" << endl;
		return NULL;
	}
	T* result = new T[height];
	int index = 1;
	result[0] = root.value;
	Tree<T>* tempRoot;
	int temp = left-1;
	if (temp >= 0)
	{
		tempRoot = root.left;
		while (temp >= 0)
		{
			result[index] = tempRoot->value;
			index++;
			if (Height(tempRoot->left) >= Height(tempRoot->right))
				tempRoot = tempRoot->left;
			else
				tempRoot = tempRoot->right;
			temp--;
		}
	}
	temp = right-1;
	if (temp >= 0)
	{
		tempRoot = root.right;
		while (temp >= 0)
		{
			result[index] = tempRoot->value;
			index++;
			if (Height(tempRoot->left) >= Height(tempRoot->right))
				tempRoot = tempRoot->left;
			else
				tempRoot = tempRoot->right;
			temp--;
		}
	}
	return result;
}
#endif 

