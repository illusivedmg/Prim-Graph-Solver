#include "Prim.h"


Edge::Edge(int dest, int weight) 
 : mDestination(dest), mWeight(weight) {
    mNext = NULL;
}


EdgeList::EdgeList() { 
  mHead = NULL; 
}


EdgeList::~EdgeList() {
  Edge* curr = mHead;
  Edge* next = NULL;
  while (curr) {
    next = curr->getNext();
    delete curr;
    curr = next;
  }
}


Graph::Graph(bool dir)
 : mDirected(dir) {

}


Graph::Graph(int numV, bool dir)
 : mNumVertices(numV), mDirected(dir) {
  initEdges();
}


Graph::~Graph() {
  for (auto list : mEdgeLists)
    delete list;
}


void Graph::addEdge(int source, int dest, int weight) {
  Edge* newE = new Edge(dest, weight);
  newE->setNext(mEdgeLists[source-1]->getHead());
  mEdgeLists[source-1]->setHead(newE);

  if (!mDirected) {
    newE = new Edge(source, weight);
    newE->setNext(mEdgeLists[dest-1]->getHead());
    mEdgeLists[dest-1]->setHead(newE);
  }
}


void Graph::initEdges() {
  EdgeList* newEL;
  for (int c = 0; c < mNumVertices; c++) {
    newEL = new EdgeList();
    mEdgeLists.push_back(newEL);
  }
}


std::istream& Graph::operator>>( std::istream& is ) {
	int numV;
  is >> numV;
  setNumVertices(numV);
  initEdges();
	
  int src, dest, weight;
  while (is >> src >> dest >> weight)
    addEdge(src, dest, weight);

	return is;
}


Prim::Prim(Graph* G, int start, std::string fname)
 : mGraph(G), mStart(start), mFileName(fname) {
  mNumVertices = mGraph->getNumVertices();
  mMSTSize = 0;

  for (c = 1; c <= mNumVertices; c++) {
    mNewNode = new Node(c, INT_MAX);
    mNodeList.push_back(mNewNode);

    mNewMSTNode = new MSTNode(c);
    mMSTSet.push_back(mNewMSTNode);
  }

  mQ = new MinHeap();
  mQ->makeHeap(mNodeList);
}


Prim::~Prim() {
  delete mQ;

  for (auto node : mNodeList)
    delete node;

  for (auto node : mMSTSet)
    delete node;
}


void Prim::addToMST(int vertex) {
  mMSTSize++;
  mMSTSet[vertex-1]->mInMST = true;
}


void Prim::updateMSTValues(int vertex, int prev, int dist) {
  mMSTSet[vertex-1]->mPrev = prev;
  mMSTSet[vertex-1]->mDist = dist;
  mQ->decreaseKey(vertex, dist, prev);
}


void Prim::solve() {
  updateMSTValues(mStart, -1, 0);
  do {
    u = mQ->deleteMin();
    addToMST(u);

    mNextEdge = mGraph->getStartingEdge(u);
    while (mNextEdge) {
      v = mNextEdge->getDestination();
      vDist = mNextEdge->getWeight();
      
      if (!mMSTSet[v-1]->mInMST && vDist < mMSTSet[v-1]->mDist) {
        updateMSTValues(v, u, vDist);
      }
      
      mNextEdge = mNextEdge->getNext();
    }
  } while (mMSTSize < mGraph->getNumVertices() - 1);
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
    std::cout << "Vertex: Distance" << std::endl;
  }

  int totalCost = 0;
  for (auto node : mMSTSet) {
    totalCost += node->mDist;
    if (path)
      std::cout << "From: " << node->mPrev << ", To: " << node->mVertexNum << ", Cost: " << node->mDist << std::endl;
  }
  if (!silent)
    std::cout << "Total Cost for  " << mFileName << ": " << totalCost << std::endl;
  return totalCost;
}