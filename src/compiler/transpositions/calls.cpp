// calls.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "utils.hpp"
#include <cstddef>
#include <vector>

Component *function_call(std::vector<Node> *nodes) {
    Node name = expect_token_type(nodes, TokenType::Identifier);
    if (nodes->at(0).token.type == TokenType::OpenParenthesis) {
        eat(nodes);
        std::vector<Node> arguments;
        while (nodes->size() > 0) {
            if (nodes->at(0).token.type == TokenType::ClosingParenthesis) {
                eat(nodes);
                break;
            } else {
                arguments.push_back(eat(nodes));
                if (nodes->at(0).token.type == TokenType::Comma) {
                    eat(nodes);
                } else if (nodes->at(0).token.type ==
                           TokenType::ClosingParenthesis) {
                    eat(nodes);
                    break;
                } else {
                    error("Invalid arguments for a function call",
                          arguments.back().token.line,
                          arguments.back().raw_value);
                }
            }
        }
        if (nodes->size() <= 0) {

        } else {
            expect_token_type(nodes, TokenType::Semicolon);
        }

        Component *c = new Component();
        c->token = &name.token;
        c->node = &name;
        c->cpp_translation = name.raw_value + "(";
        for (size_t i = 0; i < arguments.size(); i++) {
            c->cpp_translation += arguments[i].raw_value;
            if (i < arguments.size() - 1) {
                c->cpp_translation += ", ";
            }
        }
        c->cpp_translation += ");";
        return c;
    } else if (nodes->at(0).token.type == TokenType::Is) {
        eat(nodes);
        if (nodes->at(0).token.type == TokenType::Identifier) {
            Node function_name = eat(nodes);
            if (nodes->at(0).token.type == TokenType::OpenParenthesis) {
                std::vector<Node> arguments;
                eat(nodes);
                while (nodes->size() > 0) {
                    if (nodes->at(0).token.type ==
                        TokenType::ClosingParenthesis) {
                        eat(nodes);
                        break;
                    } else {
                        arguments.push_back(eat(nodes));
                        if (nodes->at(0).token.type == TokenType::Comma) {
                            eat(nodes);
                        } else if (nodes->at(0).token.type ==
                                   TokenType::ClosingParenthesis) {
                            eat(nodes);
                            break;
                        } else {
                            error("Invalid arguments for a function call",
                                  arguments.back().token.line,
                                  arguments.back().raw_value);
                        }
                    }
                }

                expect_token_type(nodes, TokenType::Semicolon);

                Component *c = new Component();
                c->token = &name.token;
                c->node = &name;
                c->cpp_translation = name.raw_value + " = ";
                c->cpp_translation +=
                    compile(arguments, false)[0].cpp_translation;
                return c;
            } else {
                Component *c = new Component();
                c->token = &name.token;
                c->node = &name;
                c->cpp_translation = name.raw_value + " = ";
                c->cpp_translation += function_name.raw_value;
                c->cpp_translation += ";";
                expect_token_type(nodes, TokenType::Semicolon);
                return c;
            }
        } else if (nodes->at(0).token.type == TokenType::Atom) {
            if (is_atom_correct(nodes->at(0).raw_value)) {
                Node atom = eat(nodes);
                Component *c = new Component();
                c->token = &name.token;
                c->node = &name;
                c->cpp_translation = name.raw_value + " = ";
                c->cpp_translation += get_atom_value(atom.raw_value);
                c->cpp_translation += ";";
                expect_token_type(nodes, TokenType::Semicolon);
                return c;
            } else {
                error("Invalid atom value", nodes->at(0).token.line,
                      nodes->at(0).raw_value);
                return nullptr;
            }
        } else {
            Node val = eat(nodes);
            Component *c = new Component();
            c->token = &name.token;
            c->node = &name;
            c->cpp_translation = name.raw_value + " = " + val.raw_value + ";";
            expect_token_type(nodes, TokenType::Semicolon);
            return c;
        }

    } else {
        error("Invalid variable call", name.token.line, name.raw_value);
        return nullptr;
    }
}
