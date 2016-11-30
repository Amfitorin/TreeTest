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
	static void SetWidh(int& space, Tree& root);
	static int GetWidth(int& width, Tree& root);
	static int Height(Tree* root);
	void MaxPath( Tree* root, TreePath& maxPath );
	Tree<T>* GetMaxPathRoot();

private:
	Tree* left;
	Tree* right;
	T value;
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
		int rootHight = Height(root->left) + Height(root->right);
		if (!maxPath.root || maxPath.height < rootHight)
		{
			maxPath.root = root;
			maxPath.height = rootHight;
		}
		MaxPath(root->left, maxPath);
		MaxPath(root -> right, maxPath);
	}
}
template<class T>
inline Tree<T>* Tree<T>::GetMaxPathRoot()
{
	path.root = this;
	path.height = Height(this->left) + Height(this->right);
	MaxPath(this, path);
	int s = 5;
	return path.root;
}
#endif 

