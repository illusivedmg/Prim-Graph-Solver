#include "MinHeap.h"


MinHeap::MinHeap() { 
  mHeap.push_back(NULL);
  mPositions.push_back(NULL);
}


MinHeap::~MinHeap() {
  for (auto node : mPositions)
    delete node;
}


void MinHeap::displayHeap() {
  std::cout << "Displaying Heap" << std::endl;
  for (int c = 1; c < mHeap.size(); c++)
    std::cout << c << ": " << mHeap[c]->mLabel << " " << mHeap[c]->mKey << std::endl;
  std::cout << std::endl;
}


void MinHeap::displayPositions() {
  std::cout << "Displaying Positions" << std::endl;
  for (int c = 1; c < mPositions.size(); c++)
    std::cout << c << ": " << mPositions[c]->mLabel << " " << mPositions[c]->mKey << std::endl;
  std::cout << std::endl;
}


int MinHeap::getPositionOfLabel(int labelToFind, bool index) {
  for (int c = 1; c < mPositions.size(); c++) {
    if (mPositions[c]->mLabel == labelToFind)
      return index ? c : mPositions[c]->mKey;
  }
  return -1;
}


void MinHeap::swapPositions(int goldenChild, int scapeGoat) {
  int gcPos = getPositionOfLabel(mHeap[goldenChild]->mLabel, true);
  int sgPos = getPositionOfLabel(mHeap[scapeGoat]->mLabel, true);

  std::swap(mHeap[goldenChild], mHeap[scapeGoat]);

  mPositions[gcPos]->mKey = scapeGoat;
  mPositions[sgPos]->mKey = goldenChild;
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
  int c = getPositionOfLabel(label, false);
  mHeap[c]->mKey = key;
  mHeap[c]->mPrev = prev;
  bubbleUp(c);
}


void MinHeap::insert(Node* x) {
  mHeap.push_back(x);
  Node *posNode = new Node(x->mLabel, numElements());
  mPositions.push_back(posNode);
  bubbleUp(numElements());
}


void MinHeap::makeHeap(const std::vector<Node*> &S) {
  for (int c = 0; c < S.size(); c++ ) {
    mHeap.push_back(S[c]);

    Node *posNode = new Node(S[c]->mLabel, c+1);
    mPositions.push_back(posNode);
  }

  for (int j = numElements(); j > 0; j--)
    siftDown(j);
}


int MinHeap::deleteMin() {
  if (isEmpty()) {
    std::cerr << "Trying to delete top element of empty heap. Exiting." << std::endl;
    exit(1);
  }

  int minLabel = mHeap[1]->mLabel;
  mPositions[getPositionOfLabel(minLabel, true)]->mKey = -1;

  swapPositions(1, numElements());
  mHeap.pop_back();

  siftDown(1);
  return minLabel;
}
