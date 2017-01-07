#ifndef MIN_HEAP
#define MIN_HEAP

#include <vector>
#include <stdexcept>

template <typename T>
class MinHeap {
  std::vector<T> items;
  int size, capacity;
  int getLeftChildIndex(int parentIndex)   { return 2*parentIndex + 1; }
  int getRightChildIndex(int parentIndex)  { return 2*parentIndex + 2; }
  int getParentIndex(int childIndex)       { return (childIndex-1)/2;  }
  bool hasLeftChild(int index)             { return getLeftChildIndex(index) < size; }
  bool hasRightChild(int index)            { return getRightChildIndex(index) < size; }
  bool hasParent(int index)                { return getParentIndex(index) < size; }
  int leftChild(int index)                 { return items[getLeftChildIndex(index)]; }
  int rightChild(int index)                { return items[getRightChildIndex(index)]; }
  int parent(int index)                    { return items[getParentIndex(index)]; }
  void swap(int indexOne, int indexTwo) {
    int tmp = items[indexOne];
    items[indexOne] = items[indexTwo];
    items[indexTwo] = tmp;
  }
  void ensureExtraCapacity() {
    if(size == capacity) {
        items.resize(capacity*2);  
    }
  }
public:
  MinHeap() : size(0), capacity(100) { items.resize(capacity); }
  T peek() {
    if(size == 0) throw std::invalid_argument("Heap is empty");

    return items[0];
  }
  T poll() { /* delete item */
    if(size == 0) throw std::invalid_argument("Heap is empty");

    T item = items[0];
    items[0] = items[size-1];
    size--;
    heapifyDown();
    return item;
  }
  void add(T item) {
    ensureExtraCapacity();
    items[size] = item;
    size++;
    heapifyUp();
  }
  void heapifyUp() {
    int index = size-1;
    while(hasParent(index) && parent(index) > items[index]) {
      swap(getParentIndex(index), index);
      index = getParentIndex(index);
    }
  }
  void heapifyDown() {
    int index = 0;

    while(hasLeftChild(index)) {
      // We're looking for left child because heap is a compact data structure.
      // if there's is a child, it must be a left child.
      int smallerChildIndex = getLeftChildIndex(index);
      if(hasRightChild(index) && rightChild(index) < items[smallerChildIndex]) 
        smallerChildIndex = getRightChildIndex(index);

      if(items[index] < items[smallerChildIndex]) 
        break; // Heap is in order
      else {
        swap(index, smallerChildIndex);
        index = smallerChildIndex;
      }
    }
  }
  bool isEmpty() { return size == 0; }
  int getSize()     { return size; }
};
#endif