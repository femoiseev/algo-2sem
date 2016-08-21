#include <iostream>
#include "MatrixGraph.h"

int main() {
    size_t N;
    std::cin >> N;
    CMatrixGraph graph(N);
    double val;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < i; j++) {
            std::cin >> val;
            graph.ChangeValue(i, j, val);
        }
        for(size_t j = i+1; j < N; j++) {
            std::cin >> val;
            graph.ChangeValue(i, j, val);
        }
    }
    //graph.Print();
    bool isTA = graph.IsTradeArbitrage();
    if(isTA) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}