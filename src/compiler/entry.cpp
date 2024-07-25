/*
 entry.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Main point for the Transpiler
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"
#include <iostream>
#include <string>
#include <vector>

std::vector<Component> compile(std::vector<Node> nodes, bool running_method) {
    std::vector<Component> components;
    std::cout << "Compiling " << nodes.size() << " nodes" << std::endl;
    while (nodes.size() > 0) {
        Node node = nodes[0];

        switch (node.token.type) {
        case TokenType::Val:
            eat(&nodes);
            components.push_back(*variable_declaration(&nodes));
            break;
        case TokenType::Procedure:
            eat(&nodes);
            components.push_back(*procedure_declaration(&nodes));
            break;
        case TokenType::Method:
            eat(&nodes);
            components.push_back(*method_declaration(&nodes));
            break;
        case TokenType::Identifier:
            components.push_back(*function_call(&nodes));
            break;
        case TokenType::Res:
            eat(&nodes);
            components.push_back(*save_statement(&nodes));
            break;
        case TokenType::If:
            eat(&nodes);
            components.push_back(*if_statements(&nodes, running_method));
            break;
        case TokenType::Data:
            eat(&nodes);
            components.push_back(*data_statement(&nodes));
            break;
        case TokenType::Class:
            eat(&nodes);
            components.push_back(*class_statement(&nodes));
            break;
        case TokenType::Apply:
            eat(&nodes);
            apply_statement(&nodes, &components);
            break;
        case TokenType::Cpp:
            components.push_back(*cpp_statement(&nodes));
            break;
        case TokenType::Struct:
            eat(&nodes);
            components.push_back(*struct_statement(&nodes));
            break;
        case TokenType::At:
            eat(&nodes);
            if (nodes.at(0).token.type != TokenType::Identifier) {
                error("Invalid macro call", nodes.at(0).token.line,
                      nodes.at(0).token.value);
            }
            if (nodes.at(0).token.value == "include") {
                eat(&nodes);
                components.push_back(*include_macro(&nodes));
            } else {
                error("Invalid macro call", nodes.at(0).token.line,
                      nodes.at(0).token.value);
            }
            break;
        case TokenType::Return:
            if (!running_method) {
                error("Return statement found outside of method",
                      node.token.line, node.token.value);
                exit(1);
            }
            eat(&nodes);
            components.push_back(*return_statement(&nodes));
            break;
        case TokenType::OpenBracket:
            eat(&nodes);
            components.push_back(*template_args(&nodes));
            break;
        default:
            error("Invalid code found in source of type " +
                      Shared::tokenNames[node.token.type],
                  node.token.line, node.token.value);
            exit(1);
        }
    }

    return components;
}

Node eat(std::vector<Node> *nodes) {
    Node node = nodes->at(0);
    nodes->erase(nodes->begin());
    return node;
}

Node expect_token_type(std::vector<Node> *nodes, TokenType type) {
    if (nodes->at(0).token.type != type) {
        error("Expected type " + Shared::tokenNames[type] + " but got type " +
                  Shared::tokenNames[nodes->at(0).token.type],
              nodes->at(0).token.line, nodes->at(0).token.value);
        exit(1);
    } else {
        return eat(nodes);
    }
}
