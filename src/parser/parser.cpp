// parser.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include <iostream>
#include <string>
#include <vector>

std::vector<Node> parse(std::vector<Token> tokens) {
    std::vector<Node> nodes;
    while (true) {
        Token t = tokens[0];

        if (t.type == TokenType::EndOfTheFile) {
            break;
        } else if (t.type == TokenType::String) {
            StringLiteral node(t, t.value);
            nodes.push_back(node);
            eat(&tokens);
        } else if (t.type == TokenType::Type) {
            Type node(t, t.value);
            nodes.push_back(node);
            eat(&tokens);
        } else if (t.type == TokenType::Integer || t.type == TokenType::Plus ||
                   t.type == TokenType::Minus || t.type == TokenType::Float ||
                   t.type == TokenType::Multiply ||
                   t.type == TokenType::Divide || t.type == TokenType::Modulo) {
            Operation *op = new Operation(t, t.value);
            while (true) {
                Token t = tokens[0];
                if (t.type == TokenType::EndOfTheFile) {
                    break;
                } else if (t.type == TokenType::Plus ||
                           t.type == TokenType::Minus ||
                           t.type == TokenType::Multiply ||
                           t.type == TokenType::Divide ||
                           t.type == TokenType::Modulo) {
                    op->values.push_back(t);
                    eat(&tokens);
                } else if (t.type == TokenType::Integer) {
                    op->values.push_back(t);
                    eat(&tokens);
                } else if (t.type == TokenType::Float) {
                    op->values.push_back(t);
                    eat(&tokens);
                } else {
                    break;
                }
            }

            if (op->values.size() == 0) {
                panic("Fatal error. Deadline", t.line);
            } else if (op->values.size() == 1) {
                nodes.push_back(NumericLiteral(t, t.value));
            } else {
                nodes.push_back(*op);
            }

        } else {
            nodes.push_back(Other(t, t.value));
            eat(&tokens);
        }
    }

    return nodes;
}
