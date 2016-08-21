//
// Created by Teodor Moiseev on 07.05.16.
//

#include "MatrixGraph.h"

bool CMatrixGraph::IsTradeArbitrage() { // Алгоритм Форда-Беллмана
    std::vector<bool> marked(size, false);
    for(size_t t = 0; t < size; t++) {
        if(!marked[t]) {
            marked[t] = true;
            std::vector<double> d(size, 0); // Вектор лучших коэффициентов обмена валюты t на валюту с индексом i
            d[t] = 1;
            for (size_t k = 0; k < size - 1; k++) { // Делаем size-1 итераций
                for (int i = 0; i < size; i++) { // Перебираем все пары
                    for (int j = 0; j < size; j++) {
                        if (d[j] < d[i] * (*matrix)[i][j]) { // Обновляем лучший коэффициент, если нужно
                            marked[j] = true;
                            d[j] = d[i] * (*matrix)[i][j];
                        }
                    }
                }
            }
            for (int i = 0; i < size; i++) { // Делаем еще одну итерацию
                for (int j = 0; j < size; j++) {
                    if (d[j] < d[i] * (*matrix)[i][j]) { // Если значения изменились, то арбитраж есть
                        return true;
                    }
                }
            }
        }
    }
    return false;
}