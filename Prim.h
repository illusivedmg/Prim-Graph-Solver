#pragma once

#include <climits>
#include <algorithm>
#include "MinHeap.h"


struct Edge {
  Edge(int dest, int weight);

  Edge* getNext() { return mNext; }

  void setNext(Edge* e) { mNext = e; }

  int getDestination() { return mDestination; }

  int getWeight() { return mWeight; }

private:
  int mDestination, mWeight;
  Edge* mNext;
};


struct EdgeList {
  EdgeList();

  ~EdgeList();

  Edge* getHead() { return mHead; }

  void setHead(Edge* nh) { mHead = nh; }

private:
  Edge* mHead;
};


// num vertices, directed or not, vec of linked list of edges per vertex
struct Graph {
  Graph(bool dir);
  Graph(int numV, bool dir);

  ~Graph();

  void initEdges();

  void addEdge(int source, int dest, int weight);

  int getNumVertices() { return mNumVertices; }
  void setNumVertices(int numV) { mNumVertices = numV; }

  Edge* getStartingEdge(int i) { return mEdgeLists[i-1]->getHead(); }

  std::istream& operator>>( std::istream& is );

private:
  std::vector<EdgeList*> mEdgeLists;
  int mNumVertices;
  bool mDirected;
};


// Vertice in graph, included in MST when prev is nonnull. Dist is cost of incoming edge.
struct MSTNode {
  MSTNode(int vtx)
  : mVertexNum(vtx) {}

  bool mInMST = false;
  int mVertexNum;
  int mPrev = -1;
  int mDist = INT_MAX;
};


struct Prim {
  Prim(Graph* G, int start, std::string fname);

  ~Prim();

  void addToMST(int vertex);

  // once vertex added, update edge values to lightest
  void updateMSTValues(int vertex, int prev, int dist);

  void solve();

  int printSolution(bool path, bool sort, bool silent);

private:
  Graph* mGraph;
  Edge* mNextEdge;
  Node* mNewNode;
  std::vector<Node*> mNodeList;
  MinHeap* mQ;

  int mNumVertices, c, u, v, vDist, mStart, mMSTSize;
  MSTNode* mNewMSTNode;
  std::vector<MSTNode*> mMSTSet;
  std::string mFileName;
};