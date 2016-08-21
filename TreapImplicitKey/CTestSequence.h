#pragma once

#include "IImplicitTree.h"

#include <vector>

class CTestSequence
{
public:
    CTestSequence(int N, unsigned int range); // В конструкторе генерируется последовательность тестов.
    std::vector<long long> RunTests(IImplicitTree*& x); // Запуск сгенерированных тестов от реализации интерфейса.
private:
    enum Type { Insert, GetRangeSum, Set, NextPermutation};
    struct Test
    {
        Test(Type t, long long p1, long long p2, unsigned int v) :
            type(t), pos1(p1), pos2(p2), val(v)
        {}
        Type type; // Тип операции.
        long long pos1; // Первая позиция.
        long long pos2; // Вторая позиция.
        unsigned int val; // Значение.
    };
    std::vector<Test> tests; // Сгенерированные тесты.
    int N; // Количество тестов.
    unsigned int range; // Диапазон значений.
};

