#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <memory>
#include <any>
#include "Error.h"
using namespace std;
enum NodeTypes{
    ExpressinN,
    NumberN,
    BinaryOperationN,
    VariableN
};
class Node;
class ExpressionNode;
class NumberNode;
class BinaryOperationNode;
class VariableNode;
class Node{
protected:
    NodeTypes type;
public:
    NodeTypes getType();
    virtual shared_ptr<ExpressionNode> getNode(ExpressionNode* node);
    virtual shared_ptr<NumberNode> getNode(NumberNode* node);
    virtual shared_ptr<BinaryOperationNode> getNode(BinaryOperationNode* node);
    virtual shared_ptr<VariableNode> getNode(VariableNode* node);
};
class ExpressionNode : public Node{
public:
    vector<shared_ptr<Node>> nodes = {};
    shared_ptr<ExpressionNode> getNode(ExpressionNode* node) override;
    ExpressionNode();
    ExpressionNode(vector<shared_ptr<Node>> nodes);
};
class NumberNode : public Node{
public:
    int value;
    shared_ptr<NumberNode> getNode(NumberNode* node) override;
    NumberNode();
    NumberNode(int value);
};
class BinaryOperationNode : public Node{
public:
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    string op;
    shared_ptr<BinaryOperationNode> getNode(BinaryOperationNode* node) override;
    BinaryOperationNode();
    BinaryOperationNode(shared_ptr<Node> left, shared_ptr<Node> right, string op);
};
class VariableNode : public Node{
public:
    string name;
    shared_ptr<VariableNode> getNode(VariableNode* node) override;
    VariableNode();
    VariableNode(string name);
};