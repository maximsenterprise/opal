// error.h
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef ERROR_H
#define ERROR_H

#include <string>

void error(const std::string &message, int line, const std::string &part);
void panic(const std::string &message, int line);
void success(const std::string &message);

#endif // ERROR_H
