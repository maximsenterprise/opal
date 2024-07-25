// nodes.h
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef NODES_H
#define NODES_H

#include "lexer/tokens.hpp"
#include <string>
#include <vector>

class Node {
  public:
    Token token;
    std::string raw_value;
    Node(Token token, std::string raw_value)
        : token(token), raw_value(raw_value) {}
    virtual void out() const;
    virtual ~Node();
};

class NumericLiteral : public Node {
  public:
    NumericLiteral(Token token, std::string raw_value)
        : Node(token, raw_value) {}
    bool is_integer;
    float value;
};

class StringLiteral : public Node {
  public:
    StringLiteral(Token token, std::string raw_value)
        : Node(token, raw_value) {}
};

class Literal : public Node {
  public:
    Literal(Token token, std::string raw_value) : Node(token, raw_value) {}
};

class Operation : public Node {
  public:
    Operation(Token token, std::string raw_value) : Node(token, raw_value) {}
    std::vector<Token> values;
    void out() const override;
};

class Type : public Node {
  public:
    Token *sample_token;
    Type(Token token, std::string raw_value);
};

class Other : public Node {
  public:
    Other(Token token, std::string raw_value) : Node(token, raw_value) {}
    void out() const override;
};

std::vector<Node> parse(std::vector<Token> tokens);
Token eat(std::vector<Token> *tokens);
Token expect(std::vector<Token> *tokens, TokenType type);

#endif // NODES_H
