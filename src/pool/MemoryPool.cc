// @Author: loser
#include "MemoryPool.h"
#include <cassert>

MemoryPool::~MemoryPool() {
  // free the blocks
  Slot *cur = current_block_;
  while (cur) {
    Slot *next = cur->next;
    operator delete(reinterpret_cast<void *>(cur));
    cur = next;
  }
}

void MemoryPool::init(int size) {
  assert(size > 0);
  slot_size_ = size;
  current_block_ = nullptr;
  current_slot_ = nullptr;
  last_slot_ = nullptr;
  free_slot_ = nullptr;
}

size_t MemoryPool::calPadSpcae(char *p, size_t align) {
  size_t result = reinterpret_cast<size_t>(p);
  return ((align - result) % align);
}

// allcated new block
Slot *MemoryPool::allocateBlock() 
{
    char* newBlock = reinterpret_cast<char*>(operator new(BLOCKSIZE));
    char* body = newBlock + sizeof(Slot*);
    // calculate the free space
    size_t bodyPadSpace = calPadSpcae(body, static_cast<size_t>(slot_size_));
    Slot* useSlot; 
    {
        std::lock_guard<std::mutex> lock{ mutex_other_ };
        reinterpret_cast<Slot*>(newBlock) -> next = current_block_;
        current_block_ = reinterpret_cast<Slot*>(newBlock);
        // the first Node of unused nodes
        current_slot_ = reinterpret_cast<Slot*>(body + bodyPadSpace);
        last_slot_ = reinterpret_cast<Slot*>(newBlock + BLOCKSIZE - slot_size_ + 1);  
        useSlot = current_slot_;

        current_slot_ += (slot_size_ >> 3); // slot_size_ = 1 即可
    }

    return useSlot;
}

Slot* MemoryPool::nofreeSlove() 
{
    if(current_slot_ >= last_slot_) return allocateBlock();
    
    Slot* useSlot;
    {
        std::lock_guard<std::mutex> lock { mutex_other_ };
        useSlot = current_slot_;
        current_slot_ += (slot_size_ >> 3);
    }
    return useSlot;
}

Slot* MemoryPool::allocate()
{
    if(free_slot_) {
        {
            std::lock_guard<std::mutex> lock { mutex_free_slot_ };
            if(free_slot_) {
                Slot* result = free_slot_;
                free_slot_ = free_slot_-> next;
                return result;
            }
        }
    }
    return nofreeSlove();
}

inline void MemoryPool::deAllcate(Slot* p)
{
    if(p) {
        std::lock_guard<std::mutex> lock{ mutex_free_slot_ };
        p -> next = free_slot_;
        free_slot_ = p;
    }
}

MemoryPool& getMemoryPool(int id)
{
    static MemoryPool MemoryPool_[MEMORYPOOLNUM];
    return MemoryPool_[id];
}

void initMemoryPool()
{
    for(int i = 0 ; i < MEMORYPOOLNUM ; i ++) {
        getMemoryPool(i).init((i + 1) << 3); }
}

void* useMemory(size_t size)
{
    if(!size) {
        return nullptr;
    } else {
        return operator new(size);
    }
    return reinterpret_cast<void*>(getMemoryPool(((size + 7) >> 3) - 1).allocate());
}

void freeMemory(size_t size, void *p)
{
    if(!p) return ;
    if(size > 512) {
        operator delete(p);
        return;
    }
    
    getMemoryPool(((size + 7) >> 3) - 1).deAllcate(reinterpret_cast<Slot*>(p));
}
