#pragma once

#include "ast.hpp"
#include <vector>

namespace XX::AST {
class Dumper {
private:
  const std::vector<uint32_t> &lineOffset;

  void dumpFloatLiteral(FloatLiteral *node);
  void dumpIntLiteral(IntLiteral *node);
  void dumpBinaryExpr(BinaryExpr *node);
  void dumpExpr(Expr *node);
  void dumpVarDeclr(VarDeclr *node);
  uint32_t getLine(uint32_t of);

public:
  void dump(Node *node);
  Dumper(const std::vector<uint32_t> &l) : lineOffset(l) {}
  ~Dumper() {}
};
}; // namespace XX::AST
