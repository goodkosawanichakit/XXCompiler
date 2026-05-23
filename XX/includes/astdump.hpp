#pragma once

#include "ast.hpp"

namespace XX::AST {

void traverse(Node *root);
void handleVarDeclr(XX::AST::VarDeclr *root);
void handleBinaryExpr(XX::AST::BinaryExpr *root);
void handleExpr(XX::AST::Expr *root);
void handleIntLiteral(XX::AST::IntLiteral *TSnotRootAnymore);

}; // namespace XX::AST
