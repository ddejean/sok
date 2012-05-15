#ifndef TESTBUDDYALLOCATOR_H_
#define TESTBUDDYALLOCATOR_H_

#include "CxxTest/TestSuite.h"
#include "Memory/BuddyAllocator.h"

#define MAX_INDEX    20
#define HEAP_SIZE    (1 << MAX_INDEX)

class TestBuddyAllocator: public CxxTest::TestSuite {
private:
   struct freeblock _TZL[MAX_INDEX];
   char _memHeap[1 << MAX_INDEX];
   BuddyAllocator* _allocator;

public:
	void setUp(void);
	void tearDown(void);

   void testSimpleAllocations(void);
   void testFreeBoundaries(void);
   void testCheckAddresses(void);
   void testFullAllocationsBySizes(void);
   void testAllocateOneOfEachSize(void);
   void testSmallAllocations(void);

   void testBadAllocationRequests(void);
   void testBadFreeRequests(void);
};

#endif /* TESTBUDDYALLOCATOR_H_ */
