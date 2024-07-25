// save.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "utils.hpp"
#include <map>
#include <string>

Component *save_statement(std::vector<Node> *nodes) {
    std::map<std::string, std::string> variables;
    Node first = nodes->at(0);
    while (!nodes->empty()) {
        if (nodes->at(0).token.type == TokenType::Semicolon) {
            break;
        } else if (nodes->at(0).token.type == TokenType::Identifier) {
            std::string var_name = eat(nodes).token.value;

            if (nodes->at(0).token.type == TokenType::LessThan) {
                eat(nodes);
                Node type = eat(nodes);
                variables[var_name] =
                    transpile_types(new Type(type.token, type.token.value));
                expect_token_type(nodes, TokenType::GreaterThan);
                if (nodes->at(0).token.type == TokenType::Comma) {
                    eat(nodes);
                }
            } else if (nodes->at(0).token.type == TokenType::Comma) {
                eat(nodes);
                variables[var_name] = "auto";
            } else {
            }
        } else {
            error("Invalid res statement", nodes->at(0).token.line,
                  nodes->at(0).token.value);
        }
    }

    expect_token_type(nodes, TokenType::Semicolon);

    Component *c = new Component();
    c->token = &first.token;
    c->node = &first;
    for (auto &var : variables) {
        c->cpp_translation += var.second + " " + var.first + ";\n";
    }
    return c;
}
