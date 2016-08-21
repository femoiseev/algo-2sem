#include "CSimpleVector.h"

#include <algorithm>
#include <iostream>

long long CSimpleVector::GetRangeSum(long long int l, long long int r)
{
    long long res = 0;
    for(long long i = l; i <= r; i++) {
        res += ar[i];
    }
    return res;
}

void CSimpleVector::Insert(long long int pos, unsigned int val)
{
    ar.insert(ar.begin() + pos, val);
}

bool CSimpleVector::NextPermutation(long long int left, long long int right)
{
    return std::next_permutation(ar.begin() + left, ar.begin() + right + 1);
}

void CSimpleVector::Set(long long int pos, unsigned int val)
{
    ar[pos] = val;
}

void CSimpleVector::Show()
{
    for( auto el : ar) {
        std::cout << el << " ";
    }
}