/*
 lexer.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Lexer for the Opal Programming Language
 Copyright (c) 2024 Maxims Enterprise
*/

#include "lexer/lexer.hpp"
#include "core/error.hpp"
#include "lexer/tokens.hpp"
#include "shared.hpp"
#include "utils.hpp"
#include <_ctype.h>
#include <algorithm>
#include <cstddef>
#include <cwctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<Token> tokenize(const std::string &source) {
    std::vector<Token> tokens;
    int line = 1;

    for (size_t i = 0; i < source.length(); i++) {
        char c = source[i];

        if (c == '\n') {
            line++;
        } else if (iswblank(c)) {
            continue;
        } else if (c == ',') {
            tokens.push_back(Token(TokenType::Comma, ",", line));
        } else if (c == '(') {
            tokens.push_back(Token(TokenType::OpenParenthesis, "(", line));
        } else if (c == ')') {
            tokens.push_back(Token(TokenType::ClosingParenthesis, ")", line));
        } else if (c == '{') {
            tokens.push_back(Token(TokenType::OpenBrace, "{", line));
        } else if (c == '}') {
            tokens.push_back(Token(TokenType::ClosingBrace, "}", line));
        } else if (c == '#') {
            tokens.push_back(Token(TokenType::Hash, "#", line));
        } else if (c == ':') {
            if (isalpha(source[i + 1])) {
                std::string atom;
                for (size_t j = i + 1; j < source.length(); j++) {
                    if (isalnum(source[j]) || source[j] == '_') {
                        atom += source[j];
                    } else {
                        i = j - 1;
                        break;
                    }
                }
                tokens.push_back(Token(TokenType::Atom, atom, line));
            } else {
                tokens.push_back(Token(TokenType::Colon, ":", line));
            }
        } else if (c == ';') {
            tokens.push_back(Token(TokenType::Semicolon, ";", line));
        } else if (c == '+') {
            tokens.push_back(Token(TokenType::Plus, "+", line));
        } else if (c == '-') {
            if (i + 1 < source.length() && source[i + 1] == '>') {
                tokens.push_back(Token(TokenType::Right_Arrow, "->", line));
                i++;
            } else {
                tokens.push_back(Token(TokenType::Minus, "-", line));
            }
        } else if (c == '*') {
            tokens.push_back(Token(TokenType::Multiply, "*", line));
        } else if (c == '/') {
            tokens.push_back(Token(TokenType::Divide, "/", line));
        } else if (c == '%') {
            tokens.push_back(Token(TokenType::Modulo, "%", line));
        } else if (c == '<') {
            tokens.push_back(Token(TokenType::LessThan, "<", line));
        } else if (c == '>') {
            tokens.push_back(Token(TokenType::GreaterThan, ">", line));
        } else if (c == '@') {
            tokens.push_back(Token(TokenType::At, "@", line));
        } else if (c == '[') {
            tokens.push_back(Token(TokenType::OpenBracket, "[", line));
        } else if (c == ']') {
            tokens.push_back(Token(TokenType::ClosingBracket, "]", line));
        } else if (c == '=') {
            if (source[i + 1] == '=') {
                tokens.push_back(Token(TokenType::LogicalEquals, "==", line));
                i++;
            } else {
                error("Unexpected character found in source: " +
                          std::string(1, c),
                      line, std::string(1, c));
            }
        } else if (c == '!') {
            if (source[i + 1] == '=') {
                tokens.push_back(Token(TokenType::NotEquals, "!=", line));
                i++;
            } else {
                std::string next_iden = "";
                for (size_t j = i + 1; j < source.length(); j++) {
                    if (isalnum(source[j]) || source[j] == '_') {
                        next_iden += std::string(1, source[j]);
                    } else {
                        break;
                    }
                }
                if (next_iden == "cpp") {
                    i = i + 4;
                    while (iswblank(source[i])) {
                        i++;
                    }
                    int opened = 1;
                    i++;
                    std::string cpp_code = "";
                    while (opened != 0) {
                        if (source[i] == '{') {
                            opened++;
                            i++;
                            cpp_code += std::string(1, '{');
                            continue;
                        } else if (source[i] == '}') {
                            opened--;
                            i++;
                            if (opened != 0) {
                                cpp_code += std::string(1, '}');
                            }
                            continue;
                        }
                        cpp_code += std::string(1, source[i]);
                        i++;
                    }
                    tokens.push_back(Token(TokenType::Cpp, cpp_code, line));
                } else {
                    tokens.push_back(
                        Token(TokenType::ExclamationMark, "!", line));
                }
            }
        } else if (c == '|') {
            if (source[i + 1] == '|') {
                tokens.push_back(Token(TokenType::LogicalOr, "||", line));
                i++;
            } else {
                tokens.push_back(Token(TokenType::Bar, "|", line));
            }
        } else if (c == '&') {
            if (source[i + 1] == '&') {
                tokens.push_back(Token(TokenType::LogicalAnd, "&&", line));
                i++;
            } else {
                error("Unexpected character found in source: " +
                          std::string(1, c),
                      line, std::string(1, c));
            }
        } else if (c == '"') {
            std::string value;
            for (size_t j = i + 1; j < source.length(); j++) {
                if (source[j] == '"') {
                    i = j;
                    break;
                }
                value += source[j];
            }
            value = value + '"';
            value = '"' + value;
            tokens.push_back(Token(TokenType::String, value, line));
        } else if (isnumber(c)) {
            std::string value;
            bool is_float = false;
            for (size_t j = i; j < source.length(); j++) {
                if (isnumber(source[j]) || source[j] == '.') {
                    value += source[j];
                    if (source[j] == '.') {
                        is_float = true;
                    }
                } else {
                    i = j - 1;
                    break;
                }
            }

            if (is_float) {
                tokens.push_back(Token(TokenType::Float, value, line));
            } else {
                tokens.push_back(Token(TokenType::Integer, value, line));
            }
        } else if (isalpha(c)) {
            std::string value;
            for (size_t j = i; j < source.length(); j++) {
                if (isalnum(source[j]) || source[j] == '_') {
                    value += source[j];
                } else {
                    i = j - 1;
                    break;
                }
            }

            if (contains_type(value)) {
                std::string pointers = "";
                while (source[i + 1] == '*') {
                    pointers += "*";
                    i++;
                }
                value += pointers;
                if (pointers != "") {
                    tokens.push_back(
                        Token(TokenType::Type, value + pointers, line));
                    continue;
                }
                tokens.push_back(Token(TokenType::Type, value, line));
            } else if (Shared::keywords.find(value) != Shared::keywords.end()) {
                tokens.push_back(Token(Shared::keywords[value], value, line));
            } else if (value == "self") {
                tokens.push_back(Token(TokenType::Identifier, "*this", line));
            } else {
                std::string pointers = "";
                while (source[i + 1] == '*') {
                    pointers += "*";
                    i++;
                }
                value += pointers;
                if (pointers != "") {
                    tokens.push_back(
                        Token(TokenType::Identifier, value + pointers, line));
                    continue;
                }

                while (source[i + 1] == '&') {
                    value += "&";
                    i++;
                }

                tokens.push_back(Token(TokenType::Identifier, value, line));
            }
        } else {
            error("Unexpected character found in source: " + std::string(1, c),
                  line, std::string(1, c));
        }
    }

    tokens.push_back(Token(TokenType::EndOfTheFile, "", line));
    return tokens;
}
