#pragma once

#include "IImplicitTree.h"
#include <ctime>
#include <iostream>
#include <utility>

class CImplicitTreap : public IImplicitTree {
public:
    CImplicitTreap(): root(nullptr)
    {
        std::srand(time(NULL));
    };
    ~CImplicitTreap();
    long long GetRangeSum(long long int left, long long int right); // Запрос суммы на подотрезке.
    void Insert(long long pos, unsigned  int val); // Вставка элемента в позицию.
    void Set(long long pos, unsigned int val); // Изменение значение элемента в позиции.
    bool NextPermutation(long long int left, long long int right); // Следующая в лексикографическом порядке перестановка на подотрезке.
    void Show(); // Вывод на экран по порядку.
private:
    class CNode {// Узел дерева.
    public:
        int priority; // Приоритет.
        CNode(unsigned int v): val(v), size(1), left(nullptr), subtreesum(v),
                      right(nullptr), leftval(v), rightval(v),
                      isReversed(false), nonIncrPostfix(1), nonDecrPrefix(1)
        {
            priority = rand();
        }
        ~CNode();
        long long size; // Размер поддерева.
        unsigned int val; // Значение в вершине.
        CNode* left; // Левый сын.
        CNode* right; // Правый сын.
        bool isReversed; // Необходимо ли развернуть поддерево.
        long long nonIncrPostfix; // Длина невозрастающего постфикса.
        long long nonDecrPrefix; // Длина неубывающего префикса.
        unsigned int leftval; // Значение самого левого элемента в поддереве.
        unsigned int rightval; // Значение самого правого элемента в поддереве.
        long long subtreesum; // Сумма значений элементов в поддереве.
        static void split(CNode *t, CNode *&left, CNode *&right, long long pos); // Разрезание по позиции.
        static void splitByVal(CNode *t, CNode *&left, CNode *&right, int val); // Разрезание по значению (если значения в поддереве отсортированы по убыванию ключей).
        static CNode* merge(CNode *left, CNode *right); // Слияние даух деревьев.
        static void insert(CNode *&t, long long int pos, unsigned int v); // Вставка элемента в позицию.
        static void set(CNode *&t, long long int pos, unsigned int v); // Изменение значение элемента в поддереве по позиции.
        static bool nextPermutation(CNode *&t); // Следующая в лексикографическом порядке перестановка элементов поддерева.
        void push(); // Проталкивание бита перевернутости.
        static void recalc(CNode *&t); // Пересчет значений на основе значений в детях.
        static long long getSubTreeSum(CNode *t); // Запрос суммы элементов поддерева.
        static long long getNonIncrPostfix(CNode *t); // Запрос длины невозрастающего постфикса.
        static long long getNonDecrPrefix(CNode *t); // Запрос длины неубывающего префикса.
        static long long getSize(CNode *t); // Запрос размера поддерева.
        static unsigned int getLeftVal(CNode *t); // Запрос значения левого элемента в поддереве.
        static unsigned int getRightVal(CNode *t); // Запрос значения правого элемента в поддереве.
        static void show(CNode *t); // Вывод элементов поддерева на экран по порядку.
    };
    CNode* root; // Корень дерева.
};


