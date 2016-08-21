//
// Created by Teodor Moiseev on 07.05.16.
//

#pragma once

#include <vector>
#include <stdlib.h>


class CLabirint { // Лабиринт
public:
    CLabirint(int n) :
            size(n)
    {
        field = new std::vector<std::vector<bool>>(n, std::vector<bool>(n, true));
    }
    ~CLabirint() {
        delete field;
    }
    void SetWall(int x, int y) { // Установить препятствие в точку (x, y)
        (*field)[x][y] = false;
    }

    int FindShortestPath(int x1, int y1, int x2, int y2); // Найти кратчайший путь из вершины (x1, y1) в (x2, y2)

private:
    struct CPoint {
        CPoint(int _x, int _y, int _f) :
                x(_x), y(_y), f(_f)
        {}
        friend class CLabirint;
        int x; // Координаты вершины
        int y;
        int f; // Значение эвристики для данной точки
        friend bool operator<(const CPoint& lhs, const CPoint& rhs) {
            if(lhs.f < rhs.f) {
                return true;
            } else if (lhs.f == rhs.f){
                if(lhs.x < rhs.x) {
                    return true;
                }
                if(lhs.y < rhs.y) {
                    return true;
                }
            }
            return false;
        }
    };
    int size; // Сторона лабиринта
    std::vector<std::vector<bool>>* field; // Сам лабиринт
    int h(int x1, int y1, int x2, int y2) { // Предполагаемый кратчайший путь из вершины (x1, y1) в (x2, y2)
        return abs(x1 - x2) + abs(y1 - y2);
    }
    int h(CPoint p1, CPoint p2) { // Предполагаемый кратчайший путь между вершинами p1 и p2
        return abs(p1.x - p2.x) + abs(p1.y-p2.y);
    }
};


