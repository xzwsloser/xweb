// @Author: loser
#pragma once
#include <memory>
#include <mutex>


namespace xweb {

#define BLOCKSIZE 4096 // 4KB
#define MEMORYPOOLNUM 64

// one Slot in memoryBlock
struct Slot {
  Slot *next;
};

class MemoryPool {
public:
  MemoryPool() = default;
  ~MemoryPool();

  void init(int size);

  // allocate a slot space
  Slot *allocate();
  // return slot space
  void deAllcate(Slot *p);

private:
  int slot_size_; // eveny slot size

  Slot *current_block_; // first Node of block list
  Slot *current_slot_;  // first Node of Slot list
  Slot *last_slot_;     // last Node of Slot list
  Slot *free_slot_;     // first Node of free Slot list

  std::mutex mutex_free_slot_;
  std::mutex mutex_other_;

  // caculate the space use to padding the pointer to align size
  size_t calPadSpcae(char *p, size_t align);
  // allocate new Block , head insert into block list
  Slot *allocateBlock();
  // when the free slot list is empty , use this function to allocate space
  Slot *nofreeSlove();
};

MemoryPool &getMemoryPool(int id);
void initMemoryPool();
void *useMemory(size_t size);
void freeMemory(size_t size, void *p);

template <typename T, typename... Args> 
T *newElement(Args &&...args) {
  T *p;
  if ((p = reinterpret_cast<T *>(useMemory(sizeof(T)))) != nullptr) {
    new (p) T(std::forward<Args>(args)...);
  }
  return p;
}

template <typename T> 
void deleteElement(T *p) {
  if (p) {
    p->~T();
  }

  freeMemory(sizeof(T), reinterpret_cast<void *>(p));
}

}
