#pragma once

#include <cstdint>
#include <string>

namespace XX::AST {

enum class Kind { EXPR, BINARY_EXPR, INT_LITERAL, FLOAT_LITERAL, VAR_DECLR };

enum class Type {
  INT8,
  INT16,
  INT32,
  INT64,
  FLOAT8,
  FLOAT16,
  FLOAT32,
  FLOAT64
};

// base class of all Node idk it's just that, do I really need to comment?
class Node {
private:
  Kind kind;
  uint32_t offset;
  uint16_t length;

public:
  inline int getOffset() { return offset; }
  inline int getLength() { return length; }
  inline Kind getKind() { return kind; }

  Node(Kind k, uint32_t o, uint16_t l) : kind(k), offset(o), length(l) {}
  ~Node() {}
};

// Expr class and yeah the name already told it propose.
class Expr : public Node {
public:
  using Node::Node;
  ~Expr() {}
};

// it's a statement duh.
class Stmt : public Node {
public:
  using Node::Node;
  ~Stmt() {}
};

// yet again the name already told it propose.
// anyway is op as a char is really a good choice?
// man I'll never leave the project for 1 month ever again, I surely forgot
// everything
class BinaryExpr : public Expr {
private:
  char op;
  Expr *LExpr;
  Expr *RExpr;

public:
  inline char getOP() { return op; }
  inline Expr *getLExpr() { return LExpr; }
  inline Expr *getRExpr() { return RExpr; }

  BinaryExpr(uint32_t o, uint16_t l, char op, Expr *lexpr, Expr *rexpr)
      : Expr(Kind::BINARY_EXPR, o, l), op(op), LExpr(lexpr), RExpr(rexpr) {}

  ~BinaryExpr() {}
};

// why do I store in int64_t bruh.
// cause it's the maximum that we can use?
// anyways to remind future me this is the terminal of BNF ,FloatLiteral too
class IntLiteral : public Expr {
private:
  int64_t value;

public:
  inline int64_t getValue() { return value; }

  IntLiteral(uint32_t o, uint16_t l, int64_t v)
      : Expr(Kind::INT_LITERAL, o, l), value(v) {}

  ~IntLiteral() {}
};

class FloatLiteral : public Expr {
private:
  double value;

public:
  inline double getValue() { return value; }

  FloatLiteral(uint32_t o, uint16_t l, double v)
      : Expr(Kind::FLOAT_LITERAL, o, l), value(v) {}

  ~FloatLiteral() {}
};

class VarDeclr : public Stmt {
private:
  Type type;
  std::string varName;
  Expr
      *whatShouldInameIt; // What should I name this variable???? English 2 / 10

public:
  inline Type getType() { return type; }
  inline std::string getVarName() { return varName; }
  inline Expr *getExpr() { return whatShouldInameIt; }

  VarDeclr(uint32_t o, uint16_t l, Type t, std::string n, Expr *init)
      : Stmt(Kind::VAR_DECLR, o, l), type(t), varName(n),
        whatShouldInameIt(init) {}
  ~VarDeclr() {}
};

} // namespace XX::AST
