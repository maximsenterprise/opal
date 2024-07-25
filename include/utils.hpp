// utils.h
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef UTILS_H
#define UTILS_H

#include "parser/nodes.hpp"
#include <string>
#include <vector>

enum class NodeType {
    NumericLiteral,
    StringLiteral,
    Literal,
    Operation,
    Type,
    Other
};

std::vector<std::string> *split(std::string str, char delimiter);
bool check_type(const Node &value, const Node &type);
std::string transpile_types(Type *opal_type);
void add_module(std::string module_name);
bool module_added(std::string module_name);
bool contains_type(const std::string &value);
void check_method(const std::vector<Node> *nodes);
std::string get_atom_value(std::string atom_value);
bool is_atom_correct(std::string atom_value);
void replace(std::string &str, const std::string &from, const std::string &to);

#endif // UTILS_H
