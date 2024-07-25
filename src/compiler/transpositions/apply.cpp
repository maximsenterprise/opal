/*
 apply.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Apply method for Opal
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

void apply_statement(std::vector<Node> *nodes,
                     std::vector<Component> *components) {
    Node struct_name = expect_token_type(nodes, TokenType::Identifier);
    if (nodes->at(0).token.type == TokenType::OpenBrace) {
        eat(nodes);
        std::vector<Node> interior;
        int opened = 1;
        while (opened > 0) {
            Node n = eat(nodes);
            if (n.token.type == TokenType::OpenBrace) {
                opened++;
                interior.push_back(n);
            } else if (n.token.type == TokenType::ClosingBrace) {
                opened--;
                if (opened != 0) {
                    interior.push_back(n);
                } else {
                    break;
                }
            } else {
                interior.push_back(n);
            }
        }

        if (Shared::structs.find(struct_name.token.value) !=
            Shared::structs.end()) {
            int component_index = -1;
            for (size_t i = 0; i < components->size(); ++i) {
                Component c = components->at(i);
                if (c.cpp_translation ==
                    Shared::structs.find(struct_name.token.value)
                        ->second->cpp_translation) {
                    component_index = i;
                    std::cout << component_index << std::endl;
                    break;
                }
            }

            if (component_index == -1) {
                panic("invalid struct value found", struct_name.token.line);
                exit(1);
            } else {
                Component *old = &components->at(component_index);
                Component *new_component = new Component();
                new_component->token = old->token;
                new_component->node = old->node;
                new_component->cpp_translation = old->cpp_translation.substr(
                    0, old->cpp_translation.size() - 3);
                for (Component c : compile(interior, false)) {
                    new_component->cpp_translation += c.cpp_translation + "\n";
                }
                new_component->cpp_translation += "\n};";
                components->at(component_index) = *new_component;
            }

        } else {
            error("Struct not found", struct_name.token.line,
                  struct_name.token.value);
            exit(1);
        }
    } else {
        error("Invalid appply statement", struct_name.token.line,
              struct_name.token.value);
        exit(1);
    }
}
