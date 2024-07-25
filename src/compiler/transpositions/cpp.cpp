/*
 cpp.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: The C++ macro
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "parser/nodes.hpp"
#include <cstdlib>
#include <vector>

Component *cpp_statement(std::vector<Node> *nodes) {
    Component *component = new Component();
    component->token = &nodes->at(0).token;
    component->node = &nodes->at(0);
    component->cpp_translation = nodes->at(0).raw_value;
    eat(nodes);
    return component;
}
