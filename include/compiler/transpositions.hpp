// transpositions.hpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef TRANSPOSITIONS_HPP
#define TRANSPOSITIONS_HPP

#include "compiler/component.hpp"
#include "parser/nodes.hpp"
#include <vector>

Component *variable_declaration(std::vector<Node> *nodes);
Component *procedure_declaration(std::vector<Node> *nodes);
Component *method_declaration(std::vector<Node> *nodes);
Component *return_statement(std::vector<Node> *nodes);
Component *function_call(std::vector<Node> *nodes);
Component *if_statements(std::vector<Node> *nodes, bool inside_method);
Component *save_statement(std::vector<Node> *nodes);
Component *data_statement(std::vector<Node> *nodes);
Component *cpp_statement(std::vector<Node> *nodes);
Component *struct_statement(std::vector<Node> *nodes);
void apply_statement(std::vector<Node> *nodes,
                     std::vector<Component> *components);
Component *class_statement(std::vector<Node> *nodes);
Component *include_macro(std::vector<Node> *nodes);
Component *template_args(std::vector<Node> *nodes);

#endif // TRANSPOSITIONS_HPP
