#include "CImplicitTreap.h"

#include <iostream>



CImplicitTreap::~CImplicitTreap()
{
    delete root;
}

void CImplicitTreap::Insert(long long pos, unsigned int val)
{
    CNode::insert(root, pos, val);
}

void CImplicitTreap::Set(long long pos, unsigned int val)
{
    CNode::set(root, pos, val);
}

long long CImplicitTreap::GetRangeSum(long long int l, long long int r)
{
    CNode* left = nullptr;
    CNode* mid = nullptr;
    CNode* right = nullptr;
    CNode::split(root, left, right, r + 1); // Вырезаем интересующий нас подотрезок.
    CNode::split(left, left, mid, l);
    long long res = mid->subtreesum; // Возвращаем значение суммы в его корне.
    left = CNode::merge(left, mid); // Сливаем обратно.
    root = CNode::merge(left, right);
    return res;
}

bool CImplicitTreap::NextPermutation(long long int l, long long int r)
{
    CNode* left = nullptr;
    CNode* mid = nullptr;
    CNode* right = nullptr;
    CNode::split(root, left, right, r + 1); // Вырезаем интересующий нас подотезок.
    CNode::split(left, left, mid, l);
    bool res = CNode::nextPermutation(mid); // Переставляем его в следующую перестановку.
    left = CNode::merge(left, mid); // Сливаем обратно.
    root = CNode::merge(left, right);
    return res;
}

CImplicitTreap::CNode::~CNode()
{
    if(left != nullptr) {
        delete left;
    }
    if(right != nullptr) {
        delete right;
    }
}

void CImplicitTreap::CNode::insert(CNode *&t, long long int pos, unsigned int v)
{
    CNode* left = nullptr;
    CNode* right = nullptr;
    CNode* newnode = new CNode(v); // Создаем дерево из одной вершины с переданным значением.
    split(t, left, right, pos); // Разрезаем по переданной позиции.
    left = merge(left, newnode); // Сливаем левую часть с новой вершиной.
    t = merge(left, right); // Сливаем с правой частью.
}

CImplicitTreap::CNode * CImplicitTreap::CNode::merge(CNode *left, CNode *right)
{
    if(left == nullptr) {
        return right;
    }
    if(right == nullptr) {
        return left;
    }
    if(left->priority < right->priority) { // Если приоритет в корне левого поддерева меньше,
        left->push();
        left->right = merge(left->right, right); // то сливаем правое поддерево с правым сыном левого.
        recalc(left);
        return left;
    }
    else {
        right->push();
        right->left = merge(left, right->left); // Иначе сливаем левое поддерево с левым сыном правого.
        recalc(right);
        return right;
    }
}

bool CImplicitTreap::CNode::nextPermutation(CNode *&t)
{
    if(getSize(t) == getNonIncrPostfix(t)) { // Если перестановка максимальна.
        t->isReversed = !t->isReversed; // Разворачиваем массив.
        return false; // Новая перестановка меньше предыдущей.
    }
    CNode* left = nullptr;
    CNode* pivot = nullptr;
    CNode* right = nullptr;
    split(t, left, right, getSize(t) - getNonIncrPostfix(t) - 1); // Отрезаем невозрастающий постфикс.
    split(right, pivot, right, 1); // Отрезаем пивот - самый правый элемент не из невозрастающего постфикса.
    CNode* right1 = nullptr;
    CNode* right2 = nullptr;
    CNode* rms = nullptr;
    splitByVal(right, right1, right2, pivot->val); // Разрезаем полученный постфикс по значению пивота.
    split(right1, right1, rms, getSize(right1) - 1); // Отрезаем самый правый элемент со значением больше пивота.
    std::swap(pivot->val, rms->val); // Меняем его значение со значением пивота.
    recalc(pivot);
    recalc(rms);
    right1 = merge(right1, rms); // Сливаем обратно постфикс.
    right = merge(right1, right2);
    right->isReversed = !right->isReversed; // Переворачиваем его.
    left = merge(left, pivot); // Сливаем с пивотом и левой частью.
    t = merge(left, right);
    return true;
}

void CImplicitTreap::CNode::set(CNode *&t, long long int pos, unsigned int v)
{
    CNode* left = nullptr;
    CNode* right = nullptr;
    CNode* mid = nullptr;
    split(t, left, right, pos); // Вырезаем элемент на нужной позиции.
    split(right, mid, right, 1);
    mid->val = v; // Меняем его значение.
    recalc(mid);
    left = merge(left, mid); // Сливаем обратно.
    t = merge(left, right);
}

void CImplicitTreap::CNode::split(CNode *t, CNode *&leftres, CNode *&rightres, long long k)
{
    if(t == nullptr) {
        leftres = nullptr;
        rightres = nullptr;
        return;
    }
    t->push();
    if(k <= getSize(t->left)) { // Если элемены, которые нужно отрезать, лежат в левом поддереве,
        split(t->left, leftres, t->left, k); // то разрезаем левое поддерево.
        rightres = t;
    }
    else {
        split(t->right, t->right, rightres, k - getSize(t->left) - 1); // Иначе разрезаем правое поддерево.
        leftres = t;
    }
    recalc(leftres);
    recalc(rightres);
}

void CImplicitTreap::CNode::push()
{
    if(isReversed) { // Если поддерево нужно перевернуть.
        std::swap(left, right); // То меняем  местами противоположный значения.
        std::swap(nonIncrPostfix, nonDecrPrefix);
        std::swap(leftval, rightval);
        if(left != nullptr) { // Проталкиваем бит перевернутости в детей.
            left->isReversed = !left->isReversed;
        }
        if(right != nullptr) {
            right->isReversed = !right->isReversed;
        }
        isReversed = false; // Мы выполнили разворот.
    }
}

void CImplicitTreap::CNode::recalc(CNode *&t)
{
    if(t != nullptr) {
        t->push(); // Проталкиваем бит перевернутости во внуков.
        if(t->left != nullptr) {
            t->left->push();
        }
        if(t->right != nullptr) {
            t->right->push();
        }
        t->subtreesum = t->val + getSubTreeSum(t->left) + getSubTreeSum(t->right); // Пересчитываем сумму значений элементов в поддереве.
        t->nonDecrPrefix = getNonDecrPrefix(t->left); // Пересчитываем значение неубывающего префикса.
        if(getNonDecrPrefix(t->left) == getSize(t->left)) {
            if(getRightVal(t->left) <= t->val || t->left == nullptr) {
                t->nonDecrPrefix++;
                if(t->val <= getLeftVal(t->right)) {
                    t->nonDecrPrefix += getNonDecrPrefix(t->right);
                }
            }
        }
        t->nonIncrPostfix = getNonIncrPostfix(t->right); // Пересчитываем значение невозрастающего постфикса.
        if(getNonIncrPostfix(t->right) == getSize(t->right)) {
            if(t->val >= getLeftVal(t->right) || t->right == nullptr) {
                t->nonIncrPostfix++;
                if(getRightVal(t->left) >= t->val) {
                    t->nonIncrPostfix += getNonIncrPostfix(t->left);
                }
            }
        }
        if(t->left != nullptr) { // Обновляем самое левое значение в поддереве.
            t->leftval = t->left->leftval;
        }
        else {
            t->leftval = t->val;
        }
        if(t->right != nullptr) { // Обновляем самое правое значение в поддереве.
            t->rightval = t->right->rightval;
        }
        else {
            t->rightval = t->val;
        }
        t->size = getSize(t->left) + getSize(t->right) + 1; // Пересчитываем размер поддерева.
    }
}

long long int CImplicitTreap::CNode::getSubTreeSum(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->subtreesum;
    }
}

long long CImplicitTreap::CNode::getNonDecrPrefix(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->nonDecrPrefix;
    }
}

long long CImplicitTreap::CNode::getNonIncrPostfix(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->nonIncrPostfix;
    }
}

long long CImplicitTreap::CNode::getSize(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->size;
    }
}

unsigned int CImplicitTreap::CNode::getLeftVal(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->leftval;
    }
}

unsigned int CImplicitTreap::CNode::getRightVal(CNode *t)
{
    if(t == nullptr) {
        return 0;
    }
    else {
        return t->rightval;
    }
}

void CImplicitTreap::Show()
{
    CNode::show(root);
}

void CImplicitTreap::CNode::show(CNode *t)
{
    if(t != nullptr) { // Совершаем in-order обход.
        t->push();
        show(t->left);
        std::cout << t-> val << " ";
        show(t->right);
    }
}

void CImplicitTreap::CNode::splitByVal(CNode *t, CNode *&leftres, CNode *&rightres, int val)
{
    if(t == nullptr) {
        leftres = nullptr;
        rightres = nullptr;
        return;
    }
    t->push();
    if(t->val <= val) { // Если значени в корне меньше либо равно,
        splitByVal(t->left, leftres, t->left, val); // То разрезаем левое поддерево.
        rightres = t;
    }
    else {
        splitByVal(t->right, t->right, rightres, val); // Иначе разрезаем правое.
        leftres = t;
    }
    recalc(leftres);
    recalc(rightres);
}