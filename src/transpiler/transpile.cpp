/*
 transpile.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Final transpiler
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "core/error.hpp"
#include "shared.hpp"
#include "transpiler.hpp"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

void transpile(std::vector<Component> components, std::string output) {
    std::string code = "";
    std::vector<std::string> modules = Shared::modules;

    for (std::string item : modules) {
        code += "#include " + item + "\n";
    }

    for (Component component : components) {
        code += component.cpp_translation + "\n";
    }

    std::ofstream file(output);
    file << code;
    file.close();

    success("File compiled successfully! " + output);

    std::string c = "clang-format -i ";
    std::string conc = c + output;
    const char *command = conc.c_str();
    int result = system(command);

    if (result == 0) {
        success("File formatted correctly!");
    } else {
        panic("Error formatting file", 0);
    }
}
