#include "MinHeap.h"
#include "Prim.h"
#include <ctime>
#include <fstream>
#include <chrono>

std::vector<std::string> files = {"graph-10-1.txt", "graph-10-2.txt", "graph-10-3.txt", "graph-10-4.txt", "graph-100-1.txt", "graph-100-2.txt", "graph-100-3.txt", "graph-100-4.txt", "graph-1000-1.txt", "graph-1000-2.txt", "graph-1000-3.txt", "graph-1000-4.txt", "graph-10000-1.txt", "graph-10000-2.txt", "graph-10000-3.txt", "graph-10000-4.txt", "graph-100000-1.txt", "graph-100000-2.txt", "graph-100000-3.txt", "graph-100000-4.txt", "graph-20000-1.txt", "graph-20000-2.txt", "graph-20000-3.txt", "graph-20000-4.txt", "graph-200000-1.txt", "graph-200000-2.txt", "graph-200000-3.txt", "graph-200000-4.txt", "graph-40000-1.txt", "graph-40000-2.txt", "graph-40000-3.txt", "graph-40000-4.txt", "graph-400000-1.txt", "graph-400000-2.txt", "graph-400000-3.txt", "graph-400000-4.txt", "graph-80000-1.txt", "graph-80000-2.txt", "graph-80000-3.txt", "graph-80000-4.txt", "graph-800000-1.txt", "graph-800000-2.txt", "graph-800000-3.txt", "graph-800000-4.txt"};


int main(int argc, char **argv) {

  for (auto filename : files) {
    std::ifstream fin(filename.c_str());
    Graph G = Graph(false);
    G >> fin;
    fin.close(); 

    int reps = 1;
    int n = G.getNumVertices();
    // if (n == 10)
    //   reps = 100000;
    // if (n == 100)
    //   reps = 1000;
    // if (n == 1000)
    //   reps = 10;

    Prim* P;
    // std::cout << n << ", " << reps << std::endl;
    clock_t t1 = clock();
    for (int c = 0; c < reps; c++) {
      P = new Prim(&G, 1, filename);
      P->solve();
      P->printSolution(false, false, true);
    }
    clock_t t2 = clock();
    clock_t dt = t2 - t1;
    double clocks_per_rep = ((double)dt)/reps;
    double seconds = clocks_per_rep/CLOCKS_PER_SEC;
    delete P;
  
    std::cout << n << ", " << seconds << std::endl;
  }
  return 0;
}