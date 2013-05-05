/*
 * LinkedList.h
 *
 * Copyright (C) 2012, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Linked list implementation of List interface.
 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "List.h"

template <typename T>
class LinkedList : public List<T>
{
protected:
    /**
     * A container element of the list.
     * value: the payload hold by this container.
     * next: the following container.
     */
    struct Node {
        const T value;
        Node *next;
        Node(const T &t, Node *n) : value(t), next(n) {};
    };

    /* First element of the list */
    Node *mHead;
    /* Last element of the list */
    Node *mLast;

public:
    LinkedList() : mHead(NULL), mLast(NULL) {};
    virtual ~LinkedList();

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
LinkedList<T>::~LinkedList(void)
{
    clear();
}

template <typename T>
void LinkedList<T>::clear(void)
{
    while (mHead != NULL) {
        Node *cur = mHead;
        mHead = mHead->next;
        delete cur;
    }
    mHead = mLast = NULL;
    List<T>::mCount = 0;
}

template <typename T>
void LinkedList<T>::append(const T &t)
{
    if (mHead == NULL && mLast == NULL) {
        mHead = mLast = new Node(t, NULL);
    } else {
        mLast->next = new Node(t, NULL);
        mLast = mLast->next;
    }
    List<T>::mCount++;
}

template <typename T>
void LinkedList<T>::prepend(const T &t)
{
    if (mHead == NULL && mLast == NULL) {
        mHead = mLast = new Node(t, NULL);
    } else {
        mHead = new Node(t, mHead);
    }
    List<T>::mCount++;
}

template <typename T>
void LinkedList<T>::insert(const T &t, unsigned i)
{
    if (i == 0) {               /* It's the prepend use-case. */
        prepend(t);

    } else if (i >= List<T>::mCount) {   /* It's the append use-case. */
        append(t);

    } else {
        Node *n;
        unsigned pos;
        for (n = mHead, pos = 0;
             pos < i-1 && n != NULL;
             pos++, n = n->next);
        assert(n != NULL);
        n->next = new Node(t, n->next);
        List<T>::mCount++;
    }
}

template <typename T>
void LinkedList<T>::removeAt(unsigned i)
{
    Node *n, *d;
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
const T& LinkedList<T>::at(unsigned i)
{
    Node *n;
    unsigned pos;

    assert(i < List<T>::mCount);
    for (n = mHead, pos = 0;
         pos < i && n != NULL;
         pos++, n = n->next);
    assert(n != NULL);
    return n->value;
}

template <typename T>
bool LinkedList<T>::isHealthy(void)
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
        Node *n = mHead;
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
#endif /* _LINKEDLIST_H_ */
