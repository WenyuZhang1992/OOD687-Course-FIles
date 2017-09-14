///////////////////////////////////////////////////////////////////////
// MT1Q1a.cpp - Node for AST                                         //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include "MT1Q1a.h"
#include "../Utilities/Utilities.h"

ASTNode::ASTNode()
{
  _name = "";
  _type = "anonymous";
  _startLine = 0;
  _endLine = 0;
}

ASTNode::ASTNode(const Type& type, const Name& name, Line start, Line end)
{
  _name = name;
  _type = type;
  _startLine = start;
  _endLine = end;
}

std::string& ASTNode::name() { return _name; }
std::string& ASTNode::type() { return _type; }
size_t& ASTNode::startLine() { return _startLine; }
size_t& ASTNode::endLine() { return _endLine; }
ASTNode::iterator ASTNode::begin() { return _children.begin(); }
ASTNode::iterator ASTNode::end() { return _children.end(); }
void ASTNode::addChild(ASTNode* pNode) { _children.push_back(pNode); }

ASTNode* ASTNode::operator[](size_t n)
{
  if (n < 0 || _children.size() <= n)
    throw(std::exception("index out of range"));
  return _children[n];
}

const ASTNode* ASTNode::operator[](size_t n) const
{
  if (n < 0 || _children.size() <= n)
    throw(std::exception("index out of range"));
  return _children[n];
}

void ASTNode::clear() { _children.clear(); }
size_t ASTNode::size() { return _children.size(); }

void ASTNode::makeChildAndPush(ScopeStack<ASTNode*>& ss)
{
  ss.top()->_children.push_back(this);
  ss.push(this);
}

void ASTNode::AddLineCountAndPop(ScopeStack<ASTNode*>& ss, size_t linecount)
{
  ss.top()->endLine() = linecount;
  ss.pop();
}

std::string showNode(ASTNode* pNode)
{
  std::ostringstream out;
  out << "\n  ASTNode " << pNode->name();
  out << "\n    type = " << pNode->type();
  out << "\n    start line = " << pNode->startLine();
  out << "\n    size = " << pNode->endLine() - pNode->startLine() + 1;
  out << "\n    number of children = " << pNode->size();
  out << "\n";
  return out.str();
}

#ifdef TEST_ASTNODE

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT1Q1a - Demonstrating AST Node class");

  ScopeStack<ASTNode*> ss;

  // global namespace

  ASTNode* pGNS = new ASTNode("namespace", "GNS", 1);
  ss.push(pGNS);

  // function

  ASTNode* pFun = new ASTNode("function", "fun", 73);
  pFun->makeChildAndPush(ss);

  // if is child of function

  ASTNode* pIf = new ASTNode("if", "", 76);
  pIf->makeChildAndPush(ss);

  // for is child of if

  ASTNode* pFor = new ASTNode("for", "", 80);
  pFor->makeChildAndPush(ss);

  // end of for

  ASTNode::AddLineCountAndPop(ss, 93);

  // end of if

  ASTNode::AddLineCountAndPop(ss, 102);

  // while is child of function

  ASTNode* pWhile = new ASTNode("while", "", 96);
  pWhile->makeChildAndPush(ss);

  // end of while

  ASTNode::AddLineCountAndPop(ss, 120);

  // finished function

  ASTNode::AddLineCountAndPop(ss, 125);

  std::cout << showNode(pGNS);
  std::cout << showNode(pFun);
  std::cout << showNode(pIf);
  std::cout << showNode(pFor);
  std::cout << showNode(pWhile);

  std::cout << "\n  children of:\n" << showNode(pFun) << "\n  are:\n";
  for (auto pNode : *pFun)
    std::cout << showNode(pNode);

  std::cout << "\n\n";
}

#endif
