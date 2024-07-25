// utils.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "utils.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "parser/nodes.hpp"
#include "shared.hpp"

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> *split(std::string str, char delimiter) {
    size_t pos = 0;
    std::vector<std::string> *tokens = new std::vector<std::string>();
    while ((pos = str.find(delimiter)) != std::string::npos) {
        tokens->push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    return tokens;
}

bool check_type(const Node &value, const Node &type) {
    if (value.token.type == TokenType::Atom) {
        if (is_atom_correct(value.raw_value)) {
            if (get_atom_value(value.raw_value).find(type.raw_value) !=
                std::string::npos) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    Type *t = new Type(type.token, type.raw_value);
    if (t->sample_token != nullptr) {
        if (t->sample_token->type == value.token.type) {
            return true;
        } else {
            return false;
        }
    } else {
        panic("program used a nullptr", value.token.line);
        return false;
    }
}

std::string transpile_types(Type *opal_type) {
    if (opal_type->raw_value == "auto") {
        return "auto";
    }
    if (opal_type->sample_token == nullptr) {
        return opal_type->raw_value;
    }
    switch (opal_type->sample_token->type) {
    case TokenType::Integer:
        return "int";
    case TokenType::Float:
        return "float";
    case TokenType::String:
        if (!module_added("string")) {
            add_module("<string>");
        }
        return "std::string";
    case TokenType::Identifier:
        return opal_type->raw_value;
    default:
        panic("type cannot be evaluated", opal_type->token.line);
        return "";
    }
}

void add_module(std::string module_name) {
    Shared::modules.push_back(module_name);
}

bool module_added(std::string module_name) {
    for (std::string module : Shared::modules) {
        if (module.substr(1, module.size() - 2) == module_name) {
            return true;
        }
    }
    return false;
}

bool contains_type(const std::string &value) {
    for (const auto &type : Shared::types) {
        if (type == value) {
            return true;
        }
    }
    return false;
}

bool is_atom_correct(std::string atom_value) {
    for (auto item : Shared::enums) {
        for (std::string member : item.second) {
            if (atom_value == member) {
                return true;
            }
        }
    }
    return false;
}

std::string get_atom_value(std::string atom_value) {
    for (auto item : Shared::enums) {
        for (std::string member : item.second) {
            if (atom_value == member) {
                return item.first + "::" + member;
            }
        }
    }
    return "";
}
