
#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"

#include <iostream>

template <typename ValueType>
class DoublyLinkedList
{
    // The forward declarations of these classes allows us to establish
    // that they exist, but delay displaying all of the details until
    // later in the file.
    //
    // (This is generally a good style, with the most important details
    // appearing earlier in the class declaration.  That's the same
    // reason why we're implementing the bodies of the member functions
    // outside of the class declaration.)
public:
    class Iterator;
    class ConstIterator;

private:
    struct Node;
    Node* head;
    Node* tail;
    int length; 


public:
	//void print(ostream& out);

    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    static void deleteList(Node* list);
    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);


    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;

    static unsigned int listLength(Node* list);

    // size() returns the number of values in the list.
    unsigned int size() const noexcept;



    // There are two kinds of iterators supported: Iterators and
    // ConstIterators.  They have similar characteristics; they both
    // allow you to see what values are in the list and move back and
    // forth between them.  The difference is that ConstIterators allow
    // you to see the elements but not modify them, while Iterators also
    // support modification of the list (both by modifying the elements
    // directly, and also by inserting or removing values at arbitrary
    // locations).
    //
    // At any given time, an iterator refers to a value in the list.
    // There are also two additional places it can refer: "past start"
    // and "past end", which are the positions directly before the
    // first value and directly after the last one, respectively.
    // Except with respect to those boundaries, they can be moved
    // both forward and backward.
    //
    // Note, too, that the reason we have a ConstIterator class instead
    // of just saying "const Iterator" is because a "const Iterator"
    // is something different: It's an Iterator object that you can't
    // modify (i.e., you can't move it around).  What a ConstIterator
    // holds constant isn't the iterator; it's the list that's protected
    // by it.


    // iterator() creates a new Iterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    Iterator iterator();


    // constIterator() creates a new ConstIterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    ConstIterator constIterator() const;


public:
    // The IteratorBase class is the base class for our two kinds of
    // iterators.  Because there are so many similarities between them,
    // we write those similarities in a base class, then inherit from
    // that base class to specify only the differences.
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
    	Node* nodeptr;
    	bool past_start;
    	bool past_end;
        // You'll want protected member variables and member functions,
        // which will be accessible to the derived classes.

    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;

    private:

    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);
    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev;
        Node* next;
       	Node(ValueType newValue, Node* newPrev = nullptr, Node* newNext = nullptr);
       	Node();
    };


    // You can feel free to add private member variables and member
    // functions here; there's a pretty good chance you'll need some.
};

/*
template <typename ValueType>
void DoublyLinkedList::print(ostream& out)
{
	for (DoublyLinkedList<ValueType> * p = head; p != nullptr; p = p->next)
	{
		out << p->info;
	}
}


ostream& operator << (ostream& out, DoublyLinkedList list)
{
	list.print(out);
	return out;
}
*/

template <typename ValueType>
DoublyLinkedList<ValueType>::Node::Node()
	: value(ValueType()), prev(nullptr), next(nullptr)
{
}

template <typename ValueType>
DoublyLinkedList<ValueType>::Node::Node(ValueType newValue, Node* newPrev, Node* newNext)
	: value(newValue), prev(newPrev), next(newNext)
{
}

template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
{
	length = 0;
	head = nullptr;
	tail = nullptr;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
{
	length = 0;
	if (list.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}	
	else
	{
		head = new Node(list.head->value);
		++length;
		Node* currentNode = head;
		Node* nextNode = list.head->next;
		
		while(nextNode != nullptr)
		{
			currentNode->next = new Node(nextNode->value,currentNode,nullptr);
			++length;
			currentNode = currentNode->next;
			nextNode = nextNode->next;
		}
		tail = currentNode;
	}
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
{
	tail = nullptr;
	head = nullptr;

	Node* tempHead = head;
	Node* tempTail = tail;

	head = list.head;
	tail = list.tail;

	list.head = tempHead;
	list.tail = tempTail;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::deleteList(Node* list)
{
	if (list != nullptr)
	{
		//need length counter
		deleteList(list->next);
		delete list;
	}
}

template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
	length = 0;
	deleteList(head);
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
	if (head != nullptr && tail != nullptr)
	{
		length = 0;
		deleteList(head);
	}

	++length;
	head = new Node(list.head->value);
	Node* currentNode = head;
	Node* nextNode = list.head->next;
	
	while(nextNode != nullptr)
	{
		currentNode->next = new Node(nextNode->value,currentNode,nullptr);
		++length;
		currentNode = currentNode->next;
		nextNode = nextNode->next;
	}
	tail = currentNode;

    return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
	Node* tempHead = head;
	Node* tempTail = tail;

	head = list.head;
	tail = list.tail;

	list.head = tempHead;
	list.tail = tempTail;

    return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{	
	if (head == nullptr && tail == nullptr)
	{
		++length;
		head = new Node(value);
		tail = head;
	}
	else
	{
		++length;
		head = new Node(value, nullptr, head);
		head->next->prev = head;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
	if (head == nullptr && tail == nullptr)
	{
		++length;
		head = new Node(value);
		tail = head;
	}
	else
	{
		++length;
		tail = new Node(value, tail, nullptr);
		tail->prev->next = tail;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
	if (head == nullptr && tail == nullptr)
	{
		throw EmptyException();
	}
	else
	{
		--length;
		Node* firstNode = head;
		head = head->next;
		delete firstNode;
	}

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
	if (head == nullptr && tail == nullptr)
	{
		throw EmptyException();
	}
	else
	{
		--length;
		Node* lastNode = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete lastNode;
	}
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
    // note that this is an awful thing i'm doing here, but i needed
    // something that would make this code compile.  you're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.
    if (head == nullptr && tail == nullptr)
    {
    	throw EmptyException();
    }
    else
    {
    	return head->value;
    }
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (head == nullptr && tail == nullptr)
    {
    	throw EmptyException();
    }
    else
    {
    	return head->value;
    }
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (head == nullptr && tail == nullptr)
    {
    	throw EmptyException();
    }
    else
    {
    	return tail->value;
    }
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (head == nullptr && tail == nullptr)
    {
    	throw EmptyException();
    }
    else
    {
    	return tail->value;
    }
}

template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::listLength(Node* list)
{
	return !list ? 0 : 1 + listLength(list->next);
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return listLength(head);
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    return head == nullptr;
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
{
	nodeptr = list.head;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
	if (isPastEnd())
	{
		throw IteratorException();
	}
	else
	{
		nodeptr = nodeptr->next;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
	if (isPastStart())
	{
		throw IteratorException();
	}
	else
	{
		nodeptr = nodeptr->prev;
	}
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
	return nodeptr == nullptr;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
	return nodeptr == nullptr;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

	if (this->nodeptr == nullptr)
	{
		throw IteratorException();
	}
	else
	{
		return this->nodeptr->value;
	}
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

	if (this->nodeptr == nullptr)
	{
		throw IteratorException();
	}
	else
	{
		return this->nodeptr->value;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
	if (this->nodeptr == nullptr)
	{
		this->nodeptr = new Node(value);
	}
	else
	{
		this->nodeptr = new Node(value, this->nodeptr->prev, this->nodeptr);
		this->nodeptr->prev->next = this->nodeptr;
		this->nodeptr->next->prev = this->nodeptr;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
	if (this->nodeptr == nullptr)
	{
		this->nodeptr = new Node(value);
	}
	else
	{
		this->nodeptr = new Node(value, this->nodeptr, this->nodeptr->next);
		this->nodeptr->next->prev = this->nodeptr;
		this->nodeptr->prev->next = this->nodeptr;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
	if (this->nodeptr == nullptr)
	{
		throw IteratorException();
	}

	else
	{
		if (moveToNextAfterward)
		{
			Node* temp = this->nodeptr;
			this->nodeptr = this->nodeptr->next;
			this->nodeptr->prev = temp->prev;
			temp->prev->next = this->nodeptr;
			delete temp;
		}
		else
		{
			Node* temp = this->nodeptr;
			this->nodeptr = this->nodeptr->prev;
			this->nodeptr->next = temp->next;
			temp->next->prev = this->nodeptr;
			delete temp;
		}
	}	
}



#endif


