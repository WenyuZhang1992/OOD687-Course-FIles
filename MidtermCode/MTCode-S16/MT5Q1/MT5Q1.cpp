///////////////////////////////////////////////////////////////////////
// MT5Q1.cpp - AST Tree Walker function                              //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include "../Utilities/Utilities.h"

struct ASTNode
{
  std::string type;
  std::string name;
  // other stuff
  std::vector<ASTNode*> children;
};

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
  std::cout << pNode->type << ", " << pNode->name 
            << ", #children = " << pNode->children.size();
}

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT5Q1 - Walking AST Tree");
  putline();

  ASTNode* pRoot = new ASTNode { "namespace", "GlobalNameSpace" };
  ASTNode* pFunc = new ASTNode { "function", "func" };
  (pRoot->children).push_back(pFunc);
  ASTNode* pIf = new ASTNode{ "if", "anonymous" };
  pFunc->children.push_back(pIf);
  ASTNode* pFor = new ASTNode{ "for", "anonymous" };
  pIf->children.push_back(pFor);
  ASTNode* pWhile = new ASTNode{ "while", "anonymous" };
  pFunc->children.push_back(pWhile);

  AST<ASTNode> ast;
  ast.root() = pRoot;
  TreeWalk(ast.root(), display, 0);

  std::cout << "\n\n";
}
