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
    StringN,
    BoolN,
    BinaryOperationN,
    VariableN,
    CallN,
    IfN
};
class Node;
class ExpressionNode;
class NumberNode;
class StringNode;
class BoolNode;
class BinaryOperationNode;
class VariableNode;
class CallNode;
class IfNode;
class Node{
protected:
    NodeTypes type;
public:
    NodeTypes getType();
    virtual shared_ptr<ExpressionNode> getNode(ExpressionNode* node);
    virtual shared_ptr<NumberNode> getNode(NumberNode* node);
    virtual shared_ptr<StringNode> getNode(StringNode* node);
    virtual shared_ptr<BoolNode> getNode(BoolNode* node);
    virtual shared_ptr<BinaryOperationNode> getNode(BinaryOperationNode* node);
    virtual shared_ptr<VariableNode> getNode(VariableNode* node);
    virtual shared_ptr<CallNode> getNode(CallNode* node);
    virtual shared_ptr<IfNode> getNode(IfNode* node);
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
class StringNode : public Node{
public:
    string value;
    shared_ptr<StringNode> getNode(StringNode* node) override;
    StringNode();
    StringNode(string value);
};
class BoolNode : public Node{
public:
    bool value;
    shared_ptr<BoolNode> getNode(BoolNode* node) override;
    BoolNode();
    BoolNode(bool value);
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
class CallNode : public Node{
public:
    string name;
    vector<shared_ptr<Node>> operands;
    shared_ptr<CallNode> getNode(CallNode* node) override;
    CallNode();
    CallNode(string name, vector<shared_ptr<Node>> operands);
};
class IfNode : public Node{
public:
    shared_ptr<Node> cond;
    vector<shared_ptr<Node>> body;
    vector<shared_ptr<Node>> els;
    shared_ptr<IfNode> getNode(IfNode* node) override;
    IfNode();
    IfNode(shared_ptr<Node> cond, vector<shared_ptr<Node>> body, vector<shared_ptr<Node>> els);
};