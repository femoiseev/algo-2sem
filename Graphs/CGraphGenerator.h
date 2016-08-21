//
// Created by Teodor Moiseev on 17.04.16.
//
#pragma once

#include "CGraph.h"

#include <iostream>

template <typename T, typename M>
class CGraphGenerator {
public:
    static CGraph<T, M>* GenerateUndirectedGraph(size_t num_of_vertex); // Генерируем граф на заданном числе ребер.
};

template <typename T, typename M>
CGraph<T, M> *CGraphGenerator<T, M>::GenerateUndirectedGraph(size_t num_of_vertex) {
    srand(time(NULL));
    int num_of_edges = 0;
    CGraph<T, M>* graph = new CGraph<T, M>();
    for(int i = 0; i < num_of_vertex; i++) {
        graph->AddVertex(); // Добавляем вершину.
        for(int j = 0; j < i; j++) {
            if(!(rand() % 100)) { // Проверяем, надо ли добавить ребро.
                num_of_edges++;
                graph->AddUndirectedEdge(j, i); // Если надо, добавляем.
            }
        }
    }
    std::cout << num_of_edges << std::endl;
    return graph;
}
