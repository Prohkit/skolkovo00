#ifndef UNTITLED_CELL_CALCULATOR_H
#define UNTITLED_CELL_CALCULATOR_H

std::string checkEqualChar(const std::string &token);

int getColumnIndexFromCell(const std::vector<std::vector<std::string> > &table, const std::string &token);

int getLineIndexFromCell(const std::vector<std::vector<std::string> > &table, const std::string &token);

std::vector<std::vector<std::string> > getTable(const std::string &token);

std::string
calculateCell(std::vector<std::vector<std::string> > &table, const std::string &token, const int i, const int j);

#endif
