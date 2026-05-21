#include "parser.hpp"
#include "ast.hpp"
#include "scanner.hpp"
#include <cstdint>
#include <string>

void XX::Parser::advance() {
  previousToken = currentToken;
  currentToken = scanner.scanToken();
}

bool XX::Parser::match(XX::TokenType t) {
  return (t == currentToken.type) ? true : false;
}

XX::AST::Type XX::Parser::matchType(XX::TokenType t) {
  switch (t) {
  case XX::TokenType::KW_INT8:
    return AST::Type::INT8;
  case XX::TokenType::KW_INT16:
    return AST::Type::INT16;
  case XX::TokenType::KW_INT32:
    return AST::Type::INT32;
  case XX::TokenType::KW_INT64:
    return AST::Type::INT64;
  case XX::TokenType::KW_FLOAT8:
    return AST::Type::FLOAT8;
  case XX::TokenType::KW_FLOAT16:
    return AST::Type::FLOAT16;
  case XX::TokenType::KW_FLOAT32:
    return AST::Type::FLOAT32;
  case XX::TokenType::KW_FLOAT64:
    return AST::Type::FLOAT64;
  default:
    // TODO: It's unreachable what do I do (in todo yes)
    return AST::Type::INT8;
  }
}

XX::AST::Node *XX::Parser::parse() {
  while (currentToken.type != TokenType::TOKEN_EOF) {
    switch (currentToken.type) {
    case TokenType::KW_INT8:
    case TokenType::KW_INT16:
    case TokenType::KW_INT32:
    case TokenType::KW_INT64:
    case TokenType::KW_FLOAT8:
    case TokenType::KW_FLOAT16:
    case TokenType::KW_FLOAT32:
    case TokenType::KW_FLOAT64:
      return parseVarDeclr();
      break;
    default:
      // TODO: I don't know what I'm gonna do, C++ make me wanna cry
      return nullptr;
    }
  }
  return nullptr;
}

// VarDeclr = type identifiers "="  (Expr | BinaryExpr) ";"
// BinaryExor is for later cause I'm suck
XX::AST::VarDeclr *XX::Parser::parseVarDeclr() {
  AST::Type t = matchType(currentToken.type);
  uint32_t o = currentToken.offset;
  uint16_t l = currentToken.length;
  advance();
  std::string name = source.substr(currentToken.offset, currentToken.length);

  advance();
  if (!match(TokenType::EQUAL))
    // TODO: make node error or something IDK, so I'll leave a return null
    return nullptr;

  advance();

  XX::AST::Expr *value = parseExpr();

  return new AST::VarDeclr(o, l, t, name, value);
}

// What's the Expression?
// I don't have any idea either, JK
// Expr = IntLiteral | FloatLiteral | BinaryExpr | ...
XX::AST::Expr *XX::Parser::parseExpr() {
  switch (currentToken.type) {
  case TokenType::NUMBER_INT:
    return parseIntLiteral();
  case TokenType::NUMBER_FLOAT:
    return parseFloatLiteral();
  default:
    // TODO: DMC short for developer may cry. although I'm just a vibe coder
    // (tho this code node vibe coded but I do talking with llm alot)
    return nullptr;
  }
}

XX::AST::IntLiteral *XX::Parser::parseIntLiteral() {
  return new AST::IntLiteral(
      currentToken.offset, currentToken.length,
      std::stoll(source.substr(currentToken.offset, currentToken.length)));
}

XX::AST::FloatLiteral *XX::Parser::parseFloatLiteral() {
  return new AST::FloatLiteral(
      currentToken.offset, currentToken.length,
      std::stod(source.substr(currentToken.offset, currentToken.length)));
}
