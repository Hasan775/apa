#include "Node.h"
using namespace std;
//Node class
NodeTypes Node::getType(){
    return type;
}
shared_ptr<ExpressionNode> Node::getNode(ExpressionNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<NumberNode> Node::getNode(NumberNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this methodh");
    return nullptr;
}
shared_ptr<BinaryOperationNode> Node::getNode(BinaryOperationNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<VariableNode> Node::getNode(VariableNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<CallNode> Node::getNode(CallNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}


//ExpressionNode class
shared_ptr<ExpressionNode> ExpressionNode::getNode(ExpressionNode* node){
    delete node;
    auto expr = make_shared<ExpressionNode>(nodes);
    return expr;
}
ExpressionNode::ExpressionNode(){
    this->type = ExpressinN;
}
ExpressionNode::ExpressionNode(vector<shared_ptr<Node>> nodes){
    this->type = ExpressinN;
    this->nodes = nodes;
}


//NumberNode class
shared_ptr<NumberNode> NumberNode::getNode(NumberNode* node){
    delete node;
    auto expr = make_shared<NumberNode>(value);
    return expr;
}
NumberNode::NumberNode(){
    this->type = NumberN;
}
NumberNode::NumberNode(int value){
    this->type = NumberN;
    this->value = value;
}


//BinaryOperationNode class
shared_ptr<BinaryOperationNode> BinaryOperationNode::getNode(BinaryOperationNode* node){
    delete node;
    auto expr = make_shared<BinaryOperationNode>(left, right, op);
    return expr;
}
BinaryOperationNode::BinaryOperationNode(){
    this->type = BinaryOperationN;
}
BinaryOperationNode::BinaryOperationNode(shared_ptr<Node> left, shared_ptr<Node> right, string op){
    this->type = BinaryOperationN;
    this->left = left;
    this->right = right;
    this->op = op;
}


//VariableNode class
shared_ptr<VariableNode> VariableNode::getNode(VariableNode* node){
    delete node;
    auto expr = make_shared<VariableNode>(name);
    return expr;
}
VariableNode::VariableNode(){
    this->type = VariableN;
}
VariableNode::VariableNode(string name){
    this->type = VariableN;
    this->name = name;
}


//CallNode class
shared_ptr<CallNode> CallNode::getNode(CallNode* node){
    delete node;
    auto expr = make_shared<CallNode>(name, operands);
    return expr;
}
CallNode::CallNode(){
    this->type = CallN;
}
CallNode::CallNode(string name, vector<shared_ptr<Node>> operands){
    this->type = CallN;
    this->name = name;
    this->operands = operands;
}