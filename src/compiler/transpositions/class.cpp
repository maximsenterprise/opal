/*
 class.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Classes in Opal and their syntax
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include <iostream>
#include <vector>

Component *class_statement(std::vector<Node> *nodes) {
    Node class_name = nodes->at(0);
    eat(nodes);
    expect_token_type(nodes, TokenType::OpenBrace);
    int count = 1;
    std::vector<Node> body;
    while (count != 0) {
        Node node = eat(nodes);
        if (node.token.type == TokenType::OpenBrace) {
            count++;
            body.push_back(node);
        } else if (node.token.type == TokenType::ClosingBrace) {
            count--;
            if (count != 0) {
                body.push_back(node);
            } else {
                break;
            }
        } else {
            body.push_back(node);
        }
    }

    std::vector<Node> public_body;
    std::vector<Node> private_body;
    bool in_private = true;
    count = 0;
    for (Node node : body) {
        if (in_private) {
            if (node.token.type == TokenType::Shared) {
                in_private = false;
            } else {
                private_body.push_back(node);
            }
        } else {
            if (node.token.type == TokenType::OpenBrace) {
                count++;
                if (count == 1) {
                    continue;
                }
                public_body.push_back(node);
            } else if (node.token.type == TokenType::ClosingBrace) {
                count--;
                if (count == 0) {
                    in_private = true;
                } else {
                    public_body.push_back(node);
                }
            } else {
                public_body.push_back(node);
            }
        }
    }

    for (Node node : private_body) {
        node.out();
    }
    std::cout << "-------" << std::endl;

    for (Node node : public_body) {
        node.out();
    }

    Component *c = new Component();
    c->node = &class_name;
    c->token = &class_name.token;
    c->cpp_translation = "class " + class_name.raw_value + "{\n";
    for (Component comp : compile(private_body, false)) {
        c->cpp_translation += comp.cpp_translation;
    }
    c->cpp_translation += "public:\n";
    for (Component comp : compile(public_body, true)) {
        c->cpp_translation += comp.cpp_translation;
    }
    c->cpp_translation += "};\n";
    return c;
}
