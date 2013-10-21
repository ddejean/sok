/*
 * RawLinkedList.h
 *
 * Copyright (C) 2012-2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Raw linked list implementation of List interface.
 */

#ifndef _RAWLINKEDLIST_H_
#define _RAWLINKEDLIST_H_

#include "List.h"


/**
 * A container element of the list.
 * value: the payload hold by this container.
 * next: the following container.
 */
template <typename V>
class Node
{
public:
    const V value;
    Node<V> *next;
    Node(const V &v, Node<V> *n) : value(v), next(n) {};
};


/**
 * Node factory interface.
 */
template <typename T>
class NodeFactory
{
public:
   /**
    * Creates an instance of a Node for the RawLinkedList.
    */
   virtual Node<T> *makeNode(const T &t, Node<T> *n) = 0;
   virtual ~NodeFactory() { /* Nothing to do here */ };
};


/**
 * Base implementation of LinkedList. The list relies on Node elements linked by
 * pointers. As a list can be used in multiple memory context/situation the
 * "raw" implementation expects a NodeFactory to allocate nodes from the right
 * memory pool.
 */
template <typename T>
class RawLinkedList : public List<T>
{
protected:
    /**
     * Raw list constructor. Expects a NodeFactory to be able to use nodes from
     * various memory pools depending on extended implementations choices.
     * @nodeFactory a factory that provides nodes to the list.
     *
     * @note protected to force a extended implementation.
     */
    RawLinkedList(NodeFactory<T> *nodeFactory);

    /* Node allocation facility */
    NodeFactory<T> *mNodeFactory;

    /* First element of the list */
    Node<T> *mHead;
    /* Last element of the list */
    Node<T> *mLast;

public:
    virtual ~RawLinkedList();

    /*
     * List interface implementation.
     */
    void clear(void);
    void append(const T &t);
    void prepend(const T &t);
    void insert(const T &t, unsigned i);
    void removeAt(unsigned i);
    const T& at(unsigned i);
    bool isHealthy(void);
};

template <typename T>
RawLinkedList<T>::RawLinkedList(NodeFactory<T> *nodeFactory)
{
    assert(nodeFactory != NULL);
    mNodeFactory = nodeFactory;
}

template <typename T>
RawLinkedList<T>::~RawLinkedList(void)
{
    clear();
    delete mNodeFactory;
}

template <typename T>
void RawLinkedList<T>::clear(void)
{
    while (mHead != NULL) {
        Node<T> *cur = mHead;
        mHead = mHead->next;
        delete cur;
    }
    mHead = mLast = NULL;
    List<T>::mCount = 0;
}

template <typename T>
void RawLinkedList<T>::append(const T &t)
{
    if (mHead == NULL && mLast == NULL) {
        mHead = mLast = mNodeFactory->makeNode(t, NULL);
    } else {
        mLast->next = mNodeFactory->makeNode(t, NULL);
        mLast = mLast->next;
    }
    List<T>::mCount++;
}

template <typename T>
void RawLinkedList<T>::prepend(const T &t)
{
    if (mHead == NULL && mLast == NULL) {
        mHead = mLast = mNodeFactory->makeNode(t, NULL);
    } else {
        mHead = mNodeFactory->makeNode(t, mHead);
    }
    List<T>::mCount++;
}

template <typename T>
void RawLinkedList<T>::insert(const T &t, unsigned i)
{
    if (i == 0) {               /* It's the prepend use-case. */
        prepend(t);

    } else if (i >= List<T>::mCount) {   /* It's the append use-case. */
        append(t);

    } else {
        Node<T> *n;
        unsigned pos;
        for (n = mHead, pos = 0;
             pos < i-1 && n != NULL;
             pos++, n = n->next);
        assert(n != NULL);
        n->next = mNodeFactory->makeNode(t, n->next);
        List<T>::mCount++;
    }
}

template <typename T>
void RawLinkedList<T>::removeAt(unsigned i)
{
    Node<T> *n, *d;
    unsigned pos;

    assert(i < List<T>::mCount);
    assert(mHead != NULL && mLast != NULL);

    /* Get the element to remove */
    if (i == 0) {
        d = mHead;
        mHead = mHead->next;
    } else {
        for (n = mHead, pos = 0;
                pos < i-1 && n != NULL;
                pos++, n = n->next);
        assert(n != NULL);
        assert(pos == i-1);
        d = n->next;
        n->next = d->next;
    }

    /* Handle the last element case */
    if (mLast == d) {
        mLast = n;
    }

    /* Handle when the list is empty */
    if (mHead == NULL) {
        mLast = NULL;
    }

    /* Effectively remove */
    delete d;
    List<T>::mCount--;
}

template <typename T>
const T& RawLinkedList<T>::at(unsigned i)
{
    Node<T> *n;
    unsigned pos;

    assert(i < List<T>::mCount);
    for (n = mHead, pos = 0;
         pos < i && n != NULL;
         pos++, n = n->next);
    assert(n != NULL);
    return n->value;
}

template <typename T>
bool RawLinkedList<T>::isHealthy(void)
{
    if (List<T>::mCount == 0 && (mHead != NULL || mLast != NULL))
        return false;

    if (mHead == NULL && (List<T>::mCount != 0 || mLast != NULL))
        return false;

    if (mLast == NULL && (List<T>::mCount != 0 || mHead != NULL))
        return false;

    /* Check ends consistency */
    if (List<T>::mCount == 1 && mHead != mLast)
        return false;

    /* Check that list is NULL terminated */
    if (mLast != NULL && mLast->next != NULL)
        return false;

    if (List<T>::mCount != 0) {
        Node<T> *n = mHead;
        unsigned count = 1; /* At least one element ! */

        while (n->next != NULL) {
            count++;
            n = n->next;
        }

        if (count != List<T>::mCount)
            return false;

        if (n != mLast)
            return false;
    }

    return true;
}
#endif /* _RAWLINKEDLIST_H_ */
