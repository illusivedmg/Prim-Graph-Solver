#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <climits>


class MinHeap {
public:

  struct Node {
    Node(int label);

    Node(int label, int prev, int key);

    int mLabel, mPrev, mKey;
  };

  MinHeap();

  virtual ~MinHeap();

  int numElements() { return mHeap.size()-1; }

  int top() { return mHeap[1]->mLabel; }

  bool isEmpty() { return numElements() == 0; }

  int getKey(int label) { return mHeap[mPositions[label]]->mKey; }

  void displayHeap();

  void displayPositions();

  // Swap two indices in heap and update Pos vector
  void swapPositions(int goldenChild, int scapeGoat);

  // compare parent with child, swap if parent bigger
  void bubbleUp(int i);

  // compare parent with children, swap with smaller
  void siftDown(int i);

  // new value for key of existing node
  void decreaseKey(int label, int key, int prev);

  void insert(Node* x);

  void makeHeap(const std::vector<Node*> &S);

  // swaps and pops first/last in heap, swap/nullify in pos vector
  Node* deleteMin();

private:
  int Parent(int i) { return floor(i/2); };

  int Left(int i) { return (2*i); };

  int Right(int i) { return (2*i+1); };

  // index = position in heap, key = value to minimize
  std::vector<Node*> mHeap;

  // index = label, value = position in heap
  std::vector<int> mPositions;
};