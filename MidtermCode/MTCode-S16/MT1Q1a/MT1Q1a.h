#pragma once
///////////////////////////////////////////////////////////////////////
// MT1Q1a.cpp - Node for AST                                         //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "ScopeStack.h"
/*
*  class needs to:
*  - hold all the properties needed for code analysis
*  - provide a way to access and modify the properties
*  - provide support for building AST
*/

class ASTNode
{
public:
  using iterator = std::vector<ASTNode*>::iterator;
  using Name = std::string;
  using Type = std::string;
  using Line = size_t;
  iterator begin();
  iterator end();

  ASTNode();
  ASTNode::ASTNode(const Type& type, const Name& name, Line start, Line end=0);
  Name& name();
  Type& type();
  Line& startLine();
  Line& endLine();
  void addChild(ASTNode* node);
  std::vector<ASTNode*> children() { return _children; }
  ASTNode* operator[](size_t n);
  const ASTNode* operator[](size_t n) const;
  void clear();
  size_t size();
  void makeChildAndPush(ScopeStack<ASTNode*>& ss);
  static void AddLineCountAndPop(ScopeStack<ASTNode*>& ss, size_t linecount);
private:
  std::vector<ASTNode*> _children;
  Name _name;
  Type _type;
  Line _startLine;
  Line _endLine;
};
