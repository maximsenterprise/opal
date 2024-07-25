/*
 data.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: The data statement
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"
#include <string>
#include <vector>

Component *data_statement(std::vector<Node> *nodes) {
    Node name = expect_token_type(nodes, TokenType::Identifier);
    // data occupation -> h | b | c;

    expect_token_type(nodes, TokenType::Right_Arrow);

    std::vector<std::string> members;
    while (nodes->size() > 0) {
        Node member = expect_token_type(nodes, TokenType::Identifier);
        if (nodes->at(0).token.type == TokenType::Semicolon) {
            members.push_back(member.token.value);
            eat(nodes);
            break;
        } else if (nodes->at(0).token.type == TokenType::Bar) {
            members.push_back(member.token.value);
            eat(nodes);
        } else {
            error("Invalid data declaration", member.token.line,
                  member.token.value);
        }
    }

    Shared::enums[name.token.value] = members;

    Component *c = new Component();
    c->token = &name.token;
    c->node = &name;

    c->cpp_translation = "enum class " + name.token.value + " {\n";
    for (std::string member : members) {
        c->cpp_translation += member + ",\n";
    }
    c->cpp_translation += "};\n";

    return c;
}
