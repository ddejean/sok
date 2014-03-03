#include "TestList.h"
#include <stdio.h>

void TestList::setUp(void)
{
    mList = new InstrumentedLinkedList<Element>();
    TS_ASSERT_EQUALS(true, mList->isEmpty());
    TS_ASSERT_EQUALS(0u, mList->count());
}

void TestList::tearDown(void)
{
    delete mList;
    mList = NULL;
}

void TestList::testCount(void)
{
    Element e1(1);
    Element e2(2);

    mList->append(e1);
    TS_ASSERT_EQUALS(1u, mList->count());
    mList->append(e2);
    TS_ASSERT_EQUALS(2u, mList->count());

    mList->clear();
    TS_ASSERT_EQUALS(0u, mList->count());
}

void TestList::testIsEmpty(void)
{
    Element e(123456);

    mList->append(e);
    TS_ASSERT_EQUALS(false, mList->isEmpty());

    mList->clear();
    TS_ASSERT_EQUALS(true, mList->isEmpty());
}

void TestList::testClear(void)
{
    Element e1(1);
    Element e2(2);
    Element e3(3);
    Element e4(4);

    mList->append(e1);
    mList->append(e2);
    mList->append(e3);
    mList->append(e4);
    TS_ASSERT_EQUALS(4u, mList->count());

    mList->clear();
    TS_ASSERT_EQUALS(0u, mList->count());
    TS_ASSERT_EQUALS(true, mList->isEmpty());
}

inline void TestList::initElementTable(Element *e, unsigned count)
{
    for (unsigned i = 0; i < count; i++) {
        e[i] = Element(i);
    }
}

void TestList::testAppend(void)
{
/* Local element number definition */
#define ELEM_NUM    100u

    Element e[ELEM_NUM];
    initElementTable(e, ELEM_NUM);

    /* Test list implementation */
    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->append(e[i]);
        TS_ASSERT_EQUALS(i+1, mList->count());
        Element r = mList->at(mList->count() - 1);
        TS_ASSERT_EQUALS(e[i].mIndex, r.mIndex);
    }

    /* Check we do not break list counts */
    TS_ASSERT_EQUALS(false, mList->isEmpty());
    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());
    TS_ASSERT(mList->isHealthy());

    /* Check list integrity */
    TS_ASSERT(mList->isHealthy());

#undef ELEM_NUM
}

void TestList::testPrepend(void)
{
/* Local element number definition */
#define ELEM_NUM    100u

    Element e[ELEM_NUM];
    initElementTable(e, ELEM_NUM);

    /* Test prepend implementation */
    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->prepend(e[i]);
        TS_ASSERT_EQUALS(i+1, mList->count());
        Element r = mList->at(0);
        TS_ASSERT_EQUALS(e[i].mIndex, r.mIndex);
    }

    /* Check we do not break list counts */
    TS_ASSERT_EQUALS(false, mList->isEmpty());
    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());
    TS_ASSERT(mList->isHealthy());

    /* Check list integrity */
    TS_ASSERT(mList->isHealthy());

#undef ELEM_NUM
}

void TestList::testInsertWithAnEmptyList(void)
{
    Element e(0xDEAD);
    Element c(0); /* Control element */

    TS_ASSERT_EQUALS(true, mList->isEmpty());

    /* Insertion at the beginning */
    mList->insert(e, 0);
    TS_ASSERT_EQUALS(1u, mList->count());
    c = mList->at(0);
    TS_ASSERT_EQUALS(e.mIndex, c.mIndex);

    mList->clear();
    TS_ASSERT_EQUALS(true, mList->isEmpty());

    /* Insertion at the end */
    mList->insert(e, mList->count() + 1);
    TS_ASSERT_EQUALS(1u, mList->count());
    c = mList->at(0);
    TS_ASSERT_EQUALS(e.mIndex, c.mIndex);
    TS_ASSERT(mList->isHealthy());

    mList->clear();
    TS_ASSERT_EQUALS(true, mList->isEmpty());
}

void TestList::testInsertWithAFilledList(void)
{
/* Local element number definition */
#define ELEM_NUM    10u

    Element e[ELEM_NUM];
    initElementTable(e, ELEM_NUM);

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->insert(e[i], mList->count());
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        Element ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }

    unsigned myPosition = mList->count() / 2;
    Element special(0xB00B);
    mList->insert(special, myPosition);
    Element control = mList->at(myPosition);
    TS_ASSERT_EQUALS(special.mIndex, control.mIndex);
    TS_ASSERT(mList->isHealthy());

    mList->clear();
    TS_ASSERT_EQUALS(true, mList->isEmpty());

#undef ELEM_NUM
}

void TestList::testRemoveAtTheBeginning(void)
{
/* Local element number definition */
#define ELEM_NUM    10u

    Element e[ELEM_NUM];
    Element ctrl;
    initElementTable(e, ELEM_NUM);

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->insert(e[i], mList->count());
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }

    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        TS_ASSERT_EQUALS(ELEM_NUM - i, mList->count());
        ctrl = mList->at(0);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
        mList->removeAt(0);
        TS_ASSERT(mList->isHealthy());
    }

    TS_ASSERT_EQUALS(true, mList->isEmpty());

#undef ELEM_NUM
}

void TestList::testRemoveAtTheEnd(void)
{
/* Local element number definition */
#define ELEM_NUM    10u

    Element e[ELEM_NUM];
    Element ctrl;
    initElementTable(e, ELEM_NUM);

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->insert(e[i], mList->count());
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }

    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());

    for (int i = ELEM_NUM - 1; i >= 0; i--) {
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, (int)ctrl.mIndex);
        mList->removeAt(i);
        TS_ASSERT(mList->isHealthy());
    }

    TS_ASSERT_EQUALS(true, mList->isEmpty());

#undef ELEM_NUM
}

void TestList::testRemoveAtTheMiddle(void)
{
/* Local element number definition */
#define ELEM_NUM    10u

    Element e[ELEM_NUM];
    Element ctrl, cur;
    initElementTable(e, ELEM_NUM);

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->insert(e[i], mList->count());
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }

    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());

    /* Remove an element in the middle */
    ctrl = mList->at(ELEM_NUM / 2);
    mList->removeAt(ELEM_NUM / 2);
    TS_ASSERT_EQUALS(ELEM_NUM - 1u, mList->count());
    TS_ASSERT(mList->isHealthy());

    /* Ensure the element is not in anymore */
    for (unsigned i = 0; i < ELEM_NUM - 1; i++) {
        cur = mList->at(i);
        TS_ASSERT_DIFFERS(ctrl.mIndex, cur.mIndex);
    }

#undef ELEM_NUM
}

void TestList::testAt(void)
{
/* Local element number definition */
#define ELEM_NUM    10u

    Element e[ELEM_NUM];
    Element ctrl;
    initElementTable(e, ELEM_NUM);

    for (unsigned i = 0; i < ELEM_NUM; i++) {
        mList->insert(e[i], mList->count());
        TS_ASSERT_EQUALS(i + 1u, mList->count());
        Element ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }

    TS_ASSERT_EQUALS(ELEM_NUM, mList->count());
    TS_ASSERT(mList->isHealthy());

    /* Check we're getting the right element */
    for (unsigned i = 0; i < mList->count(); i++) {
        ctrl = mList->at(i);
        TS_ASSERT_EQUALS(i, ctrl.mIndex);
    }
#undef ELEM_NUM
}
