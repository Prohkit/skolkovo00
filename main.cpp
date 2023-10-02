#include <map>
#include <vector>
#include "iostream"
#include "cell_calculator.h"

int main(int argc, char *argv[]) {

    std::vector<std::vector<std::string> > table = getTable(argv[1]);

    // вычисляем значения ячеек в таблице (п. 1 алгоритма)
    for (int i = 0; i < table.size(); ++i) {
        std::vector<std::string > currentLine = table[i];
        for (int j = 0; j < table[i].size(); ++j) {
            if (i == 0 | j == 0) {
                continue;
            }
            std::string token = currentLine[j];
            std::string result = calculateCell(table, token, i, j);
        }
    }

    // вывод из таблицы
    for (int i = 0; i < table.size(); ++i) {
        std::vector<std::string> line = table[i];
        for (int j = 0; j < line.size(); ++j) {
            std::cout << line[j] << ',';
        }
        std::cout << '\n';
    }
}