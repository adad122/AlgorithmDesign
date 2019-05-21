// DS_Set.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <set>
#include <assert.h>

template <typename T>
class DS_Set
{
public:
	DS_Set();
	DS_Set(const DS_Set& that);
	DS_Set& operator = (const DS_Set& that);
	~DS_Set();

	class iterator
	{
		template <typename T>
		friend class DS_Set;

		DS_Set* p; //指向的DS_Set
		int index; //当前表示的DS_Set中的节点

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator + (const int step);
		iterator& operator - (const int step);

		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		T& operator * ();
		T* operator -> ();
	};

	class reverse_iterator
	{
		template <typename T>
		friend class DS_Set;

		DS_Set* p; //指向的DS_Set
		int index; //当前表示的DS_Set中的节点

	public:
		reverse_iterator();
		bool operator != (const reverse_iterator& that);
		reverse_iterator& operator + (int);
		reverse_iterator& operator - (int);

		reverse_iterator& operator ++ ();
		reverse_iterator operator ++ (int);
		reverse_iterator& operator -- ();
		reverse_iterator operator -- (int);
		T& operator * ();
		T* operator -> ();
	};



	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	int size();
	bool empty();

	T& operator [] (const int index);
	iterator find(const T& val) const;


	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
	void clear();

protected:

	void _copy(const DS_Set& that);
};

int main()
{
    return 0;
}

