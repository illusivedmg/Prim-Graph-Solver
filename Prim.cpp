#include "Prim.h"


Graph::Edge::Edge(int dest, int cost) 
 : mDest(dest), mCost(cost) {
  
}


Graph::Edge::~Edge() {
  delete mNext;
}


Graph::EdgeList::~EdgeList() {
  delete mHead;
}


Graph::Graph(int numV, bool dir)
 : mNumVertices(numV), mDirected(dir) {
   mEdgeLists.push_back(NULL); // 1-index

  EdgeList* newEL;
  for (int C = 0; C < mNumVertices; C++) {
    newEL = new EdgeList();
    mEdgeLists.push_back(newEL);
  }
}


void Graph::addEdge(int source, int dest, int cost) {
  Edge* newE = new Edge(dest, cost);
  newE->mNext = mEdgeLists[source]->mHead;
  mEdgeLists[source]->mHead = newE;

  if (!mDirected) {
    newE = new Edge(source, cost);
    newE->mNext = mEdgeLists[dest]->mHead;
    mEdgeLists[dest]->mHead = newE;
  }
}


std::istream& operator>>(std::istream& is, Graph G) {
  int src, dest, cost;

  while (is >> src >> dest >> cost)
    G.addEdge(src, dest, cost);

	return is;
}


Prim::Prim(Graph G, int start, std::string fname)
 : Graph(G), mStart(start), mFileName(fname) {
   mMSTSize = 0;
   mMSTSet.push_back(NULL); // 1-index

  for (int C = 0; C < mNumVertices; C++) {
    MSTNode* newMN = new MSTNode();
    mMSTSet.push_back(newMN);

    MinHeap::Node* newN = new MinHeap::Node(C+1);
    mNodeList.push_back(newN);
  }

  mQ = new MinHeap();
  mQ->makeHeap(mNodeList);

  MinHeap::Node startNode = MinHeap::Node(mStart, -1, 0);
  addToMST(&startNode);
}


Prim::~Prim() {
  delete mQ;

  for (auto node : mNodeList)
    delete node;

  for (auto node : mMSTSet)
    delete node;

  for (auto list : mEdgeLists)
    delete list;
}


void Prim::addToMST(MinHeap::Node* toAdd) {
  int u = toAdd->mLabel;
  mMSTSet[u]->mInMST = true;
  mMSTSet[u]->mPrev = toAdd->mPrev;
  mMSTSet[u]->mCost = toAdd->mKey;
  mMSTSize++;

  Edge* edgeFinder =  mEdgeLists[u]->mHead;
  while (edgeFinder) {
    int v = edgeFinder->mDest;
    
    if (!mMSTSet[v]->mInMST) {
      int vDist = edgeFinder->mCost;
      if (vDist < mQ->getKey(v))
        mQ->decreaseKey(v, vDist, u);
    }
    edgeFinder = edgeFinder->mNext;
  }
}


void Prim::solve() {
  while (mMSTSize < mNumVertices)
    addToMST(mQ->deleteMin());
}


int Prim::printSolution(bool sort, bool path, bool silent) {
  if (sort) {
    std::cout << "Sorting MST Solution Set By Source, Ascending" << std::endl;
    std::sort(mMSTSet.begin(), mMSTSet.end(), [](MSTNode* a, MSTNode* b) {
        return a->mPrev < b->mPrev;
    });
  }

  if (path) {
    std::cout << "Minimum Spanning Tree:" << std::endl;
    std::cout << "Starting from: " << mStart << std::endl;
  }

  int totalCost = 0;
  for (int C = 1; C < mMSTSet.size(); C++) {
    totalCost += mMSTSet[C]->mCost;
    if (path)
      std::cout << "From: " << mMSTSet[C]->mPrev << ", To: " << C << ", Cost: " << mMSTSet[C]->mCost << std::endl;
  }

  if (!silent)
    std::cout << "Total Cost for: " << mFileName.c_str() << ": " << totalCost << std::endl;

  return totalCost;
}