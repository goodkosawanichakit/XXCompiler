#include "astdump.hpp"
#include <iostream>

std::string matchEnumKind(XX::AST::Kind k) {
  switch (k) {
  case XX::AST::Kind::EXPR:
    return "EXPR";
  case XX::AST::Kind::BINARY_EXPR:
    return "BINARY_EXPR";
  case XX::AST::Kind::INT_LITERAL:
    return "INT_LITERAL";
  case XX::AST::Kind::FLOAT_LITERAL:
    return "FLOAT_LITERAL";
  case XX::AST::Kind::VAR_DECLR:
    return "VAR_DECLR";
  }
  return "UNKNOWN_KIND";
}
std::string matchEnumType(XX::AST::Type t) {
  switch (t) {
  case XX::AST::Type::INT8:
    return "INT8";
  case XX::AST::Type::INT16:
    return "INT16";
  case XX::AST::Type::INT32:
    return "INT32";
  case XX::AST::Type::INT64:
    return "INT64";
  case XX::AST::Type::FLOAT8:
    return "FLOAT8";
  case XX::AST::Type::FLOAT16:
    return "FLOAT16";
  case XX::AST::Type::FLOAT32:
    return "FLOAT32";
  case XX::AST::Type::FLOAT64:
    return "FLOAT64";
  }
  return "UNKNOWN_TYPE";
}

void handleIntLiteral(XX::AST::IntLiteral *TSnotRootAnymore) {
  std::cout << "Value: " << TSnotRootAnymore->getValue() << "\n";
}

void handleExpr(XX::AST::Expr *root) {
  switch (root->getKind()) {
  case XX::AST::Kind::INT_LITERAL:
    handleIntLiteral((XX::AST::IntLiteral *)root);
    return;
  case XX::AST::Kind::FLOAT_LITERAL:
    // it's raining taco
  default:
    std::cout << "We shouldn't be here\n";
  }
}

// void handleBinaryExpr(XX::AST::BinaryExpr *root) {
//   std::cout << root.
// }

void handleVarDeclr(XX::AST::VarDeclr *root) {
  std::cout << matchEnumKind(root->getKind()) << ' '
            << matchEnumType(root->getType()) << root->getVarName();
  if (!(root->getExpr()))
    return;
  handleExpr(root->getExpr());
}

void traverse(XX::AST::Node *root) {
  if (!root)
    return;

  switch (root->getKind()) {
  case XX::AST::Kind::VAR_DECLR:
    handleVarDeclr((XX::AST::VarDeclr *)root);
    return;
  default:
    std::cout << "How did we even get here\n";
    return;
  }
}
