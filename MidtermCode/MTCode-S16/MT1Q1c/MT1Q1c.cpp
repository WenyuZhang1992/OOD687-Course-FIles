///////////////////////////////////////////////////////////////////////
// MT1Q1c.cpp - Node for AST (another alternate version)             //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>
#include "MT1Q1c.h"
#include "../Utilities/Utilities.h"

using SPtr = ASTNode::SPtr;

template <typename NodePtr>
class AST
{
public:
  NodePtr& root() { return _pRoot; }
  template <typename CallObj>
  void walk(NodePtr pNode, CallObj& co);
private:
  size_t indent = 0;
  NodePtr _pRoot;
};

template <typename NodePtr>
template <typename CallObj>
void AST<NodePtr>::walk(NodePtr pNode, CallObj& co)
{
  co(pNode, indent);
  indent += 2;
  for (auto pChild : *pNode)
    walk(pChild, co);
  indent -= 2;
}

std::string showTitle()
{
  std::ostringstream out;
  out << std::left << "\n  ";
  out << std::setw(10) << "Type"
    << std::setw(10) << "Name"
    << std::setw(6) << "Start"
    << std::setw(6) << "End"
    << std::setw(10) << "#Children";
  out << std::left << "\n  ";
  out << std::setw(10) << "---------"
    << std::setw(10) << "---------"
    << std::setw(6) << "-----"
    << std::setw(6) << "-----"
    << std::setw(10) << "---------";
  return out.str();
}

std::string show(SPtr pNode, bool all)
{
  std::ostringstream out;
  out << std::left;
  out << std::setw(10) << pNode->_type
    << std::setw(10) << pNode->_name;
  if (all)
  {
    out << std::setw(6) << pNode->_startLine
      << std::setw(6) << pNode->_endLine
      << std::setw(10) << pNode->_children.size();
  }
  return out.str();
}

std::function<void(SPtr, size_t)> enunc = [](SPtr pNode, size_t indent)
{
  std::cout << "\n  " << std::string(indent, ' ') << show(pNode, false);
};

#ifdef TEST_ASTNODE

struct Cosmetic
{
  ~Cosmetic() { std::cout << "\n\n"; }
} cosmetic;

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT1Q1c - AST Node Demo");

  ScopeStack<SPtr> ss;
  AST<SPtr> ast;

  std::cout << "\n  " << showTitle();
  // global namespace

  SPtr pGNS = SPtr(new ASTNode("namespace", "GNS", 1));
  ast.root() = pGNS;
  ss.push(pGNS);
  std::cout << "\n  " << show(pGNS).c_str();

  // start function fun 73 : 125

  SPtr pFun = SPtr(new ASTNode("function", "fun", 73));
  ASTNode::makeChildAndPush(ss, pFun);
  std::cout << "\n  " << show(pFun).c_str();

  // start if 76 : 102

  SPtr pIf = SPtr(new ASTNode("if", "", 76));
  ASTNode::makeChildAndPush(ss, pIf);
  std::cout << "\n  " << show(pIf).c_str();

  // start for 80 : 93

  SPtr pFor = SPtr(new ASTNode("for", "", 80));
  ASTNode::makeChildAndPush(ss, pFor);
  std::cout << "\n  " << show(pFor).c_str();

  // end of for

  ASTNode::addLineCountAndPop(ss, 93);

  // end of if

  ASTNode::addLineCountAndPop(ss, 102);

  // start of while 105 : 120

  SPtr pWhile = SPtr(new ASTNode("while", "", 105));
  ASTNode::makeChildAndPush(ss, pWhile);
  std::cout << "\n  " << show(pWhile).c_str();

  // end of while

  ASTNode::addLineCountAndPop(ss, 120);

  // end of function

  ASTNode::addLineCountAndPop(ss, 125);

  // end of file

  ASTNode::addLineCountAndPop(ss, 150);

  std::cout << "\n";
  std::cout << "\n  walking the AST Tree:";
  std::cout << "\n -----------------------";

  ast.walk(pGNS, enunc);

  std::cout << "\n  " << showTitle();
  std::cout << "\n  " << show(pGNS,   true).c_str();
  std::cout << "\n  " << show(pFun,   true).c_str();
  std::cout << "\n  " << show(pIf,    true).c_str();
  std::cout << "\n  " << show(pFor,   true).c_str();
  std::cout << "\n  " << show(pWhile, true).c_str();

  std::cout << "\n";
}
#endif
