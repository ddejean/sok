/*
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * List.h: Abstract class for list implementation.
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

#define UNUSED(var) ((void)var)

template <typename T> class List
{
protected:
    /* Number of elements in the list */
    unsigned mCount;

    /**
     * Initializes the abstract class.
     * @note protected as we don't want to be instantiable.
     */
    List() : mCount(0) {};

public:
    virtual ~List() {};

    /**
     * Retrieve the number of elements inserted in the list.
     * @return the element count.
     */
    virtual unsigned count(void);

    /**
     * Tell if the list is empty.
     * @return true if the list is empty, ie count() == 0.
     */
    virtual bool isEmpty(void);

    /**
     * Remove all entries in the list. Has no effects on an empty list.
     */
    virtual void clear(void) = 0;

    /**
     * Add an element as the end of the list.
     * @param t the element to add to the list.
     */
    virtual void append(const T &t) = 0;

    /**
     * Add an element at the beggining of the list. Its index will be 0.
     * @param t the element to add to the list.
     */
    virtual void prepend(const T &t) = 0;

    /**
     * Insert an element at the specified position. If i >= count(), the element
     * is added at the end of the list.
     * @param t the element to add.
     * @param i the index where to add the element.
     */
    virtual void insert(const T &t, unsigned i) = 0;

    /**
     * Remove the element at the specified index.
     * @param i index of the element to remove.
     *
     * @pre i < count() or failure.
     */
    virtual void removeAt(unsigned i) = 0;

    /**
     * Retrieve the element at the specified position.
     * @param i the index of the element to retrieve.
     * @return the element requested with the index.
     *
     * @pre i < count() or failure.
     */
    virtual const T& at(unsigned i) = 0;
};

template <typename T>
unsigned List<T>::count(void)
{
    return mCount;
}

template <typename T>
bool List<T>::isEmpty(void)
{
    return (mCount == 0u);
}

#endif /* _LIST_H_ */
