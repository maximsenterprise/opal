// return.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "parser/nodes.hpp"
#include <vector>

Component *return_statement(std::vector<Node> *nodes) {
    Node node = eat(nodes);
    Component *component = new Component();
    component->node = &node;
    component->token = &node.token;
    component->cpp_translation = "return " + node.raw_value + ";\n";
    expect_token_type(nodes, TokenType::Semicolon);
    return component;
}
