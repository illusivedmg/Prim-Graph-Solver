#include "MinHeap.h"


MinHeap::Node::Node(int lab) 
: mLabel(lab) {
  mKey = INT_MAX;
  mPrev = -1;
}

MinHeap::Node::Node(int label, int prev, int key)
: mLabel(label), mPrev(prev), mKey(key) {
  
}


MinHeap::MinHeap() { 
  mHeap.push_back(NULL); // 1-index
  mPositions.push_back(-1); // 1-index
}


MinHeap::~MinHeap() {

}


void MinHeap::displayHeap() {
  std::cout << "Displaying Heap" << std::endl;
  for (int C = 1; C < mHeap.size(); C++)
    std::cout << C << ": " << mHeap[C]->mLabel << " " << mHeap[C]->mKey << std::endl;
  std::cout << std::endl;
}


void MinHeap::displayPositions() {
  std::cout << "Displaying Positions" << std::endl;
  for (int C = 1; C < mPositions.size(); C++)
    std::cout << C << ": " << mPositions[C] << std::endl;
  std::cout << std::endl;
}


void MinHeap::swapPositions(int goldenChild, int scapeGoat) {
  mPositions[mHeap[scapeGoat]->mLabel] = goldenChild;
  mPositions[mHeap[goldenChild]->mLabel] = scapeGoat;

  std::swap(mHeap[goldenChild], mHeap[scapeGoat]);
}


void MinHeap::bubbleUp(int child) {
  int parent = Parent(child);
  if (child > 1 && mHeap[parent]->mKey > mHeap[child]->mKey) {
    swapPositions(child, parent);
    bubbleUp(parent);
  }
}


void MinHeap::siftDown(int parent) {
  int lChild = Left(parent);
  int rChild = Right(parent);
  int toddler = parent;

  if (lChild <= numElements() && mHeap[lChild]->mKey < mHeap[parent]->mKey)
    toddler = lChild;

  if (rChild <= numElements() && mHeap[rChild]->mKey < mHeap[toddler]->mKey)
    toddler = rChild;

  if (toddler != parent) {
    swapPositions(parent, toddler);
    siftDown(toddler);
  }
}


void MinHeap::decreaseKey(int label, int key, int prev) {
  int C = mPositions[label];
  mHeap[C]->mKey = key;
  mHeap[C]->mPrev = prev;
  bubbleUp(C);
}


void MinHeap::insert(Node* x) {
  mHeap.push_back(x);
  mPositions.push_back(numElements());
  bubbleUp(numElements());
}


void MinHeap::makeHeap(const std::vector<Node*> &S) {
  for (int C = 0; C < S.size(); C++) {
    mHeap.push_back(S[C]);
    mPositions.push_back(C+1);
  }

  for (int B = numElements(); B > 0; B--)
    siftDown(B);
}


MinHeap::Node* MinHeap::deleteMin() {
  if (isEmpty()) {
    std::cerr << "Trying to delete top element of empty heap. Exiting." << std::endl;
    exit(1);
  }

  Node* toPop = mHeap[1];
  swapPositions(1, numElements());
  mHeap.pop_back();
  mPositions[toPop->mLabel] = -1;
  siftDown(1);
  
  return toPop;
}