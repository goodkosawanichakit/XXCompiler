#include "scanner.hpp"

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

Scanner scanner;

static bool isAtEnd() { return *scanner.current == '\0'; }

static void initScanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

compiler::Token scanToken() {
  scanner.start = scanner.current;
  while (!isAtEnd()) {
  }
}
