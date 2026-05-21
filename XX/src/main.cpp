#include "ast.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

void traverse(XX::AST::Node *root);
void handleVarDeclr(XX::AST::VarDeclr *root);
void handleExpr(XX::AST::Expr *root);
void handleIntLiteral(XX::AST::IntLiteral *TSnotRootAnymore);

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

int main(int argc, char *argv[]) {
  if (argc < 2)
    return 1;

  std::ifstream file(argv[1]);

  if (!file)
    return 2;

  std::string source;
  std::stringstream buffer;
  buffer << file.rdbuf();
  source = buffer.str();

  XX::Scanner scanner(source);
  XX::Parser parser(scanner, source);

  XX::AST::Node *root = parser.parse();

  traverse(root);

  return 0;
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

void handleVarDeclr(XX::AST::VarDeclr *root) {
  std::cout << "Type: " << matchEnumType(root->getType())
            << "| Variable name: " << root->getVarName() << "\n";
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
