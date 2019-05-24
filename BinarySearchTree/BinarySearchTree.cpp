// BinarySearchTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


struct _Node
{
	_Node* parent;
	_Node* right;
	_Node* left;
	int data;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	int GetHeight();
	int GetLength();
	void Insert(int data);
	void Erase(_Node* p);
	int* Search(int data);
	void Delete(int data);
	int Maximum();
	int Minimum();
	void Output();
	int Predecessor(int data);
	int Successor(int data);

private:
	_Node* CreateNode(int data);
	_Node* Cut(_Node* p);
	void _erase(_Node* p);
	int _size(_Node* p);
	int _height(_Node* p);
	void _insert(_Node * p, int data);
	_Node* _search(_Node * p, int data);
	int _maximum(_Node * p);
	int _minimum(_Node * p);
	void InorderWalk(_Node* p);
	void _transplant(_Node * p, _Node * q);

	_Node* root;
};

BinarySearchTree::BinarySearchTree()
{
	_Node* root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
	Erase(root);
}

int BinarySearchTree::_height(_Node* p)
{
	if (p)
	{
		int left = _height(p->left);
		int right = _height(p->right);

		return (left > right ? left : right) + 1;
	}

	return 0;
}

int BinarySearchTree::GetHeight()
{
	return _height(root);
}

int BinarySearchTree::_size(_Node* p)
{
	if (p)
		return _size(p->left) + _size(p->right) + 1;

	return 0;
}

int BinarySearchTree::GetLength()
{
	return _size(root);
}

_Node * BinarySearchTree::CreateNode(int data)
{
	_Node * node = new _Node;
	node->parent = node->left = node->right = NULL;
	node->data = data;

	return node;
}

_Node * BinarySearchTree::Cut(_Node * p)
{
	if (p == NULL)
		return NULL;

	if (p->parent != NULL)
	{
		_Node * parent = p->parent;

		if (parent->left == p)
			parent->left = NULL;
		else if (parent->right == p)
			parent->right = NULL;
	}

	return p;
}

void BinarySearchTree::Insert(int data)
{
	/*if (root == NULL)
	{
		root = CreateNode(data);
		return;
	}

	_insert(root, data);*/

	_Node* parent = NULL;

	_Node* p = root;

	while (p)
	{
		parent = p;

		if (data > p->data)
			p = p->right;
		else if(data < p->data)
			p = p->left;
		else
			return;
	}

	_Node* node = CreateNode(data);

	if (parent == NULL)
	{
		root = node;
		return;
	}

	node->parent = parent;

	if (data > parent->data)
		parent->right = node;
	else
		parent->left = node;
	
}

void BinarySearchTree::_insert(_Node * p, int data)
{
	if (p == NULL || p->data == data)
		return;

	_Node* node = NULL;

	if (p->left == NULL && p->data > data)
	{
		node = CreateNode(data);
		node->parent = p;
		p->left = node;
	}
	else if (p->right == NULL && p->data < data)
	{
		node = CreateNode(data);
		node->parent = p;
		p->right = node;
	}

	if(p->data > data)
		_insert(p->left, data);
	else if(p->data < data)
		_insert(p->right, data);
}

_Node * BinarySearchTree::_search(_Node * p, int data)
{
	//if (p == NULL || p->data == data)
	//	return p;

	//if (p->data > data)
	//	return _search(p->left, data);

	//return _search(p->right, data);

	_Node * q = p;
	while (q && q->data != data)
	{
		if (q->data > data)
			q = q->left;
		else
			q = q->right;
	}

	return q;
}

void BinarySearchTree::Erase(_Node* p)
{
	if (p == NULL)
		return;

	_erase(p->left);
	_erase(p->right);
	delete p;
}

int * BinarySearchTree::Search(int data)
{
	_Node * node = _search(root, data);

	if (node != NULL)
		return &node->data;

	return NULL;
}

void BinarySearchTree::Delete(int data)
{
	_Node * node = _search(root, data);

	if (node != NULL)
	{
		_Node* parent = node->parent;

		if(node->right != NULL && node->left != NULL)
		{
			_Node* p = node->right;

			while (p->left)
			{
				p = p->left;
			}

			if (p->parent != node)
			{
				_transplant(p, p->right);
				p->right = node->right;
				node->right->parent = p;
			}
			
			_transplant(node, p);
			p->left = node->left;
			node->left->parent = p;

		}
		else if(node->right != NULL || node->left != NULL)
		{
			_Node* p = node->left ? node->left : node->right;
			_transplant(node, p);
		}

		Cut(node);
		delete node;
	}
}

void BinarySearchTree::_transplant(_Node * p, _Node * q)
{
	if (p == NULL)
		return;

	if (p->parent == NULL)
		root = q;
	else if (p == p->parent->left)
		p->parent->left = q;
	else
		p->parent->right = q;

	if (q != NULL)
		q->parent = p->parent;
}

int BinarySearchTree::Maximum()
{
	//return _maximum(root);

	_Node* p = root;
	while (p->right)
	{
		p = p->right;
	}

	return p->data;
}

int BinarySearchTree::Minimum()
{
	//return _minimum(root);

	_Node* p = root;
	while (p->left)
	{
		p = p->left;
	}

	return p->data;
}

void BinarySearchTree::Output()
{
	printf("\n");
	InorderWalk(root);
	printf("\n");
}

int BinarySearchTree::Predecessor(int data)
{
	_Node* node = _search(root, data);

	if (node == NULL)
	{
		return Maximum();
	}

	if (node->left != NULL)
		return _maximum(node->left);

	_Node* p = node->parent;

	while (p && node == p->left)
	{
		node = p;
		p = p->parent;
	}

	return p ? p->data : Minimum();
}

int BinarySearchTree::Successor(int data)
{
	_Node* node = _search(root, data);

	if (node == NULL)
	{
		return Minimum();
	}

	if (node->right != NULL)
		return _minimum(node->right);

	_Node* p = node->parent;

	while (p && node == p->right)
	{
		node = p;
		p = p->parent;
	}

	return p ? p->data : Minimum();
}

void BinarySearchTree::InorderWalk(_Node * p)
{
	if (p)
	{
		InorderWalk(p->left);
		printf("%d ", p->data);
		InorderWalk(p->right);
	}
}


int BinarySearchTree::_maximum(_Node * p)
{
	int max = p->data;

	if (p->right)
		max = _maximum(p->right);

	return max;
}

int BinarySearchTree::_minimum(_Node * p)
{
	int min = p->data;

	if (p->left)
		min = _minimum(p->left);

	return min;
}


void BinarySearchTree::_erase(_Node* p)
{
	if (p == NULL)
		return;

	_erase(p->left);
	_erase(p->right);
	delete p;
}

// 15 6 18 3 7 17 20 2 4 13 9
//      15
//    6   18
//  3  7 17  20
//2  4  13
//     9

//      15
//    6   18
//  3  7    20
//2  4  13
//     9

//         18
//       6   20
//    3    7    
//  2  4    13
//         9

//         18
//       6   20
//    3    13    
//  2  4  9

int main()
{
	int datas[11] = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
	BinarySearchTree bst;
	for (int i = 0; i < 11; ++i)
	{
		bst.Insert(datas[i]);
	}

	int* result_17 = bst.Search(17);

	if (result_17 != NULL)
	{
		printf("17 exist\n");
	}
	else
	{
		printf("17 not exist\n");
	}

	int* result_100 = bst.Search(100);

	if (result_100 != NULL)
	{
		printf("100 exist\n");
	}
	else
	{
		printf("100 not exist\n");
	}

	printf("Maximum = %d\n", bst.Maximum());
	printf("Minimum = %d\n", bst.Minimum());
	bst.Output();
	printf("Predecessor of 9 = %d\n", bst.Predecessor(9));
	printf("Successor of 9 = %d\n", bst.Successor(9));

	bst.Delete(17);
	bst.Output();
	result_17 = bst.Search(17);

	if (result_17 != NULL)
	{
		printf("17 exist\n");
	}
	else
	{
		printf("17 not exist\n");
	}

	bst.Delete(15);
	bst.Output();
	int* result_15= bst.Search(15);

	if (result_15 != NULL)
	{
		printf("15 exist\n");
	}
	else
	{
		printf("15 not exist\n");
	}

	bst.Delete(7);
	bst.Output();

    return 0;
}

