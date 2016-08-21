//
// Created by Teodor Moiseev on 09.05.16.
//

#include "CPosition.h"

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stdlib.h>

struct comp { // Компаратор для указателей на позиции
    bool operator() (CPosition* x, CPosition* y) { // Минимальный элемент - сверху
        return (*y) < (*x);
    }
};

int CPosition::h() // Эвристика - сумма манхэттенских расстояний для всех костяшек до их целевой позиции
{
    int res = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(field[i][j] != 0) {
                res += (abs(i - (field[i][j]-1)/size) + abs(j - (field[i][j]-1)%size));
            }
        }
    }
    return res;
}


void CPosition::PrintSolution(CPosition &pos) {
    if(!checkSolutionExist(pos)) { // Если решения нет, то прерываемся
        std::cout << "Not solvable" << std::endl;
        return;
    }
    std::priority_queue<CPosition*, std::vector<CPosition*>, comp> queue; // Приоритетная очередь по эвристике
    std::vector<CPosition*> positions; // Рассмотренные позиции
    positions.push_back(&pos);
    queue.push(&pos);
    std::map<CPosition, int> f; // Значение эвристики для рассмотренных позиций
    pos.f = pos.h();
    f.insert(f.begin(), std::make_pair(pos, pos.f));

    while(!queue.empty()) { // Пока очередь не пуста
        CPosition* current = queue.top(); // Достаем элемент с минимальным значением эвристики
        queue.pop();
        if(current->f == 0) { // Если он целевой
            CPosition* root = restoreSolutionTree(current); // То восстанавливаем решение
            printSolutionTree(root);
            break;
        }
        for(int i = -1; i <= 1; i++) { // Перебираем все позиции, достигаемые из данной
            for(int j = -1; j <= 1; j++) {
                int newx = current->nullX + i;
                int newy = current->nullY + j;
                if(newx >= 0 && newx < pos.size && newy >= 0 && newy < pos.size &&
                        !(i == 0 && j == 0) && !(abs(i) == 1 && abs(j) == 1)) {
                    std::vector<std::vector<short>> new_field(current->field);
                    std::swap(new_field[current->nullY][current->nullX], new_field[newy][newx]);
                    CPosition* new_pos = new CPosition(pos.size, new_field);

                    if(f.find(*new_pos) == f.end()) { // если она еще не была рассмотрена, то добавляем ее
                        int new_f = new_pos->h();
                        f.insert(f.begin(), std::make_pair(*new_pos, new_f));
                        new_pos->parent = current;
                        new_pos->f = new_f;
                        positions.push_back(new_pos);
                        queue.push(new_pos);
                    }
                }
            }
        }
    }
    for(size_t i = 1; i < positions.size(); i++) { // Удаляем рассмотренные вершины
        delete positions[i];
    }
}


CPosition* CPosition::restoreSolutionTree(CPosition *pos) { // Восстановление решения
    if(pos->parent != nullptr) { // Если позиция не начальная
        pos->parent->child = pos; // То устанавливаем в отце сына
        return restoreSolutionTree(pos->parent); // И идем в отца
    } else {
        return pos; //  Иначе возвращаем начальную позицию
    }
}


void CPosition::printSolutionTree(CPosition *pos) {
    if(pos->child != nullptr) { // Если позиция не конечная
        if(pos->nullX == pos->child->nullX) { // Печатаем соответствующее действие перехода
            switch(pos->nullY - pos->child->nullY) {
                case 1: std::cout << "D" << std::endl; break;
                case -1: std::cout << "U" << std::endl; break;
                default: std::cout << "Error" << std::endl; break;
            }
        }
        else {
            switch(pos->nullX - pos->child->nullX) {
                case 1: std::cout << "R" << std::endl; break;
                case -1: std::cout << "L" << std::endl; break;
                default: std::cout << "Error" << std::endl; break;
            }
        }
        printSolutionTree(pos->child); // И переходим к сыну
    }
}


bool CPosition::checkSolutionExist(CPosition &pos) {
    int inv = 0;
    std::vector<short> data(size_t(pos.size*pos.size), -1);
    for(short i = 0; i < pos.size; i++) {
        for(short j = 0; j < pos.size; j++) {
            data[i*pos.size+j] = pos.field[i][j];
        }
    }

    for(short i = 0; i < data.size(); i++) { // Считаем сумму количества инверсий и номера строки пустой костяшки (если размер четный)
        if(data[i]) {
            for(short j = 0; j < i; j++) {
                if(data[i] < data[j]) {
                    ++inv;
                }
            }
        }
        else if (pos.size % 2 == 0){
            inv += i/pos.size;
        }
    }

    return (inv + pos.size)%2 == 1; // Если совпадает по четности с размером, то решение есть
}

