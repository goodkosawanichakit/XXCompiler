#include "ast.hpp"
#include "astdump.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

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
