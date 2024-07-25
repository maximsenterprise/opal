// component.hpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include <string>
#include <vector>

class Component {
  public:
    Token *token;
    Node *node;
    std::string cpp_translation;
};

Node eat(std::vector<Node> *nodes);

Node expect_token_type(std::vector<Node> *nodes, TokenType type);

std::vector<Component> compile(std::vector<Node> nodes, bool inside_method);

#endif // COMPONENT_HPP
