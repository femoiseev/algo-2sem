#include "CSchedule.h"
#include <iostream>
#include <cstring>
#include <sstream>

int main() {
    size_t N = 0;
    std::cin >> N;
    CSchedule* schedule = new CSchedule(N);
    std::string str;
    std::getline(std::cin, str);
    for(size_t i = 0; i < N; i++) {
        std::getline(std::cin, str);
        std::stringstream stream(str);
        size_t end = 0;
        int start_time = 0;
        int end_time = 0;
        stream >> end >> start_time >> end_time;
        while(true) {
            if(!stream) {
                break;
            }
            schedule->AddEdge(i, end, start_time, end_time);
            stream >> end >> start_time >> end_time;
        }
    }
    size_t start_point = 0;
    size_t end_point = 0;
    int begin_time = 0;
    std::cin >> start_point >> end_point >> begin_time;
    int res = schedule->FindShortestWay(start_point, end_point, begin_time);
    std::cout << res << std::endl;

    delete schedule;

    return 0;
}