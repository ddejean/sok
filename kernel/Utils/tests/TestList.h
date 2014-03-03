#ifndef _TESTLIST_H_
#define _TESTLIST_H_

#include "CxxTest/TestSuite.h"
#include "InstrumentedLinkedList.h"

/**
 * Implements tests for the List<T> template class.
 */
class TestList : public CxxTest::TestSuite
{
private:
    struct Element {
        Element(void) : mIndex(0) {};
        Element(unsigned i) : mIndex(i) {};
        unsigned mIndex;
    };
    InstrumentedLinkedList<Element> *mList;
    void initElementTable(Element *e, unsigned count);

public:
    void setUp(void);
    void tearDown(void);

    void testCount(void);
    void testIsEmpty(void);
    void testClear(void);
    void testAppend(void);
    void testPrepend(void);
    void testInsertWithAnEmptyList(void);
    void testInsertWithAFilledList(void);
    void testRemoveAtTheBeginning(void);
    void testRemoveAtTheEnd(void);
    void testRemoveAtTheMiddle(void);
    void testAt(void);
};

#endif /* _TESTLIST_H_ */
