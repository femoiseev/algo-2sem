//
// Created by Teodor Moiseev on 09.05.16.
//

#include "CSchedule.h"
#include <set>

int CSchedule::day_length = 24;

void CSchedule::AddEdge(size_t start, size_t end, int start_time, int end_time) { // Добавление маршрута.в
    CEdge* new_edge = new CEdge(start_time, end_time, nodes[end]);
    nodes[start]->edges.push_back(new_edge);
}

int CSchedule::FindShortestWay(size_t start, size_t end, int start_time) { // Используем алгоритм Дейкстры
    int res = -1;
    nodes[start]->time = start_time;
    std::set<CNode*> set; // Создаем сет вершин
    set.insert(nodes[start]);
    while(!set.empty()) { // Пока сет не пустой
        CNode* cur = *set.begin(); // Достаем из него минимум
        set.erase(set.begin());
        if(cur->number == end) { // Если это конец, то возвращаем время пути до него
            res = cur->time - start_time;
            break;
        }
        int day_time = cur->time % day_length;
        for(int i = 0; i < cur->edges.size(); i++) { // Иначе перебираем все рейсы из текущей
            CNode* next = cur->edges[i]->end;
            int arrive_time = cur->time;
            arrive_time += (cur->edges[i]->start_time - day_time + day_length) % day_length; // Считаем, сколько времени мы будем ждать выезда
            arrive_time += (cur->edges[i]->end_time - cur->edges[i]->start_time + day_length) % day_length; // Считаем, сколько времени мы будем ехать
            if(arrive_time < next->time || next->time == -1) { // Если надо обновить кратчайший путь, то обновляем
                set.erase(next);
                next->time = arrive_time;
                set.insert(next);
            }
        }
    }
    for(int i = 0; i < nodes.size(); i++) { // Возвращаем граф в исходное состояние
        nodes[i]->time = -1;
    }
    return res;
}