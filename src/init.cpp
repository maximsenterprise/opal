// init.cpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#include "program.hpp"
#include "shared.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Open and save the text file into a string.
    ifstream file("examples/test.opal");

    if (file.is_open()) {
        string contents;
        string final;
        while (getline(file, contents)) {
            final += contents + "\n";
        }

        Program *program = new Program(final, "test.opal");
        Shared::program = program;
        program->run();
    } else {
        // If the file is not found, print an error message.
        cerr << "Error: File not found." << endl;
    }
}
