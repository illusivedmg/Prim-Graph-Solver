#include "MinHeap.h"
#include "Prim.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>

std::vector<std::string> allFiles = {
  "graph-10-1.txt", "graph-10-2.txt", "graph-10-3.txt", "graph-10-4.txt",
  "graph-100-1.txt", "graph-100-2.txt", "graph-100-3.txt", "graph-100-4.txt",
  "graph-1000-1.txt", "graph-1000-2.txt", "graph-1000-3.txt", "graph-1000-4.txt",
  "graph-10000-1.txt", "graph-10000-2.txt", "graph-10000-3.txt", "graph-10000-4.txt",
  "graph-20000-1.txt", "graph-20000-2.txt", "graph-20000-3.txt", "graph-20000-4.txt",
  "graph-40000-1.txt", "graph-40000-2.txt", "graph-40000-3.txt", "graph-40000-4.txt",
  "graph-80000-1.txt", "graph-80000-2.txt", "graph-80000-3.txt", "graph-80000-4.txt",
  "graph-100000-1.txt", "graph-100000-2.txt", "graph-100000-3.txt", "graph-100000-4.txt",
  "graph-200000-1.txt", "graph-200000-2.txt", "graph-200000-3.txt", "graph-200000-4.txt",
  "graph-400000-1.txt", "graph-400000-2.txt", "graph-400000-3.txt", "graph-400000-4.txt",
  "graph-800000-1.txt", "graph-800000-2.txt", "graph-800000-3.txt", "graph-800000-4.txt"
};


std::vector<std::string> someFiles = {
  "graph-10-1.txt",
  "graph-100-1.txt",
  "graph-1000-1.txt",
  "graph-10000-1.txt",
  "graph-20000-1.txt",
  "graph-40000-1.txt",
  "graph-80000-1.txt",
  "graph-100000-1.txt",
  "graph-200000-1.txt",
  "graph-400000-1.txt",
  "graph-800000-1.txt"
};


int main(int argc, char **argv) {
  // filename as argument, else will run list of files
  if (argc > 1) {
    std::string arg(argv[1]);
    std::stringstream ss(arg);

    std::string filename;
    ss >> filename;

    std::ifstream fin(filename.c_str());

    int numV;
    fin >> numV;

    Graph G = Graph(numV, false); 
    fin >> G;
    fin.close();

    Prim* P = new Prim(G, 1, filename);
    P->solve();
    P->printSolution(false, true, false);
    delete P;

    return 0;
  }

  int numV;
  Graph G;
  Prim* P;
  int reps;

  for (auto filename : allFiles) {
    std::ifstream fin(filename.c_str());

    fin >> numV;

    G = Graph(numV, false); 
    
    int src, dest, cost, numE = 0;

    while (fin >> src >> dest >> cost) {
      G.addEdge(src, dest, cost);
      numE++;
    }

    fin.close(); 

    reps = 10;
    if (numV == 10)
      reps = 1000000;
    if (numV == 100)
      reps = 100000;
    if (numV == 1000)
      reps = 10000;
    if (numV == 10000)
      reps = 100;

    clock_t t1 = clock();
    for (int c = 0; c < reps; c++) {
      P = new Prim(G, 1, filename);
      P->solve();
    }
    clock_t t2 = clock();


    clock_t dt = t2 - t1;
    double clocks_per_rep = ((double)dt)/reps;
    double seconds = clocks_per_rep/CLOCKS_PER_SEC;

    std::cout << numV << ", " << numE << ", " << seconds << std::endl;
  }

  delete P;

  return 0;
}