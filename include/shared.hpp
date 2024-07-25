// shared.h
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef SHARED_H
#define SHARED_H

#include "compiler/component.hpp"
#include "lexer/tokens.hpp"
#include "program.hpp"
#include <map>
#include <string>
#include <vector>

class Shared {
  public:
    static Program *program;
    static std::map<std::string, TokenType> keywords;
    static std::map<std::string, Token *> sampleTokens;
    static std::map<TokenType, std::string> tokenNames;
    static std::vector<std::string> types;
    static std::vector<std::string> modules;
    static std::map<std::string, std::vector<std::string>> enums;
    static std::map<std::string, Component *> structs;
};

#endif // SHARED_H
