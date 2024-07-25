/*
 program.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Program class
 Copyright (c) 2024 Maxims Enterprise
*/

#include "program.hpp"
#include "compiler/component.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "transpiler.hpp"

#include <iostream>
#include <string>
#include <vector>

Program::Program(std::string contents, std::string name) {
    this->contents = contents;
    this->name = name;
}

Program::~Program() {}

void Program::run() {
    std::vector<Token> tokens = tokenize(this->contents);
    // for (Token t : tokens) {
    //     t.out();
    // }
    std::vector<Node> nodes = parse(tokens);
    // for (Node n : nodes) {
    //     n.out();
    // }
    std::vector<Component> components = compile(nodes, false);
    transpile(components, "examples/test.cpp");
}
