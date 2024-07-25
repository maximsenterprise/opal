/*
 template.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Template statement
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include <iostream>
#include <string>
#include <vector>

Component *template_args(std::vector<Node> *nodes) {
    Node first = nodes->at(0);
    std::string template_args = {};
    while (nodes->size() > 0) {
        std::cout << "HERE" << std::endl;
        if (nodes->at(0).token.type == TokenType::ClosingBracket) {
            eat(nodes);
            break;
        }
        template_args += eat(nodes).raw_value + " ";
    }

    Component *component = new Component();
    component->cpp_translation = "template <";
    component->cpp_translation += template_args;
    component->cpp_translation += ">\n";
    component->node = &first;
    component->token = &first.token;
    return component;
}
