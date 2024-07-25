// procedure.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "utils.hpp"
#include <iostream>
#include <map>
#include <string>

Component *procedure_declaration(std::vector<Node> *nodes) {
    Node name = expect_token_type(nodes, TokenType::Identifier);
    expect_token_type(nodes, TokenType::OpenParenthesis);
    std::map<std::string, std::string> arguments;

    while (nodes->size() > 0) {
        if (nodes->at(0).token.type == TokenType::ClosingParenthesis) {
            eat(nodes);
            break;
        } else {
            Node arg = eat(nodes);
            expect_token_type(nodes, TokenType::As);
            Node type = expect_token_type(nodes, TokenType::Type);
            arguments[arg.raw_value] =
                transpile_types(new Type(type.token, type.raw_value));
            if (nodes->at(0).token.type == TokenType::Comma) {
                eat(nodes);
            } else if (nodes->at(0).token.type ==
                       TokenType::ClosingParenthesis) {
                eat(nodes);
                break;
            } else {
                error("Invalid arguments for a procedure", arg.token.line,
                      arg.raw_value);
            }
        }
    }

    expect_token_type(nodes, TokenType::OpenBrace);
    std::vector<Node> body;
    int level = 1;
    while (nodes->size() > 0) {
        if (nodes->at(0).token.type == TokenType::ClosingBrace) {
            level--;
            if (level == 0) {
                eat(nodes);
                break;
            } else {
                body.push_back(eat(nodes));
            }
        } else if (nodes->at(0).token.type == TokenType::OpenBrace) {
            level++;
            body.push_back(eat(nodes));
        } else {
            body.push_back(eat(nodes));
        }
    }

    Component *component = new Component();
    component->token = &name.token;
    component->node = &name;
    component->cpp_translation = "void " + name.raw_value + "(";
    for (auto &arg : arguments) {
        if (arg.first == "*this") {
            component->cpp_translation += "*this, ";
            continue;
        }
        component->cpp_translation += arg.second + " " + arg.first + ", ";
    }
    if (arguments.size() > 0) {
        component->cpp_translation.pop_back();
        component->cpp_translation.pop_back();
    }
    component->cpp_translation += ") {\n";
    for (Component &c : compile(body, false)) {
        component->cpp_translation += c.cpp_translation + "\n";
    }
    component->cpp_translation += "}\n";
    return component;
}
