//
// Created by Teodor Moiseev on 07.05.16.
//
#pragma once

#include <vector>
#include <iostream>

class CMatrixGraph {
public:
    CMatrixGraph(size_t n): size(n)
    {
        matrix = new std::vector<std::vector<double>>(n, std::vector<double>(n, -1));
    }
    ~CMatrixGraph()
    {
        delete matrix;
    }
    void ChangeValue(size_t i, size_t j, double val) { // Изменение коэффициента обмена.
        (*matrix)[i][j] = val;
    }
    void Print() {
        for(size_t i = 0; i < size; i++) {
            for(size_t j = 0; j < size; j++) {
                std::cout << (*matrix)[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    bool IsTradeArbitrage();
private:
    size_t size; // Количество валют.
    std::vector<std::vector<double>>* matrix; // Коэффициенты обмена.
};
