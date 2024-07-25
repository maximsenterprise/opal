// program.h
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>

class Program {
  public:
    Program(std::string contents, std::string name);
    ~Program();
    void run();
    std::string name;
    std::string contents;
};

#endif // PROGRAM_H
