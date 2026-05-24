#include "astdump.hpp"
#include "ast.hpp"
#include <iostream>

// TBH these two match function is llm generated cause I'm lazy.
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

uint32_t XX::AST::Dumper::getLine(uint32_t of) {
  if (lineOffset.empty())
    return 1;
  int l = 0;
  int r = lineOffset.size() - 1;
  uint32_t target = lineOffset.size();
  while (l <= r) {
    int m = l + (r - l) / 2;

    if (lineOffset[m] > of) {
      target = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  return target;
}

void XX::AST::Dumper::dump(Node *node) {
  if (!node)
    return;
  switch (node->getKind()) {
  case Kind::VAR_DECLR:
    dumpVarDeclr((VarDeclr *)node);
    break;
  default:
    // TODO: IDK what I need to handle in this deafult section.
    // so todo is I need to think what I'm gonna do
    std::cout << "You shouldn't be here." << std::endl;
  }
}

// Prob work fine I think
void XX::AST::Dumper::dumpVarDeclr(VarDeclr *node) {
  if (!node)
    return;
  std::cout << matchEnumKind(node->getKind()) << ' '
            << matchEnumType(node->getType()) << " Name: " << node->getVarName()
            << ' ' << getLine(node->getOffset()) << std::endl;
  dumpExpr(node->getExpr());
}

void XX::AST::Dumper::dumpExpr(Expr *node) {
  if (!node)
    return;
  switch (node->getKind()) {
  case Kind::INT_LITERAL:
    return dumpIntLiteral((IntLiteral *)node);
  case Kind::BINARY_EXPR:
    return dumpBinaryExpr((BinaryExpr *)node);
  default:
    std::cout << "How did you get here." << std::endl;
  }
}

void XX::AST::Dumper::dumpBinaryExpr(BinaryExpr *node) {
  if (!node)
    return;
  std::cout << matchEnumKind(node->getKind()) << " Operator: " << node->getOP()
            << ' ' << getLine(node->getOffset()) << std::endl;
  dumpExpr(node->getLExpr());
  dumpExpr(node->getRExpr());
}

void XX::AST::Dumper::dumpIntLiteral(IntLiteral *node) {
  if (!node)
    return;
  std::cout << matchEnumKind(node->getKind()) << " Value: " << node->getValue()
            << std::endl;
}
