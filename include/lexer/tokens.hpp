// tokens.hpp
// As part of the Opal project
// Created by Maxims Enterprise in 2024

#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

enum class TokenType {
    // Keywords
    Use,
    Procedure,
    Method,
    Val,
    Is,
    As,
    Return,
    If,
    Else,
    Res,
    Data,
    Struct,
    Apply,
    Rule,
    Final,
    Class,
    Shared,
    New,

    // Operators
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,

    // Punctuation
    Comma,
    OpenParenthesis,
    ClosingParenthesis,
    OpenBrace,
    ClosingBrace,
    Colon,
    Semicolon,
    LessThan,
    GreaterThan,
    LogicalEquals,
    LogicalOr,
    LogicalAnd,
    NotEquals,
    Bar,
    Right_Arrow,
    ExclamationMark,
    Hash,

    // Literals
    String,
    Char,
    Integer,
    Float,

    // Others
    Type,
    Identifier,
    Atom,
    Cpp,
    EndOfTheFile,
};

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, const std::string &value, int line)
        : type(type), value(value), line(line) {}

  public:
    void out();
};

#endif // TOKENS_HPP
