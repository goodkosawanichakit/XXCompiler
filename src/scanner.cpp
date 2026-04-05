#include "scanner.hpp"

XX::Scanner::Scanner(const std::string &source) : source(source) {}

bool XX::Scanner::isAtEnd() { return current >= source.length(); }

bool XX::Scanner::match(char c) {
  if (isAtEnd())
    return false;
  if (source[current] != c)
    return false;
  current++;
  return true;
}

char XX::Scanner::advance() { return source[current++]; }

char XX::Scanner::peek() {
  if (isAtEnd())
    return '\0';
  return source[current];
}

char XX::Scanner::peekNext() {
  if (isAtEnd())
    return '\0';
  return source[current + 1];
}

void XX::Scanner::skipWhitespace() {
  while (!isAtEnd())
    switch (peek()) {
    case ' ':
    case '\t':
    case '\r':
      advance();
      break;
    case '\n':
      line++;
      advance();
      break;
    default:
      return;
    }
}

XX::Token XX::Scanner::string() {
  while (peek() != '"' && !isAtEnd())
    advance();
  if (isAtEnd()) {
    // TODO : I've no idea what I should return, so yeah maybe one day I'll
    // know.
  }
  advance();
  return Token{TokenType::STRING, source.substr(start + 1, current - start - 2),
               line};
}

XX::Token XX::Scanner::digit() {
  bool is_float = false;

  while (isdigit(peek()) && !isAtEnd())
    advance();

  if (peek() == '.' && isdigit(peekNext())) {
    is_float = true;
    advance();
    while (isdigit(peek()) && !isAtEnd())
      advance();
  }

  return (is_float) ? Token{TokenType::NUMBER_FLOAT,
                            source.substr(start, current - start), line}
                    : Token{TokenType::NUMBER_INT,
                            source.substr(start, current - start), line};
}

XX::Token XX::Scanner::scanToken() {
  skipWhitespace();

  start = current;

  if (isAtEnd())
    return Token{TokenType::TOKEN_EOF, "", line};

  char c = advance();

  switch (c) {
  case '+':
    return Token{TokenType::PLUS, "+", line};
  case '-':
    return Token{TokenType::MINUS, "-", line};
  case '*':
    return Token{TokenType::STAR, "*", line};
  case '/':
    return Token{TokenType::SLASH, "/", line};
  case '(':
    return Token{TokenType::LEFT_PAREN, "(", line};
  case ')':
    return Token{TokenType::RIGHT_PAREN, ")", line};
  case '{':
    return Token{TokenType::LEFT_BRACE, "{", line};
  case '}':
    return Token{TokenType::RIGHT_BRACE, "}", line};
  case ';':
    return Token{TokenType::SEMICOLON, ";", line};
  case ':':
    return Token{TokenType::COLON, ":", line};
  case '.':
    if (match('.'))
      return Token{TokenType::DOT_DOT, "..", line};
    return Token{TokenType::DOT, ".", line};
  case '=':
    if (match('='))
      return Token{TokenType::EQUAL_EQUAL, "==", line};
    return Token{TokenType::EQUAL, "=", line};
  case '!':
    if (match('='))
      return Token{TokenType::NOT_EQUAL, "!=", line};
    return Token{TokenType::NOT, "!", line};
  case '<':
    if (match('='))
      return Token{TokenType::LESS_EQUAL, "<=", line};
    return Token{TokenType::LESS, "<", line};
  case '>':
    if (match('='))
      return Token{TokenType::GREATER_EQUAL, ">=", line};
    return Token{TokenType::GREATER, ">", line};
  case '"':
    return string();
  default:
    if (isdigit(c))
      return digit();
  }

  return Token{TokenType::TOKEN_EOF, "", line};
}
