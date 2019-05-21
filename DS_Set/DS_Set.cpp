// DS_Set.cpp : �������̨Ӧ�ó������ڵ㡣
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

		DS_Set* p; //ָ���DS_Set
		int index; //��ǰ��ʾ��DS_Set�еĽڵ�

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

		DS_Set* p; //ָ���DS_Set
		int index; //��ǰ��ʾ��DS_Set�еĽڵ�

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

