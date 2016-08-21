//
// Created by Teodor Moiseev on 07.05.16.
//

#include "Labirint.h"
#include <climits>
#include <set>

int CLabirint::FindShortestPath(int x1, int y1, int x2, int y2) {
    // Текущие кратчайшие пути до вершин
    std::vector<std::vector<int>>* g = new std::vector<std::vector<int>>(size, std::vector<int>(size, INT_MAX));
    // Значения эвристики для вершин
    std::vector<std::vector<int>>* f = new std::vector<std::vector<int>>(size, std::vector<int>(size, INT_MAX));
    // Были ли вершины помечены
    std::vector<std::vector<bool>>* marked = new std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
    // Сет вершин для посещения
    std::set<CPoint> closed;
    (*g)[x1][y1] = 0;
    (*f)[x1][y1] = h(x1, y1, x2, y2);
    CPoint start(x1, y1, (*f)[x1][y1]);
    closed.insert(start); // Вставл]ем 1-ю вершину

    while(closed.size() != 0) { // Пока сет не пуст
        auto current = *closed.begin(); // Берем из него минимум
        if(current.x == x2 && current.y == y2) { // Если он совпадает с целью, то возвращем длину пути до него
            return current.f;
        }
        closed.erase(closed.begin());
        (*marked)[current.x][current.y] = true;
        if(current.x == 2 && current.y == 1) {

        }
        for(int i = -1; i <= 1; i++) { // Перебираем соседние точки
            for(int j = -1; j <= 1; j++) {
                int newx = current.x + i;
                int newy = current.y + j;
                if(newx == 2 && newy == 3) {

                }
                // Если надо, добавляем точку в сет с нужными значениями эвристики
                if(newx >= 0 && newx < size && newy >= 0 && newy < size && !(i == 0 && j == 0) && !(abs(i) == 1 && abs(j) == 1)) {
                    if((*field)[newx][newy]) {
                        int tentativeScore = (*g)[current.x][current.y] + 1;
                        if(!(*marked)[newx][newy] || tentativeScore < (*g)[newx][newy]) {

                            (*g)[newx][newy] = tentativeScore;
                            (*f)[newx][newy] = tentativeScore + h(newx, newy, x2, y2);
                            CPoint newpoint(newx, newy, (*f)[newx][newy]);
                            closed.erase(newpoint);
                            closed.insert(newpoint);
                        }
                    }
                }
            }
        }
    }

    delete f;
    delete g;
    delete marked;

    return -1;
}
