// HashSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include <iostream>
#include <algorithm>


template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet() noexcept;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    struct Node
    {
        ElementType element;
        Node* next;

        Node(ElementType newElement, Node* newNext = nullptr);
    };

    Node** table;
    unsigned int sz;
    unsigned int capacity;


private:
    void printAll(Node** table);
    void destroyAll(Node** table);
    Node** copyAll(Node** table, int capacity);

};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}

template <typename ElementType>
HashSet<ElementType>::Node::Node(ElementType newElement, Node* newNext)
    : element(newElement), next(newNext)
{
}

template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    //std::cout << "DEFAULT_CAPACITY" << std::endl;

    capacity = DEFAULT_CAPACITY;
    sz = 0;
    table = new Node* [capacity];

    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }

    //printAll(table);
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    destroyAll(table);
    /*
    Node* temp;
    Node* curr;
    for (int i = 0; i < capacity; ++i)
    {
        if (table[i] != nullptr)
        {
            curr = table[i];
            while (curr != nullptr)
            {
                temp = curr;
                delete temp;
                curr = curr->next;
            }
        }
        table[i] = nullptr;
    }
    delete[] table;
    */
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    //std::cout << "COPY CONSTRUCTOR" << std::endl;

    table = copyAll(s.table, s.capacity);
    sz = s.sz;
    capacity = s.capacity;
    //printAll(table);  
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{

    capacity = DEFAULT_CAPACITY;
    sz = 0;
    table = new Node* [capacity];

    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }

    std::swap(table, s.table);
    std::swap(capacity, s.capacity);
    std::swap(sz, s.sz);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        Node** temp = copyAll(s.table, s.capacity);
        destroyAll(table);
        table = temp;
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    std::swap(table, s.table);
    std::swap(capacity, s.capacity);
    std::swap(sz, s.sz);
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    //std::cout << "ADD" << std::endl;

    if (sz/capacity > 0.8)
    {
        Node* curr;

        int newCapacity = capacity * 2;
        Node** newTable = new Node* [newCapacity];
        for (int i = 0; i < capacity; ++i)
        {
            curr = table[i];
            if (curr != nullptr)
            {
                while(curr != nullptr)
                {
                    ElementType key = curr->element;
                    unsigned int j = hashFunction(key) % newCapacity;
                    newTable[j] = new Node(key, newTable[j]);
                }
            }
        }
    }

    unsigned int i = hashFunction(element) % capacity;

    if (table[i] == nullptr)
    {
        table[i] = new Node(element);
        ++sz;
    }
    else
    {
        Node* temp = table[i];
        while (temp->next != nullptr)
        {
            if (temp->element == element)
            {
                return;
            }
            else
            {
                temp = temp->next;
            }
        }
        temp->next = new Node(element, nullptr);
        ++sz;
    }
    //printAll(table);
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    unsigned int i = hashFunction(element) % capacity;
    if (table[i] != nullptr)
    {
        while (table[i] != nullptr)
        {
            if (table[i]->element == element)
            {
                return true;
            }
            else
            {
                table[i] = table[i]->next;
            }
        }  
    } 
    return false;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    //std::cout << "size: " << sz << std::endl;
    return sz;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    if (index < 0 || index >= capacity)
    {
        return 0;
    }
    else
    {
        int length = 0;
        Node* curr = table[index];
        while (curr != nullptr)
        {
            ++length;
            curr = curr->next;
        }
        return length;
    }
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if (index < 0 || index >= capacity)
    {
        return 0;
    }
    else
    {
        Node* curr = table[index];
        while (curr != nullptr)
        {
            if (curr->element == element)
            {
                return true;
            }
            else
            {
                curr = curr->next;
            }
        }
    return false;
    }
}

template <typename ElementType>
void HashSet<ElementType>::printAll(Node** table)
{
    for (int i = 0; i < capacity; ++i)
    {
        std::cout << i << ": ";
        Node* temp = table[i];
        while (temp != nullptr)
        {
            std::cout << temp->element << " -> ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename ElementType>
void HashSet<ElementType>::destroyAll(Node** table)
{
    Node* temp;
    Node* curr;
    for (int i = 0; i < capacity; ++i)
    {
        curr = table[i];

        while (curr != nullptr)
        {
            temp = curr;
            delete temp;
            curr = curr->next;
        }
        table[i] = nullptr;
    }
    //delete[] table;
}

template <typename ElementType>
typename HashSet<ElementType>::Node** HashSet<ElementType>::copyAll(
    Node** table, int capacity)
{
    Node** newHash = new Node* [capacity];

    for (int i = 0; i < capacity; ++i)
    {
        //std::cout << "INDEX: " << i << std::endl;
        Node* curr = table[i];
        Node* newList = newHash[i];

        if (curr != nullptr)

            while (curr != nullptr)
            {
                newList = new Node{curr->element, newList};
                //std::cout << curr->element << std::endl;
                curr = curr->next;
            }
        else
        { 
            //std::cout << 0 << std::endl;
            newList = nullptr;
        }
    }
    return newHash;
}


#endif // HASHSET_HPP

