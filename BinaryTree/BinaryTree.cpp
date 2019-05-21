// BinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct _Node
{
	_Node* parent;
	_Node* right;
	_Node* left;
	int data;
};

class BinaryTree
{
public:
	static int GetHeight(_Node* p);
	static int GetLength(_Node* p);
	static void InorderWalk(_Node* p);
	static void PreorderWalk(_Node* p);
	static void PostorderWalk(_Node* p);
	static void LevelWalk(_Node* p);
	static _Node* CreateNode(int data);
	static _Node* Cut(_Node* p);
	static _Node* Copy(_Node* p);
	static _Node* Insert(_Node* p, _Node* c, bool Left = true);
	static void Erase(_Node* p);
	static bool Equal(_Node* p, _Node* q);

private:
	static _Node* _copy(_Node* p, _Node* q);
	static void _erase(_Node* p);
};

int BinaryTree::GetHeight(_Node * p)
{
	if (p)
	{
		int left = GetHeight(p->left);
		int right = GetHeight(p->right);

		return (left > right ? left : right) + 1;
	}

	return 0;
}

int BinaryTree::GetLength(_Node * p)
{
	if (p)
		return GetLength(p->left) + GetLength(p->right) + 1;

	return 0;
}

void BinaryTree::InorderWalk(_Node * p)
{
	if (p)
	{
		InorderWalk(p->left);
		printf("%d ", p->data);
		InorderWalk(p->right);
	}
}

void BinaryTree::PreorderWalk(_Node * p)
{
	if (p)
	{
		printf("%d ", p->data);
		PreorderWalk(p->left);
		PreorderWalk(p->right);
	}
}

void BinaryTree::PostorderWalk(_Node * p)
{
	if (p)
	{
		PostorderWalk(p->left);
		PostorderWalk(p->right);
		printf("%d ", p->data);
	}
}

void BinaryTree::LevelWalk(_Node * p)
{
}

_Node * BinaryTree::CreateNode(int data)
{
	_Node * node = new _Node;
	node->parent = node->left = node->right = NULL;
	node->data = data;

	return node;
}

_Node * BinaryTree::Cut(_Node * p)
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

_Node * BinaryTree::Copy(_Node * p)
{
	if (p == NULL)
		return NULL;

	_Node* node = CreateNode(p->data);
	node->left = _copy(p->left, node);
	node->right = _copy(p->right, node);

	return node;
}

_Node * BinaryTree::Insert(_Node * p, _Node * c, bool Left)
{
	Cut(c);
	if(Left)
	{
		_Node * ol = Cut(p->left);
		p->left = c;
		c->parent = p;
		return ol;
	}
	else
	{
		_Node * or = Cut(p->right);
		p->right = c;
		c->parent = p;
		return or;
	}
}

void BinaryTree::Erase(_Node * p)
{
	if (p == NULL)
		return;

	Cut(p);
	_erase(p->left);
	_erase(p->right);
	delete p;
}

bool BinaryTree::Equal(_Node * p, _Node * q)
{
	if (p == NULL && q == NULL)
		return true;

	if (p != NULL && q != NULL)
	{
		bool equal = p->data == q->data;
		equal = Equal(p->left, p->left) && equal;
		equal = Equal(p->right, p->right) && equal;
		return equal;
	}

	return false;
}

_Node* BinaryTree::_copy(_Node* p, _Node* q)
{
	if (p == NULL)
		return NULL;

	_Node* node = CreateNode(p->data);
	node->left = _copy(p->left, node);
	node->right = _copy(p->right, node);
	node->parent = q;

	return node;
}

void BinaryTree::_erase(_Node* p)
{
	if (p == NULL)
		return;

	_erase(p->left);
	_erase(p->right);
	delete p;
}


//         6
//    5         7
//  2   3           8
//1

//Pre  6 5 2 1 3 7 8
//In   1 2 5 3 6 7 8
//Post 1 2 3 5 8 7 6

int main()
{
	_Node* node_6 = BinaryTree::CreateNode(6);
	_Node* node_5 = BinaryTree::CreateNode(5);
	_Node* node_7 = BinaryTree::CreateNode(7);
	_Node* node_2 = BinaryTree::CreateNode(2);
	_Node* node_3 = BinaryTree::CreateNode(3);
	_Node* node_8 = BinaryTree::CreateNode(8);
	_Node* node_1 = BinaryTree::CreateNode(1);

	BinaryTree::Insert(node_2, node_1);
	BinaryTree::Insert(node_5, node_2);
	BinaryTree::Insert(node_5, node_3, false);

	BinaryTree::Insert(node_7, node_8, false);

	BinaryTree::Insert(node_6, node_5);
	BinaryTree::Insert(node_6, node_7, false);

	printf("Tree Height: %d\n", BinaryTree::GetHeight(node_6));
	printf("Tree Size: %d\n", BinaryTree::GetLength(node_6));

	printf("\nPre Order\n");
	BinaryTree::PreorderWalk(node_6);

	printf("\nIn Order\n");
	BinaryTree::InorderWalk(node_6);

	printf("\nPost Order\n");
	BinaryTree::PostorderWalk(node_6);

	_Node* node_6_copy = BinaryTree::Copy(node_6);

	printf("\nTree node_6 is equals to node_6_copy: %s\n", BinaryTree::Equal(node_6, node_6_copy) ? "True" : "False");

	BinaryTree::Erase(node_6);
	BinaryTree::Erase(node_6_copy);
    return 0;
}

