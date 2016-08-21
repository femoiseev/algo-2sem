//
// Created by Teodor Moiseev on 17.04.16.
//

#pragma once

#include "IGraphTraversal.h"
#include <stack>

template <typename T, typename M>
class CStackDfs : public IGraphTraversal<T, M> { // Обход в глубину без использования рекурсии.
public:
    CStackDfs(CGraph<T, M>* g) :
            graph(g)
    {
        colors.resize(graph->GetSize(), Colors::WHITE);
    }
    ~CStackDfs() {}

    void StartTraversal(); // Начало обхода.
    bool CheckCorrectness() const; // Проверка корректности.

protected:
    virtual void onColorGray(size_t number) // Событие при покраске вершины в серый цвет.
    {}
    virtual void onColorBlack(size_t number) // Событие при покраске вершины в черный цвет.
    {}
    virtual void dfs(); // Поиск в глубину.
    CGraph<T, M>* graph; // граф, по которому выполняется обход.
    std::vector<Colors> colors; // Цвета вершин.
    std::stack<const CNode<T, M>*> stack; // Стек вызова поиска в глубину.
};

template <typename T, typename M>
void CStackDfs<T, M>::StartTraversal() { // Начало обхода.
    for(int i = 0; i < graph->GetSize(); i++) { // Перебираем все вершины,
        if(colors[i] == Colors::WHITE) { // Если вершина белая, то
            stack.push(graph->GetNode(i)); // Добавляем ее в стек,
            colors[i] = Colors::GRAY; // Красим ее в серый.
            onColorGray(i);
            dfs(); // Запускаем поиск в глубину.
        }
    }
}

template <typename T, typename M>
void CStackDfs<T, M>::dfs() { // Поиск в глубину.
    while(!stack.empty()) { // Пока стек не пуст,
        const CNode<T, M>* node = stack.top(); // Смотрим на вершину наверху стека.
        const std::list<CEdge<T, M>> &successors = node->GetSuccessors(); // Получаем список смежности.
        auto edge = successors.begin();
        auto end = successors.end();
        bool isWhiteChild = false;
        for (; edge != end; ++edge) { // Перебираем всех ее соседей.
            CNode<T, M>* end = edge->GetEnd();
            if (colors[end->GetNumber()] == Colors::WHITE) { // Если сосед белый, то
                stack.push(end); // Помещаем его в стек,
                colors[end->GetNumber()] = Colors::GRAY; // Красим его в серый,
                onColorGray(edge->GetEnd()->GetNumber());
                isWhiteChild = true; // Помечаем, что у вершины были белые дети.
                break;
            }
        }
        if(!isWhiteChild) { // Если белых детей не было, то все соседи обработаны.
            colors[node->GetNumber()] = Colors::BLACK; // Красим вершину в черный
            onColorBlack(node->GetNumber());
            stack.pop(); // Выталкиваем вершину из стека.
        }
    }
}

template <typename T, typename M>
bool CStackDfs<T, M>::CheckCorrectness() const {
    for(int i = 0; i < graph->GetSize(); i++) {
        if(colors[i] != Colors::BLACK) { // Проверяем, что все вершины черные.
            return false;
        }
    }
    return true;
}