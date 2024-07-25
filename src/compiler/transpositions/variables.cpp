// variables.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

Component *variable_declaration(std::vector<Node> *nodes) {
    if (nodes->at(1).token.type == TokenType::OpenParenthesis) {
        std::vector<Node> function_nodes = {};
        int open_parenthesis = 0;
        while (true) {
            Node node = eat(nodes);
            if (node.token.type == TokenType::OpenParenthesis) {
                open_parenthesis++;
            } else if (node.token.type == TokenType::ClosingParenthesis) {
                open_parenthesis--;
                if (open_parenthesis == 0) {
                    function_nodes.push_back(node);
                    break;
                }
            }
            function_nodes.push_back(node);
        }

        Type *var_type = nullptr;
        expect_token_type(nodes, TokenType::Is);
        Node symbol = expect_token_type(nodes, TokenType::Identifier);
        if (nodes->at(0).token.type == TokenType::LessThan) {
            eat(nodes);
            if (nodes->at(0).token.type == TokenType::Identifier) {
                for (auto item : Shared::enums) {
                    if (item.first == nodes->at(0).raw_value) {
                        Node type =
                            expect_token_type(nodes, TokenType::Identifier);
                        expect_token_type(nodes, TokenType::GreaterThan);
                        var_type = new Type(type.token, type.raw_value);
                        break;
                    }
                }

                if (var_type == nullptr) {
                    error("Invalid enum type", nodes->at(0).token.line,
                          nodes->at(0).raw_value);
                }
            } else {
                Node type = expect_token_type(nodes, TokenType::Type);
                expect_token_type(nodes, TokenType::GreaterThan);
                var_type = new Type(type.token, type.raw_value);
            }
        }
        expect_token_type(nodes, TokenType::Semicolon);
        Component *component = new Component();
        component->token = &symbol.token;
        component->node = &symbol;
        if (var_type == nullptr) {
            Type *type = new Type(symbol.token, "auto");
            component->cpp_translation =
                transpile_types(type) + " " + symbol.raw_value + " = ";
            for (Component c : compile(function_nodes, false)) {
                component->cpp_translation += c.cpp_translation;
            }
        } else {
            component->cpp_translation =
                transpile_types(var_type) + " " + symbol.raw_value + " = ";
            for (Component c : compile(function_nodes, false)) {
                component->cpp_translation += c.cpp_translation;
            }
        }
        return component;
    }

    Node value = eat(nodes);
    expect_token_type(nodes, TokenType::Is);
    // val "Hello" is a<string>;

    Type *var_type = nullptr;
    Node symbol = expect_token_type(nodes, TokenType::Identifier);
    if (nodes->at(0).token.type == TokenType::LessThan) {
        eat(nodes);
        nodes->at(0).out();
        if (nodes->at(0).token.type == TokenType::Identifier) {
            for (auto item : Shared::enums) {
                if (item.first == nodes->at(0).raw_value) {
                    Node type = expect_token_type(nodes, TokenType::Identifier);
                    expect_token_type(nodes, TokenType::GreaterThan);
                    var_type = new Type(type.token, type.raw_value);
                    break;
                }
            }

            if (var_type == nullptr) {
                error("Invalid enum type", nodes->at(0).token.line,
                      nodes->at(0).raw_value);
            }
        } else {
            Node type = expect_token_type(nodes, TokenType::Type);
            expect_token_type(nodes, TokenType::GreaterThan);
            var_type = new Type(type.token, type.raw_value);
        }
    }

    if (value.token.type == TokenType::Atom) {
        if (!is_atom_correct(value.raw_value)) {
            error("Invalid atom value", value.token.line, value.raw_value);
        } else {
            value.raw_value = get_atom_value(value.raw_value);
        }
    }

    expect_token_type(nodes, TokenType::Semicolon);
    Component *component = new Component();
    component->token = &symbol.token;
    component->node = &value;

    if (var_type == nullptr) {
        Type *type = new Type(value.token, "auto");
        component->cpp_translation = transpile_types(type) + " " +
                                     symbol.raw_value + " = " +
                                     value.raw_value + ";";
    } else {
        component->cpp_translation = transpile_types(var_type) + " " +
                                     symbol.raw_value + " = " +
                                     value.raw_value + ";";
    }
    return component;
}
