/*
 tokens.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Tokens translation
 Copyright (c) 2024 Maxims Enterprise
*/

#include "lexer/tokens.hpp"
#include "shared.hpp"
#include <iostream>
#include <map>
#include <vector>

std::map<std::string, TokenType> Shared::keywords = {
    {"use", TokenType::Use},       {"procedure", TokenType::Procedure},
    {"method", TokenType::Method}, {"val", TokenType::Val},
    {"is", TokenType::Is},         {"proc", TokenType::Procedure},
    {"as", TokenType::As},         {"give", TokenType::Return},
    {"if", TokenType::If},         {"else", TokenType::Else},
    {"res", TokenType::Res},       {"data", TokenType::Data},
    {"apply", TokenType::Apply},   {"final", TokenType::Final},
    {"shared", TokenType::Shared}, {"struct", TokenType::Struct},
    {"rule", TokenType::Rule},     {"class", TokenType::Class},
    {"new", TokenType::New},       {"const", TokenType::Const},
};

void Token::out() {
    std::cout << "Token: " << value << " at line " << line << "\n";
    std::cout << "Type: " << Shared::tokenNames[type] << "\n";
    std::cout << "-------------------\n";
}

std::map<std::string, Token *> Shared::sampleTokens = {
    {"string", new Token(TokenType::String, "string", 0)},
    {"char", new Token(TokenType::Char, "char", 0)},
    {"int", new Token(TokenType::Integer, "int", 0)},
    {"float", new Token(TokenType::Float, "float", 0)},
};

std::vector<std::string> Shared::types = {"string", "char", "int", "float"};

std::map<TokenType, std::string> Shared::tokenNames = {
    {TokenType::Use, "Use"},
    {TokenType::Procedure, "Procedure"},
    {TokenType::Method, "Method"},
    {TokenType::Val, "Val"},
    {TokenType::Is, "Is"},
    {TokenType::Plus, "Plus"},
    {TokenType::Minus, "Minus"},
    {TokenType::Multiply, "Multiply"},
    {TokenType::Divide, "Divide"},
    {TokenType::Modulo, "Modulo"},
    {TokenType::Comma, "Comma"},
    {TokenType::OpenParenthesis, "OpenParenthesis"},
    {TokenType::ClosingParenthesis, "ClosingParenthesis"},
    {TokenType::OpenBrace, "OpenBrace"},
    {TokenType::ClosingBrace, "ClosingBrace"},
    {TokenType::Colon, "Colon"},
    {TokenType::Semicolon, "Semicolon"},
    {TokenType::String, "String"},
    {TokenType::Char, "Char"},
    {TokenType::Integer, "Integer"},
    {TokenType::Float, "Float"},
    {TokenType::Type, "Type"},
    {TokenType::Identifier, "Identifier"},
    {TokenType::EndOfTheFile, "EndOfTheFile"},
    {TokenType::As, "As"},
    {TokenType::GreaterThan, "GreaterThan"},
};
