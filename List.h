#ifndef LIST_H
#define LIST_H

#include <cassert>

#include <iostream>

#include <stdexcept>

#include "ListNode.h"

template <class NODETYPE>
class List
{
	template <typename NODETYPE>
	friend std::ostream& operator << (std::ostream&, const List<NODETYPE>&);
public:
	List();
	List(const std::initializer_list<NODETYPE>&);
	~List();

	void pushFront(const NODETYPE&);
	void pushBack(const NODETYPE&);
	void popFront();
	void popBack();
	void insert(const NODETYPE&, size_t);
	void erase(size_t);
	bool isEmpty() const;
	size_t size() const;
	NODETYPE& operator [] (size_t);
	const NODETYPE& operator [] (size_t) const;
private:
	size_t sizeOfList;
	ListNode<NODETYPE>* firstPtr, * lastPtr;

	ListNode<NODETYPE>* getNewNode(const NODETYPE&);
	ListNode<NODETYPE>* getPtrAtIndex(size_t) const;
};

template<class NODETYPE>
inline List<NODETYPE>::List()
	:sizeOfList(0ll), firstPtr(nullptr), lastPtr(nullptr)
{   }

template <class NODETYPE>
inline List<NODETYPE>::List(const std::initializer_list<NODETYPE>& list) : List()
{
	for (const NODETYPE& value : list)
	{
		pushBack(value);
	}
}

template <class NODETYPE>
inline List<NODETYPE>::~List()
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr, * holdPtr;

		while (currentPtr != nullptr)
		{
			holdPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete holdPtr;
		}
	}
}

template <class NODETYPE>
inline void List<NODETYPE>::pushFront(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = getNewNode(value);

	if (isEmpty())
	{
		firstPtr = lastPtr = newPtr;
	}
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}

	++sizeOfList;
}

template <class NODETYPE>
inline void List<NODETYPE>::pushBack(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = getNewNode(value);

	if (isEmpty())
	{
		firstPtr = lastPtr = newPtr;
	}
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

	++sizeOfList;
}

template <class NODETYPE>
inline void List<NODETYPE>::popFront()
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* holdPtr = firstPtr;

		if (firstPtr == lastPtr)
		{
			firstPtr = lastPtr = nullptr;
		}
		else
		{
			firstPtr = firstPtr->nextPtr;
		}

		delete holdPtr;
		--sizeOfList;
	}
}

template <class NODETYPE>
inline void List<NODETYPE>::popBack()
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* holdPtr = lastPtr;

		if (firstPtr == lastPtr)
		{
			firstPtr = lastPtr = nullptr;
		}
		else
		{
			ListNode<NODETYPE>* currentPtr = firstPtr;

			while (currentPtr->nextPtr != lastPtr)
			{
				currentPtr = currentPtr->nextPtr;
			}

			lastPtr = currentPtr;
			currentPtr->nextPtr = nullptr;
		}

		delete holdPtr;
		--sizeOfList;
	}
}

template <class NODETYPE>
inline void List<NODETYPE>::insert(const NODETYPE& value, size_t index)
{
	if (index == 0)
	{
		pushFront(value);
	}
	else
	{
		ListNode<NODETYPE>* newPtr = getNewNode(value);

		ListNode<NODETYPE>* currentPtr = getPtrAtIndex(index - 1);

		newPtr->nextPtr = currentPtr->nextPtr;
		currentPtr->nextPtr = newPtr;

		++sizeOfList;
	}
}

template <class NODETYPE>
inline void List<NODETYPE>::erase(size_t index)
{
	if (index == 0)
	{
		popFront();
	}
	else if (index == sizeOfList - 1)
	{
		popBack();
	}
	else if (index == sizeOfList)
	{
		throw std::out_of_range("index out of range");
	}
	else
	{
		ListNode<NODETYPE>* currentPtr = getPtrAtIndex(index - 1), * holdPtr = currentPtr->nextPtr;

		currentPtr->nextPtr = holdPtr->nextPtr;
		delete holdPtr;

		--sizeOfList;
	}
}

template <class NODETYPE>
inline bool List<NODETYPE>::isEmpty() const { return firstPtr == nullptr; }

template <class NODETYPE>
inline size_t List<NODETYPE>::size() const { return sizeOfList; }

template <class NODETYPE>
NODETYPE& List<NODETYPE>::operator[](size_t index)
{
	ListNode<NODETYPE>* currentPtr = getPtrAtIndex(index);

	return currentPtr->data;
}

template <class NODETYPE>
const NODETYPE& List<NODETYPE>::operator[](size_t index) const
{
	ListNode<NODETYPE>* currentPtr = getPtrAtIndex(index);

	return currentPtr->data;
}

template <class NODETYPE>
inline ListNode<NODETYPE>* List<NODETYPE>::getNewNode(const NODETYPE& value)
{
	ListNode<NODETYPE>* ptr = new ListNode<NODETYPE>(value);

	assert(ptr != nullptr);

	return ptr;
}

template<class NODETYPE>
inline ListNode<NODETYPE>* List<NODETYPE>::getPtrAtIndex(size_t index) const
{
	if (index >= sizeOfList)
	{
		throw std::out_of_range("index out of range");
	}

	ListNode<NODETYPE>* currentPtr = firstPtr;

	for (size_t iter = 0; iter < index; ++iter)
	{
		currentPtr = currentPtr->nextPtr;
	}

	return currentPtr;
}

template<typename NODETYPE>
inline std::ostream& operator << (std::ostream& output, const List<NODETYPE>& list)
{
	for (size_t iter = 0; iter < list.size(); ++iter)
	{
		output << list[iter] << ' ';
	}

	return output;
}

#endif // !LIST_H
