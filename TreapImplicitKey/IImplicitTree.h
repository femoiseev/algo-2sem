#pragma once
// Интерфейс дерева по неявному ключу.
class IImplicitTree {
public:
    virtual ~IImplicitTree() {}
    virtual long long GetRangeSum(long long int left, long long int right) = 0; // Запрос суммы на подотрезке.
    virtual void Insert(long long int pos, unsigned int val) = 0; // Вставка элемента в позицию.
    virtual void Set(long long int pos, unsigned int val) = 0; // Изменение значения элемента по позиции.
    virtual bool NextPermutation(long long int left, long long int right) = 0; // Следующая в лексикографическом порядке перестановка на подотрезке.
    virtual void Show() = 0; // Вывод значений элементов по порядку.
};

