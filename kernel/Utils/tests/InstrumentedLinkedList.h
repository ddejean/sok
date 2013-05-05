#ifndef _INSTRUMENTEDLIST_H_
#define _INSTRUMENTEDLIST_H_

#include "Utils/LinkedList.h"

template <typename T>
class InstrumentedLinkedList : public LinkedList<T> {
public:
    bool listIsHealthy(void);
};

template <typename T>
bool InstrumentedLinkedList<T>::listIsHealthy(void)
{
    if (LinkedList<T>::mCount == 0 && (LinkedList<T>::mHead != NULL || LinkedList<T>::mLast != NULL))
        return false;

    if (LinkedList<T>::mHead == NULL && (LinkedList<T>::mCount != 0 || LinkedList<T>::mLast != NULL))
        return false;

    if (LinkedList<T>::mLast == NULL && (LinkedList<T>::mCount != 0 || LinkedList<T>::mHead != NULL))
        return false;

    /* Check ends consistency */
    if (LinkedList<T>::mCount == 1 && LinkedList<T>::mHead != LinkedList<T>::mLast)
        return false;

    /* Check that list is NULL terminated */
    if (LinkedList<T>::mLast != NULL && LinkedList<T>::mLast->next != NULL)
        return false;

    if (LinkedList<T>::mCount != 0) {
        typename LinkedList<T>::Node *n = LinkedList<T>::mHead;
        unsigned count = 0;

        while (n->next != NULL) {
            count++;
            n = n->next;
        }

        if (count != LinkedList<T>::mCount)
            return false;

        if (n != LinkedList<T>::mLast)
            return false;
    }

    return true;
}

#endif  /*_INSTRUMENTEDLIST_H_ */
