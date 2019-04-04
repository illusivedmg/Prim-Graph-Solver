#pragma once

#include <algorithm>
#include <iostream>
#include "MinHeap.h"


class Graph {
public:
  Graph() {};
  Graph(int numV, bool dir);

  virtual ~Graph() {};

  void addEdge(int source, int dest, int weight);

protected:
  struct Edge {
    Edge(int dest, int weight);
    ~Edge();

    int mDest, mCost;
    Edge* mNext = NULL;
  };

  struct EdgeList {
    ~EdgeList();

    Edge* mHead = NULL;
  };

  int mNumVertices;
  std::vector<EdgeList*> mEdgeLists;

private:
  bool mDirected;
};

std::istream& operator>>(std::istream& is, Graph G);


class Prim : private Graph {
public:
  Prim(Graph G, int start, std::string fname);

  ~Prim();

  // add a vertex to MST w/ prev and cost values
  // then update mQ w/ values of vertices it can reach
  void addToMST(MinHeap::Node* toAdd);

  void solve();

  int printSolution(bool path, bool sort, bool silent);

private:
  int mStart, mMSTSize;
  std::string mFileName;

  // mQ -> label = vertex num; key = best distance from a vtx in MST
  MinHeap* mQ;
  std::vector<MinHeap::Node*> mNodeList;

  // Vertices. ID is index in Set vector.
  struct MSTNode {
    int mPrev = -1;
    int mCost = INT_MAX;
    bool mInMST = false;
  };

  std::vector<MSTNode*> mMSTSet;

};