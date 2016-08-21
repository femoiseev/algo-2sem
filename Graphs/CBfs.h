//
// Created by Teodor Moiseev on 16.04.16.
//

#pragma once

#include "IGraphTraversal.h"

#include <queue>



template <typename T, typename M>
class CBfs : public IGraphTraversal<T, M> { // Обход в ширину.
public:
    CBfs(CGraph<T, M>* g) :
            graph(g)
    {
        colors.resize(graph->GetSize(), Colors::WHITE);
    }
    ~CBfs() {}

    void StartTraversal(); // Начало обхода.
    bool CheckCorrectness() const; // Проверка, что все всершины покрашены.

protected:
    virtual void onColorGray(size_t number) // Событие при покраске вершины в серый цвет.
    {}
    virtual void onColorBlack(size_t number) // Событие при покраске вершины в черный цвет.
    {}
    virtual void bfs(); // Поиск в глубину.
    CGraph<T, M>* graph; // Граф, по которому выполняется поиск.
    std::vector<Colors> colors; // Цвета вершин.
    std::queue<const CNode<T, M>*> queue; // Очередь вызова поиска в ширину.
};

template <typename T, typename M>
void CBfs<T, M>::StartTraversal() { // Начало обхода.
    for(int i = 0; i < graph->GetSize(); i++) { // Перебираем вершины.
        if(colors[i] == Colors::WHITE) { // Если вершина белая,
            queue.push(graph->GetNode(i)); // Добавляем вершину в очередь и
            bfs(); // Запускаем поиск в ширину.
        }
    }
}

template <typename T, typename M>
void CBfs<T, M>::bfs() {
    while(!queue.empty()) { // Пока очередб не пуста.
        const CNode<T, M> *node = queue.front(); // Достаем вершину из очереди.
        queue.pop();
        colors[node->GetNumber()] = Colors::BLACK; // Красим ее в черный.
        onColorBlack(node->GetNumber());
        const std::list<CEdge<T, M>> &successors = node->GetSuccessors();
        auto edge = successors.begin();
        auto end = successors.end();
        for (; edge != end; ++edge) { // Бежим по ее соседям.
            const CNode<T, M> *successor = edge->GetEnd();
            if (colors[successor->GetNumber()] == Colors::WHITE) { // Если сосед белый, то
                colors[successor->GetNumber()] = Colors::GRAY; // Красим его в серый.
                onColorGray(successor->GetNumber());

                queue.push(successor); // Кладем ее в очередь.
            }
        }
    }
}

template <typename T, typename M>
bool CBfs<T, M>::CheckCorrectness() const{
    for(int i = 0; i < graph->GetSize(); i++) {
        if(colors[i] != Colors::BLACK) { // Проверяем, что  все вершины покрашены в черный.
            return false;
        }
    }
    return true;
}

