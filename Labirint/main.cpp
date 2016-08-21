#include "Labirint.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    int N;
    std::cin >> N;
    CLabirint lab(N);
    std::string str;
    std::getline(std::cin, str);
    for(int i = 0; i < N; i++) {
        std::getline(std::cin, str);
        std::stringstream stream(str);
        while(true) {
            if(!stream) {
                break;
            }
            int start = 0;
            int end = 0;
            stream >> start >> end;
            for(int j = start; j < end; j++) {
                lab.SetWall(j, i);
            }
        }
    }
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    int len = lab.FindShortestPath(x1, y1, x2, y2);

    std::cout << len << std::endl;

    return 0;
}