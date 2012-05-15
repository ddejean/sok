#include "TestBuddyAllocator.h"
#include <string.h>
#include <stdint.h>

void TestBuddyAllocator::setUp(void)
{
   memset(_TZL, 0, sizeof(struct freeblock) * MAX_INDEX);
   memset(_memHeap, 0, 1 << MAX_INDEX);
   _allocator = new BuddyAllocator(_TZL, MAX_INDEX, _memHeap, HEAP_SIZE);
}


void TestBuddyAllocator::tearDown(void) 
{
   delete _allocator;
}

void TestBuddyAllocator::testHeapSize(void)
{
    uint32_t heapSize;

    heapSize = _allocator->heapSize();
    TS_ASSERT_EQUALS(heapSize, (uint32_t)HEAP_SIZE);
}

void TestBuddyAllocator::testSimpleAllocations(void)
{
   void *m1 = NULL;
   void *m2 = NULL;
   void *mref = NULL;
   uint32_t i1, i2, iref;

   mref = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, NULL); 

   memset(mref, 4, HEAP_SIZE);
   _allocator->free(mref, HEAP_SIZE);

   m1 = _allocator->alloc(64);
   TS_ASSERT_DIFFERS(m1, NULL); 
   memset(m1, 0, 1);

   m2 = _allocator->alloc(64);
   TS_ASSERT_DIFFERS(m2, NULL); 
   memset(m2, 0, 1);

   i1 = (uint32_t)m1;
   i2 = (uint32_t)m2;
   iref = (uint32_t)mref;
   TS_ASSERT_EQUALS((i1 - iref) ^ (i2 - iref), (uint32_t)64);

   _allocator->free(m1, 64);
   _allocator->free(m2, 64);

   mref = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, NULL);
   memset(mref, 4, HEAP_SIZE);
   _allocator->free(mref, HEAP_SIZE);
}


void TestBuddyAllocator::testFreeBoundaries(void)
{
   void *m1 = NULL;

   m1 = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(m1, NULL);
   _allocator->free(m1, HEAP_SIZE);
}


void TestBuddyAllocator::testCheckAddresses(void)
{
   void *m1 = NULL;
   void *m2 = NULL;
   void *mref = NULL;
   uint32_t i1, i2, iref;

   mref = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(mref, NULL); 

   memset(mref, 4, HEAP_SIZE);
   _allocator->free(mref, HEAP_SIZE);

   m1 = _allocator->alloc(64);
   TS_ASSERT_DIFFERS(m1, NULL); 
   memset(m1, 0, 1);

   m2 = _allocator->alloc(64);
   TS_ASSERT_DIFFERS(m2, NULL); 
   memset(m2, 0, 1);

   i1 = (uint32_t)m1;
   i2 = (uint32_t)m2;
   iref = (uint32_t)mref;
   TS_ASSERT_EQUALS((i1 - iref) ^ (i2 - iref), (uint32_t)64);

   _allocator->free(m1, 64);
   _allocator->free(m2, 64);

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
         chunk = _allocator->alloc(allocSize);
         TS_ASSERT_DIFFERS(chunk, NULL);
         areas[i] = chunk;
         chunk = NULL;
      }

      /* Free it */
      for (int i = 0; i < HEAP_SIZE / allocSize; i++) {
         _allocator->free(areas[i], allocSize);
      }

      /* Check memory have been released */
      chunk = _allocator->alloc(HEAP_SIZE);
      TS_ASSERT_DIFFERS(chunk, NULL);
      _allocator->free(chunk, HEAP_SIZE);
   }
}


void TestBuddyAllocator::testAllocateOneOfEachSize(void)
{
   int size = 0;
   void *chunk;
   void *areas[MAX_INDEX];

   for (int i = MAX_INDEX - 1; i >= 4; i--) {
      size = 1 << i;
      chunk = _allocator->alloc(size);
      TS_ASSERT_DIFFERS(chunk, NULL);
      areas[i] = chunk;
      chunk = NULL;
   }

   for (int i = 4; i < MAX_INDEX; i++) {
      _allocator->free(areas[i], 1 << i);
   }

   /* Check memory have been released */
   chunk = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(chunk, NULL);
   _allocator->free(chunk, HEAP_SIZE);
}


void TestBuddyAllocator::testSmallAllocations(void)
{
   void *chunk;
   void *areas[3];

   /* Try small and special allocations */
   for (int i = 1; i < 4; i++) {
      areas[i-1] = _allocator->alloc(i);
      TS_ASSERT_DIFFERS(areas[0], NULL);
   }

   for (int i = 1; i < 4; i++) {
      _allocator->free(areas[i-1], i);
   }

   /* Check allocator consistency */
   chunk = _allocator->alloc(HEAP_SIZE);
   TS_ASSERT_DIFFERS(chunk, NULL);
   _allocator->free(chunk, HEAP_SIZE);
}


void TestBuddyAllocator::testBadAllocationRequests(void)
{
   void *chunk;

   chunk = _allocator->alloc(0);
   TS_ASSERT_EQUALS(chunk, NULL);
}


void TestBuddyAllocator::testBadFreeRequests(void)
{
   void *chunk = (void*)0xDEADBEEF;

   /*
    * Even if this is not directly visible,
    * ensure this does not throw something bad.
    */
   _allocator->free(NULL, 8);
   _allocator->free(chunk, 0);
}
