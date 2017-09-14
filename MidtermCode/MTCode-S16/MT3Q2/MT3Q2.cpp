///////////////////////////////////////////////////////////////////////
// MT3Q2.cpp - Abstract Syntax Tree declaration                      //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <functional>
#include "../MT1Q1b/MT1Q1b.h"        // defines ASTNode, used in main()
#include "../Utilities/Utilities.h"
/*
 * Destructor is declared virtual so that a designer can create
 * a derived AST that might, perhaps, include a ScopeStack<Node>
 * as a data member and include functions for building the tree.
 *
 * I chose to put that support in the ASTNode class.
 */
template <typename Node>
class AST
{
public:
  AST() {}
  AST(const AST&) = delete;
  AST& operator=(const AST&) = delete;
  Node*& root();
  template <typename CallObj>
  void walk(CallObj& co);
  template <typename CallObj>
  void walk(Node* pNode, CallObj& co);
  size_t indent() { return _indent; }
  virtual ~AST() { delete _pRoot; }
private:
  ASTNode* _pRoot = nullptr;
  size_t _indent = 0;
};

template<typename Node>
Node*& AST<Node>::root()
{
  return _pRoot;
}

template <typename Node>
template <typename CallObj>
void AST<Node>::walk(Node* pNode, CallObj& co)
{
  co(pNode);
  _indent += 2;
  for (auto ptrNode : pNode->children)
    walk(ptrNode, co);
  _indent -= 2;
}

template<typename Node>
template<typename CallObj>
void AST<Node>::walk(CallObj& co)
{
  _indent = 0;
  walk(_pRoot, co);
}

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT3Q2 - Demonstrating AST class");

  ASTNode* pN1 = new ASTNode;  // see MT1Q1a, or b, or c for more
  pN1->name = "fun";           // elegant way of building AST linkage
  pN1->type = "function";
  pN1->startLine = 73;
  pN1->endLine = 125;

  ASTNode* pN2 = new ASTNode;
  pN2->name = "";
  pN2->type = "if";
  pN2->startLine = 76;
  pN2->endLine = 102;

  ASTNode* pN3 = new ASTNode;
  pN3->name = "";
  pN3->type = "for";
  pN3->startLine = 80;
  pN3->endLine = 93;

  ASTNode* pN4 = new ASTNode;
  pN4->name = "";
  pN4->type = "while";
  pN4->startLine = 96;
  pN4->endLine = 120;

  pN1->addChild(pN2);
  pN2->addChild(pN3);
  pN1->addChild(pN4);

  std::cout << showNode(pN1);
  std::cout << showNode(pN2);
  std::cout << showNode(pN3);
  std::cout << showNode(pN4);

  AST<ASTNode> ast;

  using CallType = std::function<void(ASTNode*)>;
  CallType co = [&ast](ASTNode* pNode)
  {
    std::string indenter(ast.indent(), char(32));
    std::cout << "\n  " << indenter.c_str() << "type = " << pNode->type;
  };
  ast.root() = pN1;
  
  Utils::title("walking the AST");
  ast.walk(co);
  std::cout << "\n\n";
}