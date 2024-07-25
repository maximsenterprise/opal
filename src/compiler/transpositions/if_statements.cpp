/*
 if_statements.cpp
 As part of the Opal project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: If Statements in Opal
 Copyright (c) 2024 Maxims Enterprise
*/

#include "compiler/component.hpp"
#include "compiler/transpositions.hpp"
#include "parser/nodes.hpp"
#include <vector>

Component *if_statements(std::vector<Node> *nodes, bool insideMethod) {
    std::vector<Node> ifStatement;
    std::vector<Node> ifCondition;
    std::vector<std::vector<Node>> elseIfStatements;
    std::vector<std::vector<Node>> elseIfStatementsConditions;

    int openedParenthesis = 0;

    while (nodes->size() != 0) {
        if (nodes->at(0).token.type == TokenType::OpenParenthesis) {
            openedParenthesis++;
        } else if (nodes->at(0).token.type == TokenType::ClosingParenthesis) {
            openedParenthesis--;
            if (openedParenthesis == 0) {
                ifCondition.push_back(eat(nodes));
                break;
            }
        }
        ifCondition.push_back(eat(nodes));
    }

    std::vector<Node> elseStatement;

    int opened_braces = 0;
    while (nodes->size() != 0) {
        if (nodes->at(0).token.type == TokenType::OpenBrace) {
            opened_braces++;
            eat(nodes);
            continue;
        } else if (nodes->at(0).token.type == TokenType::ClosingBrace) {
            opened_braces--;
            if (opened_braces == 0) {
                eat(nodes);
                break;
            }
            eat(nodes);
            continue;
        }
        ifStatement.push_back(eat(nodes));
    }

    while (nodes->size() != 0) {
        openedParenthesis = 0;
        opened_braces = 0;
        if (nodes->at(0).token.type == TokenType::Else) {
            eat(nodes);
            if (nodes->at(0).token.type == TokenType::If) {
                eat(nodes);
                std::vector<Node> elseIfStatementCondition;
                while (nodes->size() != 0) {
                    if (nodes->at(0).token.type == TokenType::OpenParenthesis) {
                        openedParenthesis++;
                        eat(nodes);
                        continue;
                    } else if (nodes->at(0).token.type ==
                               TokenType::ClosingParenthesis) {
                        openedParenthesis--;
                        if (openedParenthesis == 0) {
                            eat(nodes);
                            break;
                        }
                        eat(nodes);
                        continue;
                    }
                    elseIfStatementCondition.push_back(eat(nodes));
                }

                elseIfStatementsConditions.push_back(elseIfStatementCondition);

                std::vector<Node> elseIfStatement;
                while (nodes->size() != 0) {
                    if (nodes->at(0).token.type == TokenType::OpenBrace) {
                        opened_braces++;
                        eat(nodes);
                        continue;
                    } else if (nodes->at(0).token.type ==
                               TokenType::ClosingBrace) {
                        opened_braces--;
                        if (opened_braces == 0) {
                            eat(nodes);
                            break;
                        }
                        eat(nodes);
                        continue;
                    }
                    elseIfStatement.push_back(eat(nodes));
                }
                elseIfStatements.push_back(elseIfStatement);
            } else {
                while (nodes->size() != 0) {
                    if (nodes->at(0).token.type == TokenType::OpenBrace) {
                        opened_braces++;
                        eat(nodes);
                        continue;
                    } else if (nodes->at(0).token.type ==
                               TokenType::ClosingBrace) {
                        opened_braces--;
                        if (opened_braces == 0) {
                            eat(nodes);
                            break;
                        }
                        eat(nodes);
                        continue;
                    }
                    elseStatement.push_back(eat(nodes));
                }
            }
        } else {
            break;
        }
    }

    std::vector<Component> ifStatementRendered;
    std::vector<std::vector<Component>> elseIfStatementsRendered;
    std::vector<Component> elseStatementRendered;

    ifStatementRendered = compile(ifStatement, insideMethod);
    if (elseStatementRendered.size() != 0) {
        for (std::vector<Node> nodes : elseIfStatements) {
            elseIfStatementsRendered.push_back(compile(nodes, insideMethod));
        }
    }

    if (elseStatement.size() != 0) {
        elseStatementRendered = compile(elseStatement, insideMethod);
    }

    Component *c = new Component();
    c->node = &ifStatement[0];
    c->token = &ifStatement[0].token;
    c->cpp_translation = "if ";
    for (Node n : ifCondition) {
        c->cpp_translation += n.raw_value;
    }

    c->cpp_translation += " {\n";
    for (Component comp : ifStatementRendered) {
        c->cpp_translation += comp.cpp_translation + "\n";
    }
    c->cpp_translation += "}\n";

    if (elseIfStatementsRendered.size() != 0) {
        for (size_t i = 0; i < elseIfStatementsRendered.size(); i++) {
            c->cpp_translation += "else if ";
            for (Node n : elseIfStatementsConditions[i]) {
                c->cpp_translation += n.raw_value;
            }
            c->cpp_translation += " {\n";
            for (Component comp : elseIfStatementsRendered[i]) {
                c->cpp_translation += comp.cpp_translation + "\n";
            }
            c->cpp_translation += "}\n";
        }
    }

    if (elseStatementRendered.size() != 0) {
        c->cpp_translation += "else ";
        c->cpp_translation += "{\n";
        for (Component comp : elseStatementRendered) {
            c->cpp_translation += comp.cpp_translation + "\n";
        }
        c->cpp_translation += "}\n";
    }

    return c;
}
