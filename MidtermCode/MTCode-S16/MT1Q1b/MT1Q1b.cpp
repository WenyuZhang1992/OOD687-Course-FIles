///////////////////////////////////////////////////////////////////////
// MT1Q1b.cpp - Node for AST (alternate version)                     //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "MT1Q1b.h"
#include "../Utilities/Utilities.h"

ASTNode::ASTNode()
{
  name = "";  type = "anonymous";  startLine = 0;  endLine = 0;
}

ASTNode::~ASTNode()
{
  for (auto pNode : children)
    delete pNode;
}

ASTNode::iterator ASTNode::begin() { return children.begin(); }

ASTNode::iterator ASTNode::end() { return children.end(); }

void ASTNode::addChild(ASTNode* pNode) { children.push_back(pNode); }

void ASTNode::makeChildAndPush(ScopeStack<ASTNode*>& ss)
{
  ss.top()->children.push_back(this);
  ss.push(this);
}

void ASTNode::AddLineCountAndPop(ScopeStack<ASTNode*>& ss, size_t linecount)
{
  ss.top()->endLine = linecount;
  ss.pop();
}

ASTNode* ASTNode::operator[](size_t n)
{
  if (n < 0 || children.size() <= n)
    throw(std::exception("index out of range"));
  return children[n];
}

const ASTNode* const ASTNode::operator[](size_t n) const
{
  if (n < 0 || children.size() <= n)
    throw(std::exception("index out of range"));
  return children[n];
}

void ASTNode::clear() { children.clear(); }
size_t ASTNode::size() { return children.size(); }

std::string showNode(ASTNode* pNode)
{
  std::ostringstream out;
  out << "\n  ASTNode " << pNode->name;
  out << "\n    type = " << pNode->type;
  out << "\n    start line = " << pNode->startLine;
  out << "\n    size = " << pNode->endLine - pNode->startLine + 1;
  out << "\n    number of children = " << pNode->size();
  out << "\n";
  return out.str();
}

#ifdef TEST_ASTNODE

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT1Q1b - Demonstrating AST Node class");

  ScopeStack<ASTNode*> ss;

  // global namespace

  ASTNode* pGNS = new ASTNode("namespace", "GNS", 1);
  ss.push(pGNS);

  // function

  ASTNode* pN1 = new ASTNode("function", "fun", 73);
  pN1->makeChildAndPush(ss);

  // if is child of function

  ASTNode* pN2 = new ASTNode("if", "", 76);
  pN2->makeChildAndPush(ss);

  // for is child of if

  ASTNode* pN3 = new ASTNode("for", "", 80);
  pN3->makeChildAndPush(ss);

  // end of for

  ASTNode::AddLineCountAndPop(ss, 93);

  // end of if

  ASTNode::AddLineCountAndPop(ss, 102);

  // while is child of function

  ASTNode* pN4 = new ASTNode("while", "", 96);
  pN4->makeChildAndPush(ss);

  // end of while

  ASTNode::AddLineCountAndPop(ss, 120);
  
  // finished function

  ASTNode::AddLineCountAndPop(ss, 125);

  std::cout << showNode(pN1);
  std::cout << showNode(pN2);
  std::cout << showNode(pN3);
  std::cout << showNode(pN4);

  std::cout << "\n  children of:\n" << showNode(pN1) << "\n  are:\n";
  for (auto pNode : *pN1)
    std::cout << showNode(pNode);

  std::cout << "\n\n";
}

#endif
