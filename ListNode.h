#ifndef LISTNODE_H
#define LISTNODE_H

template <class NODETYPE> class List;

template <class NODETYPE>
class ListNode
{
	friend class List<NODETYPE>;
public:
	ListNode(const NODETYPE&);
private:
	NODETYPE data;
	ListNode<NODETYPE>* nextPtr;
};

template <class NODETYPE>
inline ListNode<NODETYPE>::ListNode(const NODETYPE& value)
	:data(value), nextPtr(nullptr)
{   }

#endif // !LISTNODE_H
