// lexer.hpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef LEXER_HPP
#define LEXER_HPP

#include "lexer/tokens.hpp"
#include <string>
#include <vector>

std::vector<Token> tokenize(const std::string &source);

#endif // LEXER_HPP
