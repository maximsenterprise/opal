/*
 struct.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Structures for Opal
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"
#include "utils.hpp"
#include <map>
#include <vector>

Component *struct_statement(std::vector<Node> *nodes) {
    Node name = expect_token_type(nodes, TokenType::Identifier);
    expect_token_type(nodes, TokenType::OpenBrace);
    std::map<std::string, std::string> properties;
    while (true) {
        Node var_name = expect_token_type(nodes, TokenType::Identifier);
        if (var_name.token.type == TokenType::Comma) {
            properties[var_name.token.value] = "auto";
            continue;
        } else if (nodes->at(0).token.type == TokenType::LessThan) {
            expect_token_type(nodes, TokenType::LessThan);
            Node type = eat(nodes);
            if (type.token.type == TokenType::Identifier) {
                properties[var_name.token.value] = type.raw_value;
            } else if (type.token.type == TokenType::Type) {
                properties[var_name.token.value] =
                    transpile_types(new Type(type.token, type.token.value));
            } else {
                error("Expected type or identifier", type.token.line,
                      type.token.value);
            }
            expect_token_type(nodes, TokenType::GreaterThan);
            if (nodes->at(0).token.type == TokenType::Comma) {
                eat(nodes);
            } else {
                expect_token_type(nodes, TokenType::ClosingBrace);
                break;
            }
        } else {
            expect_token_type(nodes, TokenType::ClosingBrace);
            break;
        }
    }

    Component *c = new Component();
    c->token = &name.token;
    c->node = &name;
    c->cpp_translation = "struct " + name.token.value + " {\n";
    for (auto val : properties) {
        c->cpp_translation += val.second + " " + val.first + ";\n";
    }
    c->cpp_translation += "};\n";

    Shared::structs[name.token.value] = c;
    return c;
}
