// shared.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "shared.hpp"
#include "compiler/component.hpp"
#include <map>
#include <string>
#include <vector>

Program *Shared::program = nullptr;
std::vector<std::string> Shared::modules = {};
std::map<std::string, std::vector<std::string>> Shared::enums = {};
std::map<std::string, Component *> Shared::structs = {};
