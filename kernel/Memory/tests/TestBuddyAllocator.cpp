#include "TestBuddyAllocator.h"
#include <string.h>
#include <stdint.h>

void TestBuddyAllocator::setUp(void)
{
   memset(mTZL, 0, sizeof(struct freeblock) * MAX_INDEX);
   memset(mMemHeap, 0, 1 << MAX_INDEX);
   mAllocator = new BuddyAllocator(mTZL, MAX_INDEX, mMemHeap, HEAP_SIZE);
}


void TestBuddyAllocator::tearDown(void) 
{
   delete mAllocator;
}

void TestBuddyAllocator::testHeapSize(void)
{
    uint32_t heapSize;

    heapSize = mAllocator->heapSize();
    TS_ASSERT_EQUALS(heapSize, (uint32_t)HEAP_SIZE);
}

void TestBuddyAllocator::testSimpleAllocations(void)
{
   void *m1 = NULL;
   void *m2 = NULL;
   void *mref = NULL;
   uint32_t i1, i2, iref;

   mref = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, (void*)NULL); 

   memset(mref, 4, HEAP_SIZE);
   mAllocator->free(mref, HEAP_SIZE);

   m1 = mAllocator->alloc(64);
   TS_ASSERT_DIFFERS(m1, (void*)NULL); 
   memset(m1, 0, 1);

   m2 = mAllocator->alloc(64);
   TS_ASSERT_DIFFERS(m2, (void*)NULL); 
   memset(m2, 0, 1);

   i1 = (uint32_t)m1;
   i2 = (uint32_t)m2;
   iref = (uint32_t)mref;
   TS_ASSERT_EQUALS((i1 - iref) ^ (i2 - iref), (uint32_t)64);

   mAllocator->free(m1, 64);
   mAllocator->free(m2, 64);

   mref = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, (void*)NULL);
   memset(mref, 4, HEAP_SIZE);
   mAllocator->free(mref, HEAP_SIZE);
}


void TestBuddyAllocator::testFreeBoundaries(void)
{
   void *m1 = NULL;

   m1 = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(m1, (void*)NULL);
   mAllocator->free(m1, HEAP_SIZE);
}


void TestBuddyAllocator::testCheckAddresses(void)
{
   void *m1 = NULL;
   void *m2 = NULL;
   void *mref = NULL;
   uint32_t i1, i2, iref;

   mref = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, (void*)NULL); 

   memset(mref, 4, HEAP_SIZE);
   mAllocator->free(mref, HEAP_SIZE);

   m1 = mAllocator->alloc(64);
   TS_ASSERT_DIFFERS(m1, (void*)NULL); 
   memset(m1, 0, 1);

   m2 = mAllocator->alloc(64);
   TS_ASSERT_DIFFERS(m2, (void*)NULL); 
   memset(m2, 0, 1);

   i1 = (uint32_t)m1;
   i2 = (uint32_t)m2;
   iref = (uint32_t)mref;
   TS_ASSERT_EQUALS((i1 - iref) ^ (i2 - iref), (uint32_t)64);

   mAllocator->free(m1, 64);
   mAllocator->free(m2, 64);

   TS_ASSERT((int)m1 >= (int)mref);
   TS_ASSERT((int)m1 < ((int)mref + HEAP_SIZE));
   TS_ASSERT((int)m2 >= (int)mref);
   TS_ASSERT((int)m2 < ((int)mref + HEAP_SIZE));
}

void TestBuddyAllocator::testFullAllocationsBySizes(void)
{
   void *chunk;
   void *areas[HEAP_SIZE / 4];

   for (int allocSize = 4; allocSize <= HEAP_SIZE; allocSize <<= 1) {
      /* Allocate all the memory in small chunks */
      for (int i = 0; i < HEAP_SIZE / allocSize; i++) {
         chunk = mAllocator->alloc(allocSize);
         TS_ASSERT_DIFFERS(chunk, (void*)NULL);
         areas[i] = chunk;
         chunk = NULL;
      }

      /* Free it */
      for (int i = 0; i < HEAP_SIZE / allocSize; i++) {
         mAllocator->free(areas[i], allocSize);
      }

      /* Check memory have been released */
      chunk = mAllocator->alloc(HEAP_SIZE);
      TS_ASSERT_DIFFERS(chunk, (void*)NULL);
      mAllocator->free(chunk, HEAP_SIZE);
   }
}


void TestBuddyAllocator::testAllocateOneOfEachSize(void)
{
   int size = 0;
   void *chunk;
   void *areas[MAX_INDEX];

   for (int i = MAX_INDEX - 1; i >= 4; i--) {
      size = 1 << i;
      chunk = mAllocator->alloc(size);
      TS_ASSERT_DIFFERS(chunk, (void*)NULL);
      areas[i] = chunk;
      chunk = NULL;
   }

   for (int i = 4; i < MAX_INDEX; i++) {
      mAllocator->free(areas[i], 1 << i);
   }

   /* Check memory have been released */
   chunk = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(chunk, (void*)NULL);
   mAllocator->free(chunk, HEAP_SIZE);
}


void TestBuddyAllocator::testSmallAllocations(void)
{
   void *chunk;
   void *areas[3];

   /* Try small and special allocations */
   for (int i = 1; i < 4; i++) {
      areas[i-1] = mAllocator->alloc(i);
      TS_ASSERT_DIFFERS(areas[0], (void*)NULL);
   }

   for (int i = 1; i < 4; i++) {
      mAllocator->free(areas[i-1], i);
   }

   /* Check allocator consistency */
   chunk = mAllocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(chunk, (void*)NULL);
   mAllocator->free(chunk, HEAP_SIZE);
}


void TestBuddyAllocator::testBadAllocationRequests(void)
{
   void *chunk;

   chunk = mAllocator->alloc(0);
   TS_ASSERT_EQUALS(chunk, (void*)NULL);
}


void TestBuddyAllocator::testBadFreeRequests(void)
{
   void *chunk = (void*)0xDEADBEEF;

   /*
    * Even if this is not directly visible,
    * ensure this does not throw something bad.
    */
   mAllocator->free(NULL, 8);
   mAllocator->free(chunk, 0);
}
