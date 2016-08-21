#pragma once

#include "IImplicitTree.h"

#include <vector>

class CSimpleVector : public IImplicitTree {
public:
    long long GetRangeSum(long long int left, long long int right); // Запрос суммы на подотрезке.
    void Insert(long long int pos, unsigned int val); // Вставка элемента в позицию.
    void Set(long long int pos, unsigned int val); // Изменение значения элемента по позиции.
    bool NextPermutation(long long int left, long long int right); // Следующая в лексикографическом порядке перестановка на подотрезке.
    void Show(); // Вывод значений элементов по порядку.
private:
    std::vector<int> ar; // Вектор значений.
};

