//
// Created by Teodor Moiseev on 09.05.16.
//

#include <vector>

class CPosition {
public:
    CPosition(short N, std::vector<short> data):
            size(N), field(N, std::vector<short>(N, -1)), f(0),
            parent(nullptr), child(nullptr)
    {
        for(short i = 0; i < N*N; i++) {
            field[i/size][i%size] = data[i];
            if(data[i] == 0) {
                nullX = i%size;
                nullY = i/size;
            }
        }
    }
    CPosition(short N, std::vector<std::vector<short>> data):
            size(N), f(0), parent(nullptr), child(nullptr), field(data)
    {
        for(short i = 0; i < N; i++) {
            for(short j = 0; j < N; j++) {
                if(field[i][j] == 0) {
                    nullY = i;
                    nullX = j;
                }
            }
        }
    }
    bool operator<(const CPosition& another) const{
        if(this->f < another.f)
            return true;
        return this->field < another.field;
    } // Компаратор для позиций (упорядочивает по возрастанию эвристики)
    static void PrintSolution(CPosition& pos); // Нахождени и печать решения
private:
    int f; // Значение эвристики для данной вершины (пройденный путь мы не учитываем)
    short nullX; // Координаты пустой костяшки
    short nullY;
    short size; // Размер поля
    CPosition* parent; // Позиция, из которой была получена данная
    CPosition* child; // Позиция, которая была получена из данной (в ветке правильного решения)
    std::vector<std::vector<short>> field; // Игровое поле
    static CPosition* restoreSolutionTree(CPosition* pos); // Восстановление ветки правильного решения
    static void printSolutionTree(CPosition* pos); // Печать правильного решения
    int h(); // Эвристическая функция для позиции (сумма манхеттенских расстояний всех костяшек до нужной им позиции
    static bool checkSolutionExist(CPosition& pos); // Проверка существования решения
};

