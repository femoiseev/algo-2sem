//
// Created by Teodor Moiseev on 09.05.16.
//
#pragma once
#include <cstring>
#include <vector>

class CSchedule {
public:
    CSchedule(size_t N) : size(N), nodes(N, nullptr)
    {
        for(size_t i = 0; i < N; i++) {
            nodes[i] = new CNode(i);
        }
    }
    ~CSchedule() {
        for(int i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
    }
    void AddEdge(size_t start, size_t end, int start_time, int end_time); // Добавление рейсас

    int FindShortestWay(size_t start, size_t end, int start_time); // Поиск кратчайшего пути

private:
    static int day_length; // Длина дня
    struct CEdge;
    struct CNode { // Станция
        CNode() : number(0) {}
        CNode(size_t N) : number(N), time(-1) {}
        size_t number; // Номер станции
        int time; // Время, затраченное на поездку до данной станции
        std::vector<CEdge*> edges;
        bool operator<(const CNode& t) {
            if(this->time < t.time) {
                return true;
            } else {
                return this->number < t.number;
            }
        }
    };
    struct CEdge { // Рейс автобуса
        CEdge(int st, int et, CNode* e) : start_time(st), end_time(et), end(e) {}
        int start_time; // Время выезда
        int end_time; // Время приезда
        CNode* end; // Конечная станция
    };
    size_t size; // Количество станций
    std::vector<CNode*> nodes; // Вектор станций
};

