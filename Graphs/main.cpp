#include "CGraph.h"
#include "CDfs.h"
#include "CBfs.h"
#include "CStackDfs.h"
#include "CGraphGenerator.h"

#include <iostream>

int main()
{
    CGraph<int, int>* graph = CGraphGenerator<int, int>::GenerateUndirectedGraph(1000);
    std::cout << "Graph generated!" << std::endl;
    CBfs<int, int>* bfs = new CBfs<int, int>(graph);
    CStackDfs<int, int>* dfs = new CStackDfs<int, int>(graph);
    bfs->StartTraversal();
    std::cout << bfs->CheckCorrectness() << std::endl;

    dfs->StartTraversal();
    std::cout << dfs->CheckCorrectness() << std::endl;

    delete graph;

    std::cout << "Graph deleted!" << std::endl;
    delete dfs;
    delete bfs;

    return 0;
}