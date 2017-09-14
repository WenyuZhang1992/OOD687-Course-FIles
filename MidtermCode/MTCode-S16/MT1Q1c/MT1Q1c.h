#pragma once
///////////////////////////////////////////////////////////////////////
// MT1Q1c.h - Node for AST (another alternate version)               //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>
#include <string>
#include "ScopeStack.h"
/*
 *  Note that we don't need a destructor because std::shared_ptr<T> has correct
 *  destruction semantics.
 */
struct ASTNode
{
  using Name = std::string;
  using Type = std::string;
  using line = size_t;
  using SPtr = std::shared_ptr<ASTNode>;
  using iterator = std::vector<SPtr>::iterator;

  ASTNode(const Type& type, const Name& name, line startLine)
    : _type(type), _name(name), _startLine(startLine), _endLine(0) {}
  ~ASTNode();

  // disable copy and assignment - would generate two trees sharing same nodes

  ASTNode(const ASTNode&) = delete;
  ASTNode& operator=(const ASTNode&) = delete;

  // support for managing children

  iterator begin() { return _children.begin(); }
  iterator end() { return _children.end(); }
  void addChild(SPtr pNode);

  // support for building AST with ScopeStack<SPtr>

  static void makeChildAndPush(ScopeStack<SPtr>& ss, SPtr pNode);
  static void addLineCountAndPop(ScopeStack<SPtr>& ss, line endLine);

  // Node properties

  std::vector<SPtr> _children;
  Name _name;
  Type _type;
  line _startLine;
  line _endLine;
};

inline ASTNode::~ASTNode()  // don't need except for enunciation 
{ 
  std::cout << "\n  destroying " << _type << " " << _name; 
}

inline void ASTNode::addChild(SPtr pNode) { _children.push_back(pNode); }

inline void ASTNode::makeChildAndPush(ScopeStack<SPtr>& ss, SPtr pNode)
{
  ss.top()->_children.push_back(pNode);
  ss.push(pNode);
}

inline void ASTNode::addLineCountAndPop(ScopeStack<SPtr>& ss, line endLine)
{
  ss.top()->_endLine = endLine;
  ss.pop();
}

std::string showTitle();

std::string show(ASTNode::SPtr pNode, bool all = true);

