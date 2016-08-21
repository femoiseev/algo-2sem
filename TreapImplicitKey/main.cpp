#include "CImplicitTreap.h"
#include "CSimpleVector.h"
#include "CTestSequence.h"

#include <iostream>


int main()
{
    CImplicitTreap treap;

    CSimpleVector v;

    IImplicitTree* first = &treap;
    IImplicitTree* second = &v;

    CTestSequence tests(5000000, 1000000);


    clock_t start = 0;
    clock_t end = 0;

    start = clock();
    std::vector<long long> treapres = tests.RunTests(first);
    end = clock();
    std::cout << "ImplicitTreap time: " << end - start << std::endl;

    start = clock();
    std::vector<long long> vectorres = tests.RunTests(second);
    end = clock();
    std::cout << "Vector time: " << end - start << std::endl;

    int errors = 0;
    for(int i = 0; i < vectorres.size(); i++) {
        if(treapres[i] != vectorres[i]) {
            errors++;
        }
    }

    std::cout << errors << std::endl;

    return 0;
}