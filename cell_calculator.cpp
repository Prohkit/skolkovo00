#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "cell_calculator.h"

std::vector<std::vector<std::string> > getTable(const std::string &token) {
    // получение заголовка, первой строки
    std::ifstream file(token, std::ios::in);
    std::string input;

    std::getline(file, input);

    size_t pos = input.find(',');
    std::string token1;

    std::vector<std::string> vec;
    vec.emplace_back();
    input.erase(0, pos + 1);
    while ((pos = input.find(',')) != std::string::npos) {
        token1 = input.substr(0, pos);
        vec.push_back(token1);
        input.erase(0, pos + 1);
    }
    vec.push_back(input);
    std::vector<std::vector<std::string> > table(0, std::vector<std::string>());
    table.push_back(vec);
    // читает строки из стрима file в строку input
    while (file >> input) {
        std::stringstream ss(input);
        std::string token;
        std::vector<std::string> line;
        // сохраняем таблицу в вектор векторов
        for (int i = 0; getline(ss, token, ','); i++) {
            if (i == 0) {
                line.push_back(token);
                continue;
            }
            line.push_back(token);
        }
        table.push_back(line);
    }
    file.close();
    return table;
}

// есть ли знак равенства перед значением
std::string checkEqualChar(const std::string &token) {
    std::string result = token;
    if (token.compare(0, 1, "=") == 0) {
        result = token.substr(1, token.size() - 1);
    }
    return result;
}

int getColumnIndexFromCell(const std::vector<std::vector<std::string> > &table, const std::string &token) {
    int k = 0;
    while (!isdigit(token[k])) {
        k++;
    }
    std::string columnName = token.substr(0, k);
    int columnIndex = 0;
    for (int t = 1; t < table[0].size(); ++t) {
        if (table[0][t] == columnName) {
            columnIndex = t;
            break;
        }
    }
    return columnIndex;
}

int getLineIndexFromCell(const std::vector<std::vector<std::string> > &table, const std::string &token) {
    int k = 0;
    while (!isdigit(token[k])) {
        k++;
    }
    int delimitIndex = k;
    while (isdigit(token[k])) {
        k++;
    }
    std::string lineName = token.substr(delimitIndex, k);
    int lineIndex;
    for (int t = 1; t < table.size(); ++t) {
        if (table[t][0] == lineName) {
            lineIndex = t;
            break;
        }
    }
    return lineIndex;
}

std::string calculateCell(std::vector<std::vector<std::string> > &table, const std::string &token, const int i, const int j) {

    std::string result = checkEqualChar(token);

    std::string first_arg;
    std::string second_arg;
    char operation;
    bool flag = false;

    // Для случая выражения (ARG1 OP ARG2) (п. 4 алгоритма)
    for (int k = 0; k < result.length(); k++) {
        if (result[k] == '+' || result[k] == '-' || result[k] == '*' || result[k] == '/') {

            first_arg = result.substr(0, k);
            second_arg = result.substr(k + 1, result.length());
            operation = result[k];
            flag = true;
            break;
        }
    }
    std::string cellValue;
    if (flag) {
        int a = stoi(calculateCell(table, first_arg, i, j));
        int b = stoi(calculateCell(table, second_arg, i, j));
        switch (operation) {
            case '+':
                calculateCell(table, std::to_string(a + b), i, j);
                break;
            case '-':
                calculateCell(table, std::to_string(a - b), i, j);
                break;
            case '*':
                calculateCell(table, std::to_string(a * b), i, j);
                break;
            case '/':
                calculateCell(table, std::to_string(a / b), i, j);
                break;
        }
        return "";

        // п.2 алгоритма
    } else if (!isdigit(result[0])) {
        do {
            int lineIndex = getLineIndexFromCell(table, result);
            int columnIndex = getColumnIndexFromCell(table, result);
            cellValue = table[lineIndex][columnIndex];

            cellValue = checkEqualChar(cellValue);
            if (!isdigit(cellValue[0])) {
                calculateCell(table, cellValue, lineIndex, columnIndex);
            }
            std::vector<std::string> currentLineToSave = table[i];
            currentLineToSave.at(j) = cellValue;
            table.at(i) = currentLineToSave;
        } while (!isdigit(cellValue[0]));
        return cellValue;
    } else {
        // число записать (п. 3 алгоритма)
        std::vector<std::string> currentLine = table[i];
        currentLine.at(j) = result;
        table.at(i) = currentLine;
        return result;
    }
}
