#pragma once

#include <string>

namespace compiler {

enum class TokenType {
  // Single-character tokens
  PLUS,
  MINUS,
  STAR,
  SLASH,

  // Two-character tokens
  DOT_DOT,
  NOT,
  NOT_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals
  IDENTIFIER,
  STRING,
  NUMBER_INT,
  NUMBER_FLOAT,

  // Keywords
  KW_INT,
  KW_FLOAT,
  KW_BOOL,
  KW_IF,
  KW_ELSE,
  KW_LOOP,
  KW_IN,
  KW_STEP,
  KW_FN,
  KW_RETURN,
  KW_TRUE,
  KW_FALSE,

  TOKEN_EOF
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;
};

} // namespace compiler
