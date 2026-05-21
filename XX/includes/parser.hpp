#pragma once

#include "ast.hpp"
#include "scanner.hpp"

namespace XX {
class Parser {
private:
  Scanner &scanner;
  const std::string &source;
  AST::Node *module;
  Token currentToken;
  Token previousToken;

  void advance();
  bool match(TokenType t);
  AST::Type matchType(TokenType t);
  AST::VarDeclr *parseVarDeclr();
  AST::Expr *parseExpr();
  AST::BinaryExpr *parseBinaryExpr();
  AST::IntLiteral *parseIntLiteral();
  AST::FloatLiteral *parseFloatLiteral();

public:
  AST::Node *parse();
  Parser(Scanner &s, std::string &sc) : scanner(s), source(sc) { advance(); }
  ~Parser() {}
};
} // namespace XX
