#include "scanner.hpp"
#include <iostream>
#include <string>
#include <vector>

int tests_passed = 0;
int tests_failed = 0;

void testScanner(const std::string &test_name, const std::string &source,
                 const std::vector<XX::TokenType> &expected_tokens) {
  XX::Scanner scanner(source);

  for (size_t i = 0; i < expected_tokens.size(); ++i) {
    XX::Token token = scanner.scanToken();

    if (token.type != expected_tokens[i]) {
      std::cout << "[FAILED] " << test_name << " at token index " << i << "\n";
      std::cout << "  Expected type: " << static_cast<int>(expected_tokens[i])
                << ", Got: " << static_cast<int>(token.type) << " (Lexeme: '"
                << token.lexeme << "')\n";
      tests_failed++;
      return;
    }
  }

  XX::Token eof_token = scanner.scanToken();
  if (eof_token.type != XX::TokenType::TOKEN_EOF) {
    std::cout << "[FAILED] " << test_name << " did not end with TOKEN_EOF.\n";
    tests_failed++;
    return;
  }

  std::cout << "[OK] " << test_name << "\n";
  tests_passed++;
}

int main() {
  testScanner("Math Operators", "1 + 2.5 * 3",
              {XX::TokenType::NUMBER_INT, XX::TokenType::PLUS,
               XX::TokenType::NUMBER_FLOAT, XX::TokenType::STAR,
               XX::TokenType::NUMBER_INT});

  testScanner("Variable Declaration", "int x = 10;",
              {XX::TokenType::KW_INT, XX::TokenType::IDENTIFIER,
               XX::TokenType::EQUAL, XX::TokenType::NUMBER_INT,
               XX::TokenType::SEMICOLON});

  testScanner("Range Operator", "1..10",
              {XX::TokenType::NUMBER_INT, XX::TokenType::DOT_DOT,
               XX::TokenType::NUMBER_INT});

  std::cout << "\nTest Results: " << tests_passed << " Passed, " << tests_failed
            << " Failed.\n";
  return 0;
}
