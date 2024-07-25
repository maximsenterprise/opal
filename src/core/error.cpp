// error.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "core/error.hpp"
#include "shared.hpp"
#include "utils.hpp"
#include <iostream>

void error(const std::string &message, int line, const std::string &part) {
    std::cout << "Error found in source at file: " << Shared::program->name
              << " line: " << line << std::endl;

    std::string conflicting =
        split(Shared::program->contents, '\n')->at(line - 1);
    std::string line_minus;
    try {
        line_minus = split(Shared::program->contents, '\n')->at(line - 2);
    } catch (std::out_of_range) {
        line_minus = "";
    }
    std::string tildes;
    for (size_t i = 0; i < part.length(); i++) {
        tildes += "^";
    }

    int start = conflicting.find(part);
    for (int i = 0; i < start; i++) {
        tildes += " ";
    }

    std::cout << "|\t" << line_minus << std::endl;
    std::cout << "|\t" << conflicting << std::endl;
    std::cout << "|\t" << tildes << std::endl;

    std::cout << "\033[31m" << message << std::endl;
    std::cout << "\033[0m";
    exit(1);
}

void panic(const std::string &message, int line) {
    std::cout << "opal panicked at file: " + Shared::program->name +
                     " at line: " + std::to_string(line)
              << std::endl;
    std::cout << message << std::endl;
    exit(1);
}

void success(const std::string &message) {
    std::cout << "\033[32m" << "\033[1m" << message << "\033[0m" << std::endl;
}
