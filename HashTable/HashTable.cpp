// HashTable.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "string.h"

#define HASH_SIZE 16

template<typename T>
class ChainingHashTable
{
	template<typename T>
	struct _hashNode
	{
		int key;
		T data;
		_hashNode* next;
	};

public:
	ChainingHashTable();
	~ChainingHashTable();
	void Insert(int key, T data);
	T* Search(int key);
	void Delete(int key);

private:
	_hashNode<T>* m_datas[HASH_SIZE];

	int _hashCode(int key);
	_hashNode<T>* _get(int key);
};

template<typename T>
ChainingHashTable<T>::ChainingHashTable()
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		m_datas[i] = NULL;
	}
}

template<typename T>
ChainingHashTable<T>::~ChainingHashTable()
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		_hashNode<T>* p = m_datas[i];
		_hashNode<T>* q;

		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}
}

template<typename T>
void ChainingHashTable<T>::Insert(int key, T data)
{
	_hashNode<T>* node = _get(key);

	if (node)
	{
		node->data = data;
	}
	else
	{
		_hashNode<T>* node = new _hashNode<T>;
		node->key = key;
		node->data = data;
		node->next = NULL;

		_hashNode<T>* head = m_datas[_hashCode(key)];

		if (head)
		{
			node->next = head->next;
			head->next = node;
		}
		else
		{
			m_datas[_hashCode(key)] = node;
		}
	}
}

template<typename T>
T * ChainingHashTable<T>::Search(int key)
{
	_hashNode<T>* p = _get(key);

	if (p)
	{
		return &p->data;
	}

	return NULL;
}

template<typename T>
void ChainingHashTable<T>::Delete(int key)
{
	_hashNode<T>* p = m_datas[_hashCode(key)];
	if (p->key == key)
	{
		m_datas[_hashCode(key)] = p->next;
		delete p;
		return;
	}

	_hashNode<T>* q = p->next;

	while (q)
	{
		if (q->key == key)
		{
			p->next = q->next;
			delete q;
			return;
		}
		p = q;
		q = q -> next;
	}
}

template<typename T>
int ChainingHashTable<T>::_hashCode(int key)
{
	static char buf[8] = {};
	unsigned int hash = 0;
	sprintf_s(buf, "%d", key);
	for (const char* c = buf; *c; ++c)
	{
		hash = hash * 33 + *c;
	}
	return hash%HASH_SIZE;
}

template<typename T>
typename ChainingHashTable<T>::_hashNode<T> * ChainingHashTable<T>::_get(int key)
{
	_hashNode<T> * p = m_datas[_hashCode(key)];

	while (p)
	{
		if (key == p->key)
		{
			break;
		}
		else
			p = p->next;
	}

	return p;
}

//496 896 1 337 353 387 184 26 126 91 155 171 12 28 108 140 31 111


template<typename T>
class OpenAddressingHashTable
{
	template<typename T>
	struct _hashNode
	{
		int key;
		T data;
	};

public:
	OpenAddressingHashTable();
	~OpenAddressingHashTable();
	void Insert(int key, T data);
	T* Search(int key);
	void Delete(int key);

private:
	_hashNode<T>** m_datas;
	int m_capacity;

	int _hashCode(int key);
	int _doubleHashCode(int key);
	void _expand();
};

template<typename T>
OpenAddressingHashTable<T>::OpenAddressingHashTable()
{
	m_capacity = HASH_SIZE;
	m_datas = new _hashNode<T>*[m_capacity];

	for (int i = 0; i < m_capacity; ++i)
	{
		m_datas[i] = NULL;
	}
}

template<typename T>
OpenAddressingHashTable<T>::~OpenAddressingHashTable()
{
	for (int i = 0; i < m_capacity; ++i)
	{
		if (m_datas[i] != NULL)
			delete m_datas[i];
	}
	delete m_datas;
}

template<typename T>
void OpenAddressingHashTable<T>::Insert(int key, T data)
{
	int index = _hashCode(key);

	_hashNode<T>* pos = m_datas[index];

	if (pos == NULL)
	{
		_hashNode<T>* node = new _hashNode<T>;
		node->key = key;
		node->data = data;
		m_datas[index] = node;
	}
	else
	{
		if (pos->key == key)
		{
			pos->data = data;
			return;
		}

		int doubleHash = _doubleHashCode(key);
		bool inserted = false;

		while (!inserted)
		{
			index += doubleHash;
			if (index >= m_capacity)
			{
				_expand();
			}

			pos = m_datas[index];
			if (pos == NULL)
			{
				_hashNode<T>* node = new _hashNode<T>;
				node->key = key;
				node->data = data;
				m_datas[index] = node;
				inserted = true;
			}
			else
			{
				if (pos->key == key)
				{
					pos->data = data;
					inserted = true;
				}
				else
				{
					index += doubleHash;
				}
			}
		}
	}
}

template<typename T>
T * OpenAddressingHashTable<T>::Search(int key)
{
	int index = _hashCode(key);
	int doubleHash = _doubleHashCode(key);

	while (index < m_capacity)
	{
		_hashNode<T>* pos = m_datas[index];
		if (pos != NULL && pos->key == key)
		{
			return &pos->data;
		}

		index += doubleHash;
	}

	return NULL;
}

template<typename T>
void OpenAddressingHashTable<T>::Delete(int key)
{
	int index = _hashCode(key);
	int doubleHash = _doubleHashCode(key);

	while (index < m_capacity)
	{
		_hashNode<T>* pos = m_datas[index];
		if (pos != NULL && pos->key == key)
		{
			delete pos;
			m_datas[index] = NULL;
			return;
		}
		
		index += doubleHash;
	}
}

template<typename T>
int OpenAddressingHashTable<T>::_hashCode(int key)
{
	static char buf[8] = {};
	unsigned int hash = 0;
	sprintf_s(buf, "%d", key);
	for (const char* c = buf; *c; ++c)
	{
		hash = hash * 33 + *c;
	}
	return hash%HASH_SIZE;
}

template<typename T>
int OpenAddressingHashTable<T>::_doubleHashCode(int key)
{
	static char buf[8] = {};
	unsigned int hash = 0;
	sprintf_s(buf, "%d", key);
	for (const char* c = buf; *c; ++c)
	{
		hash = hash * 33 + *c;
	}
	return 1 + hash%(HASH_SIZE - 2);
}

template<typename T>
void OpenAddressingHashTable<T>::_expand()
{
	_hashNode<T>** newDatas = new _hashNode<T>*[m_capacity * 2];
	memcpy_s(newDatas, sizeof(_hashNode<T>) * m_capacity * 2, m_datas, sizeof(_hashNode<T>) * m_capacity);

	for (int i = m_capacity; i < m_capacity*2; ++i)
	{
		newDatas[i] = NULL;
	}

	m_capacity *= 2;
	delete m_datas;

	m_datas = newDatas;
}

int main()
{
	int datas[18] = { 496, 896, 1, 337, 353, 387, 184, 26, 126, 91, 155, 171, 12, 28, 108, 140, 31, 111 };
	ChainingHashTable<int> hashTable1;
	OpenAddressingHashTable<int> hashTable2;

	for (int i = 0; i < 18; ++i)
	{
		hashTable1.Insert(datas[i], datas[i]);
		hashTable2.Insert(datas[i], datas[i]);
	}

	if (hashTable1.Search(171))
	{
		printf("hashTable1 Search 171 success\n");
	}
	else
	{
		printf("hashTable1 Search 171 failed\n");
	}

	if (hashTable2.Search(171))
	{
		printf("hashTable2 Search 171 success\n");
	}
	else
	{
		printf("hashTable2 Search 171 failed\n");
	}

	hashTable1.Delete(171);
	hashTable2.Delete(171);

	if (hashTable1.Search(171))
	{
		printf("hashTable1 Search 171 success\n");
	}
	else
	{
		printf("hashTable1 Search 171 failed\n");
	}

	if (hashTable2.Search(171))
	{
		printf("hashTable2 Search 171 success\n");
	}
	else
	{
		printf("hashTable2 Search 171 failed\n");
	}

    return 0;
}
