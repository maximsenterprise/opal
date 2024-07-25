// nodes.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "parser/nodes.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "shared.hpp"
#include "utils.hpp"
#include <cstring>
#include <iostream>
#include <string>

Token eat(std::vector<Token> *tokens) {
    Token token = tokens->at(0);
    tokens->erase(tokens->begin());
    return token;
}

Token expect(std::vector<Token> *tokens, TokenType type) {
    Token token = tokens->at(0);
    if (token.type != type) {
        error("Expected type " + Shared::tokenNames[type] + " but got type " +
                  Shared::tokenNames[token.type],
              token.line, token.value);
    }
    tokens->erase(tokens->begin());
    return token;
}

Node::~Node() {}

void Node::out() const {
    std::cout << "Node: " << Shared::tokenNames[token.type] << " " << raw_value
              << std::endl;
}

void Other::out() const {
    std::cout << "Other: " << Shared::tokenNames[token.type] << " " << raw_value
              << std::endl;
}

void Operation::out() const {
    for (Token t : this->values) {
        std::cout << "Operation: " << Shared::tokenNames[t.type] << " "
                  << t.value << std::endl;
    }
}

Type::Type(Token token, std::string raw_value)
    : Node(token, raw_value), sample_token(Shared::sampleTokens[raw_value]) {}
