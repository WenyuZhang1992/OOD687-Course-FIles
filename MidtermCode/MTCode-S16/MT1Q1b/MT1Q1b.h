#pragma once
///////////////////////////////////////////////////////////////////////
// MT1Q1b.h - Node for AST (alternate version)                       //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "ScopeStack.h"

struct ASTNode
{
  using Type = std::string;
  using Name = std::string;
  using line = size_t;
  using iterator = std::vector<ASTNode*>::iterator;

  iterator begin();
  iterator end();

  ASTNode();
  ASTNode(const Type& type, const Name& name, line start) 
    : type(type), name(name), startLine(start) {}
  ASTNode(const ASTNode&) = delete;
  ASTNode& operator=(const ASTNode&) = delete;
  ~ASTNode();

  void addChild(ASTNode* pNode);
  void makeChildAndPush(ScopeStack<ASTNode*>& ss);
  static void AddLineCountAndPop(ScopeStack<ASTNode*>& ss, size_t linecount);
  
  ASTNode* operator[](size_t n);
  const ASTNode* const operator[](size_t n) const;
  void clear();
  size_t size();

  std::vector<ASTNode*> children;
  Name name;
  Type type;
  line startLine;
  line endLine;
};

std::string showNode(ASTNode* pNode);
