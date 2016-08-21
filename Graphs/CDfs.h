//
// Created by Teodor Moiseev on 16.04.16.
//

#pragma once

#include "IGraphTraversal.h"

template <typename T, typename M>
class CDfs : public IGraphTraversal<T, M> { // Поиск в глубину.
public:
    CDfs(CGraph<T, M>* g) :
            graph(g)
    {
        colors.resize(graph->GetSize(), Colors::WHITE);
    }
    ~CDfs() {}

    void StartTraversal(); // Начало обхода.
    bool CheckCorrectness() const; // Проверка, что все вершины покрашены.

protected:
    virtual void onColorGray(size_t number) // Событие при покраске вершины в серый цвет.
    {}
    virtual void onColorBlack(size_t number) // Событие при покраске вершины в черный цвет.
    {}
    virtual void dfs(const CNode<T, M>* node); // Обход в глубину из данной вершины.
    CGraph<T, M>* graph; // Граф, по которому делаем обход.
    std::vector<Colors> colors; // Цвета вершин.
};

template <typename T, typename M>
void CDfs<T, M>::StartTraversal() { // Начало обхода.
    for(int i = 0; i < graph->GetSize(); i++) {
        if(colors[i] == Colors::WHITE) { // Если вершина белая.
            dfs(graph->GetNode(i)); // Запускаем поиск в глубину от нее.
        }
    }
}

template <typename T, typename M>
void CDfs<T, M>::dfs(const CNode<T, M> *node) {
    colors[node->GetNumber()] = Colors::GRAY; // Красим вершину в серый.
    onColorGray(node->GetNumber());
    const std::list<CEdge<T, M>>& successors = node->GetSuccessors(); // Получаем список смежности.
    auto edge = successors.begin();
    auto end = successors.end();
    for (; edge != end; ++edge) { // Перебираем соседей.
        if(colors[edge->GetEnd()->GetNumber()] == Colors::WHITE) { // Если сосед белый.
            dfs(edge->GetEnd()); // Запускаем поиск в глубину от нее.
        }
    }
    colors[node->GetNumber()] = Colors::BLACK; // Красим вершину в черный.
    onColorBlack(node->GetNumber());
}

template <typename T, typename M>
bool CDfs<T, M>::CheckCorrectness() const {
    for(int i = 0; i < graph->GetSize(); i++) {
        if(colors[i] != Colors::BLACK) {
            return false;
        }
    }
    return true;
}
