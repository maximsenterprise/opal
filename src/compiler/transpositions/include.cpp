/*
 include.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Include low level macro
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "parser/nodes.hpp"

Component *include_macro(std::vector<Node> *nodes) {
    expect_token_type(nodes, TokenType::OpenParenthesis);
    Node file = expect_token_type(nodes, TokenType::String);
    expect_token_type(nodes, TokenType::ClosingParenthesis);

    Component *c = new Component();
    c->token = &file.token;
    c->node = &file;
    c->cpp_translation = "#include " + file.raw_value + "\n";
    return c;
}
