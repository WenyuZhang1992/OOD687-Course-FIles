///////////////////////////////////////////////////////////////////////
// MT5Q2.cpp - AST Node declaration                                  //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include "../Utilities/Utilities.h"

///////////////////////////////////////////////////////////
// solution starts here
/*
 *   Only reason for deleted operations is to avoid
 *   sharing child pointers between source and target.
 */
struct ASTNode
{
  using Type = std::string;
  using Name = std::string;
  using Line = size_t;
  using Children = std::vector<ASTNode*>;

  ASTNode(const Type& type, const Name& name, Line start, Line end) 
    : type(type), name(name), startLine(start), endLine(end) {}
  ASTNode(const ASTNode&) = delete;
  ASTNode& operator=(const ASTNode&) = delete;

  Type type;
  Name name;
  Line startLine;
  Line endLine;
  Children children;
};
// solution ends here
///////////////////////////////////////////////////////////

template<typename Node>
class AST
{
public:
  AST() {}
  Node*& root() { return _pRoot; }
  AST(const AST&) = delete;
  AST& operator=(const AST&) = delete;
  // other stuff
private:
  Node* _pRoot = nullptr;
};
///////////////////////////////////////////////////////////
// solution starts here
//
// Assumes that:
// - AST nodes are stored on the heap
// - AST node children are pointers to nodes on heap
//   stored in an iterable collection

template<typename Node, typename CallObj>
void TreeWalk(Node* pNode, CallObj& co, size_t indent)
{
  ++indent;
  co(pNode, indent);
  for (auto pChild : pNode->children)
    TreeWalk(pChild, co, indent);
  --indent;
}
// solution ends here
///////////////////////////////////////////////////////////

void display(ASTNode* pNode, size_t indent)
{
  std::cout << "\n  " << std::string(2 * indent, ' ');
  std::cout << pNode->type << ", " << pNode->name << ": "
            << pNode->startLine << ", " << pNode->endLine
            << ", #children = " << pNode->children.size();
}

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT5Q2 - Walking AST Tree");
  putline();

  ASTNode* pRoot = new ASTNode{ "namespace", "GlobalNameSpace", 1, 80 };
  ASTNode* pFunc = new ASTNode{ "function", "func", 20, 68 };
  (pRoot->children).push_back(pFunc);
  ASTNode* pIf = new ASTNode{ "if", "anonymous", 35, 52 };
  pFunc->children.push_back(pIf);
  ASTNode* pFor = new ASTNode{ "for", "anonymous", 40, 50 };
  pIf->children.push_back(pFor);
  ASTNode* pWhile = new ASTNode{ "while", "anonymous", 55, 65 };
  pFunc->children.push_back(pWhile);

  std::function<void(ASTNode*, size_t)> f = [](ASTNode* pNode, size_t ignore)
  {
    if (pNode->type == "function")
      std::cout << "\n  " << pNode->name << ": size is " << pNode->endLine - pNode->startLine + 1;
  };
  AST<ASTNode> ast;
  ast.root() = pRoot;
  TreeWalk(ast.root(), display, 0);
  putline();

  TreeWalk(ast.root(), f, 0);

  std::cout << "\n\n";
}
