#include "CTestSequence.h"

#include <iostream>

CTestSequence::CTestSequence(int n, unsigned int r) :
    N(n), range(r)
{
    std::srand(time(NULL));
    Test first(Type::Insert, 0, 0, rand() % range); // Вставляем первый элемент.
    tests.push_back(first);
    long long size = 1;
    for(int i = 1; i < N; i++) {
        int oper = rand() % 4; // Отсальный операции выбираем рандомно.
        switch (oper) {
            case 0: {
                Test test(Type::Insert, rand() % (size + 1), 0, rand() % range);
                tests.push_back(test);
                size++;
                break;
            }
            case 1: {
                Test test(Type::Set, rand() % size, 0, rand() % range);
                tests.push_back(test);
                break;
            }
            case 2: {
                long long right = rand() % size;
                long long left = rand() % (right + 1);
                Test test(Type::GetRangeSum, left, right, 0);
                tests.push_back(test);
                break;
            }
            case 3: {
                long long right = rand() % size;
                long long left;
                if(right == 0) {
                    left = 0;
                }
                else {
                    left = rand() % right;
                }
                Test test(Type::NextPermutation, left, right, 0);
                tests.push_back(test);
                break;
            }
        }
    }
}

std::vector<long long> CTestSequence::RunTests(IImplicitTree *&x)
{
    std::vector<long long> res;
    for(int i = 0; i < N; i++) {
        switch (tests[i].type) {
            case NextPermutation:
                res.push_back(x->NextPermutation(tests[i].pos1, tests[i].pos2));
                break;
            case GetRangeSum:
                res.push_back(x->GetRangeSum(tests[i].pos1, tests[i].pos2));
                break;
            case Insert:
                x->Insert(tests[i].pos1, tests[i].val);
                break;
            case Set:
                x->Set(tests[i].pos1, tests[i].val);
                break;
        }
    }
    return res;
}