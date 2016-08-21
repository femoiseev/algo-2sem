//
// Created by Teodor Moiseev on 09.05.16.
//

#include "CPosition.h"

#include <iostream>

int main()
{
    short N;
    std::cin >> N;
    std::vector<short> data;
    for(int i = 0; i < N*N; i++) {
        short val;
        std::cin >> val;
        data.push_back(val);
    }
    CPosition pos(N, data);
    pos.PrintSolution(pos);

    return 0;
}