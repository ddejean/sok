/*
 * LinkedList.h
 *
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Linked list implementation with a standard memory allocation interface.
 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "RawLinkedList.h"

template <typename T>
class LinkedList : public RawLinkedList<T>
{
private:
    /**
     * Node factory that allocates nodes from the standard/system-wide memory pool.
     */
    template <typename V>
    class StandardNodeFactory : public NodeFactory<V>
    {
    public:
        virtual Node<V> *makeNode(const V &v, Node<V> *n) {
            return new Node<V>(v, n);
        }
        virtual ~StandardNodeFactory() { /* Nothing to do */ }
    };

public:
    LinkedList(void) : RawLinkedList<T>(new StandardNodeFactory<T>()) {};
};

#endif /* _LINKEDLIST_H_ */
