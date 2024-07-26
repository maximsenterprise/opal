/*
 use.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: The use statement for managing modules
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "core/error.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include <fstream>
#include <string>
#include <vector>

void use_statement(std::vector<Node> *nodes,
                   std::vector<Component> *compile_components) {
    if (nodes->at(0).token.type == TokenType::String) {
        Node file = eat(nodes);
        expect_token_type(nodes, TokenType::Semicolon);
        if (std::fstream(file.token.value.replace(file.token.value.begin(),
                                                  file.token.value.begin() + 1,
                                                  "\"", ""))) {
            if (file.raw_value.find(".opal") != std::string::npos) {
                std::string contents;
                std::ifstream file_stream;
                file_stream.open(file.token.value);
                if (file_stream.is_open()) {
                    file_stream >> contents;
                }

                std::vector<Token> tokens = tokenize(contents);
                std::vector<Node> nodes = parse(tokens);
                std::vector<Component> components = compile(nodes, false);
                for (Component component : components) {
                    compile_components->push_back(component);
                }
            }

        } else {
            error("File doesn't exists", file.token.line, file.token.value);
        }
    } else if (nodes->at(0).token.type == TokenType::Identifier) {
        Node module = eat(nodes);
        expect_token_type(nodes, TokenType::Semicolon);

        if (module.token.value == "std") {
            std::string contents;
            std::ifstream file_stream;
            file_stream.open("./std/std.opal");
            if (file_stream.is_open()) {
                while (file_stream.good()) {
                    std::string line;
                    std::getline(file_stream, line);
                    contents += line + "\n";
                }
            }

            std::vector<Token> tokens = tokenize(contents);
            std::vector<Node> nodes = parse(tokens);
            std::vector<Component> components = compile(nodes, false);
            for (Component component : components) {
                compile_components->push_back(component);
            }
        } else {
            error("Module doesn't exists", module.token.line,
                  module.token.value);
        }
    } else {
        error("Invalid module name", nodes->at(0).token.line,
              nodes->at(0).token.value);
    }
}
