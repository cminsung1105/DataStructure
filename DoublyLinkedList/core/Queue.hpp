#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DoublyLinkedList.hpp"



template <typename ValueType>
class Queue : private DoublyLinkedList<ValueType>
{
public:
    // Note that the constructors, destructors, and assignment
    // operators are not declared here, because the defaults
    // will do precisely what we want them to, in this case:
    // Call the versions from the base class.  The only reason
    // you would need to add those declarations is if you
    // added something to this class template that required
    // initialization, cleanup, etc., which is unlikely.


    // enqueue() adds the given value to the back of the queue, after
    // all of the ones that are already stored within.
    void enqueue(const ValueType& value);

    // dequeue() removes the front value from the queue, if there is
    // one.  If the queue is empty, it throws an EmptyException instead.
    void dequeue();

    // front() returns the front value in the queue, if there is one.
    // If the queue is empty, it throws an EmptyException instead.
    const ValueType& front() const;


    // These members of DoublyLinkedList are being made into public
    // members of Queue.  Given a Queue object, you'd now be able to
    // call the isEmpty(), size(), or constIterator() member functions,
    // as well as say something like "Queue<int>::ConstIterator".
    //
    // Note that we don't need to implement these separately; the
    // implemenations from DoublyLinkedList are now a part of Queue.
    // All we're doing is making them public.

    using DoublyLinkedList<ValueType>::isEmpty;
    using DoublyLinkedList<ValueType>::size;

    using DoublyLinkedList<ValueType>::constIterator;
    using ConstIterator = typename DoublyLinkedList<ValueType>::ConstIterator;
};



template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value)
{
    // Note that it's not always necessary (or even preferable) to say "this->"
    // when you access an inherited member.  addToEnd() is part of the base
    // class (DoublyLinkedList), so you would expect to be able to say this:
    //
    //     addToEnd(value);
    //
    // However, in the presence of templates, things can get more complicated.
    // For example, there are stricter rules about how names are looked up.
    // One of those rules is that names in "dependent types" (i.e., types
    // that depend on what ValueType is, in the context of this function)
    // are not looked up by the compiler.  The reason why is a long story,
    // but revolves roughly around the idea that different instantiations of
    // the same template can have wildly different details sometimes.  So
    // the compiler will refuse to find addToEnd(), though it can find it if
    // give it a little more help with where to look.  "this->" is our way of
    // doing that; we're saying "You can expect to find addToEnd as a member
    // function of the current object."

    this->addToEnd(value);
}


template <typename ValueType>
void Queue<ValueType>::dequeue()
{
    this->removeFromStart();
}


template <typename ValueType>
const ValueType& Queue<ValueType>::front() const
{
    return this->first();
}



#endif

