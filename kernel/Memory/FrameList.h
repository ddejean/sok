/*
 * FrameList.h
 *
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * LinkedList implemented for hardware frame management to allocate on the
 * BootstrapAllocator.
 */

#ifndef _FRAMELIST_H_
#define _FRAMELIST_H_

#include "Utils/RawLinkedList.h"
#include "BootstrapAllocator.h"

class FrameList : public RawLinkedList<void*>
{
private:
    /**
     * Node class extension designed to be allocated on Bootstrap allocator.
     * @note Operators implementation almost duplicates RunTime/allocation.cpp.
     */
    template <typename V>
    class FrameNode : public Node<V>
    {
    private:
        /* Keep size in the allocated chunk */
        struct AllocationHeader {
            size_t mySize;
            uint32_t magic;
        };

        /* Magic for chunk intergity */
#define MAGIC  0xBADB00B5u

    public:
         void* operator new (size_t size)
         {
             BootstrapAllocator *ba;
             struct AllocationHeader *ah;
             char *final_pointer;

             ba = BootstrapAllocator::getInstance();
             ah = ba->alloc(sizeof(*ah) + size);

             ah->mySize = sizeof(*ah) + size;
             ah->magic = (uint32_t)ah ^ MAGIC;

             final_pointer = (char*)ah;
             final_pointer += sizeof(*ah);

             return final_pointer;
         }

         void operator delete (void *p)
         {
             char *raw_pointer;
             size_t size;
             BootstrapAllocator *ba;
             struct AllocationHeader *ah;

             ba = BootstrapAllocator::getInstance();
             raw_pointer = (char*)p;
             ah = raw_pointer - sizeof(*ah);

             assert(ah->magic ^ MAGIC == (unsigned)ah);
             size = ah->mySize;

             ba->free(ah, size);
         }
    };

    /**
     * Node factory that allocates nodes from the standard/system-wide memory pool.
     */
    template <typename V>
    class FrameNodeFactory : public NodeFactory<V>
    {
    public:
        virtual Node<V> *makeNode(const V &v, Node<V> *n) {
            return new Node<V>(v, n);
        }
        virtual ~FrameNodeFactory() { /* Nothing to do */ }
    };

public:
    FrameList(void) : RawLinkedList<void*>(new FrameNodeFactory<void*>()) {};
};

#endif /* _FRAMELIST_H_ */
