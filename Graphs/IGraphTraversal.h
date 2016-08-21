//
// Created by Teodor Moiseev on 11.04.16.
//

#pragma once

#include "CGraph.h"

enum Colors { // Цвета вершин.
    WHITE, GRAY, BLACK
};

template <typename T, typename M>
class IGraphTraversal { // Обход графа.
public:
    IGraphTraversal() {}
    virtual ~IGraphTraversal() {};
    virtual void StartTraversal() = 0; // Начало обхода.
};

