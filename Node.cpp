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
shared_ptr<StringNode> Node::getNode(StringNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this methodh");
    return nullptr;
}
shared_ptr<BoolNode> Node::getNode(BoolNode* node){
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
shared_ptr<FunctionNode> Node::getNode(FunctionNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<IfNode> Node::getNode(IfNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<CycleNode> Node::getNode(CycleNode* node){
    delete node;
    Error::throwMessage("This node type can't access to this method");
    return nullptr;
}
shared_ptr<ReturnNode> Node::getNode(ReturnNode* node){
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


//StringNode class
shared_ptr<StringNode> StringNode::getNode(StringNode* node){
    delete node;
    auto expr = make_shared<StringNode>(value);
    return expr;
}
StringNode::StringNode(){
    this->type = StringN;
}
StringNode::StringNode(string value){
    this->type = StringN;
    this->value = value;
}


//BoolNode class
shared_ptr<BoolNode> BoolNode::getNode(BoolNode* node){
    delete node;
    auto expr = make_shared<BoolNode>(value);
    return expr;
}
BoolNode::BoolNode(){
    this->type = BoolN;
}
BoolNode::BoolNode(bool value){
    this->type = BoolN;
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


//FunctionNode class
shared_ptr<FunctionNode> FunctionNode::getNode(FunctionNode* node){
    delete node;
    auto expr = make_shared<FunctionNode>(name, operands, body);
    return expr;
}
FunctionNode::FunctionNode(){
    this->type = FunctionN;
}
FunctionNode::FunctionNode(string name, vector<shared_ptr<Node>> operands, vector<shared_ptr<Node>> body){
    this->type = FunctionN;
    this->name = name;
    this->operands = operands;
    this->body = body;
}


//IfNode class
shared_ptr<IfNode> IfNode::getNode(IfNode* node){
    delete node;
    auto expr = make_shared<IfNode>(cond, body, els);
    return expr;
}
IfNode::IfNode(){
    this->type = IfN;
}
IfNode::IfNode(shared_ptr<Node> cond, vector<shared_ptr<Node>> body){
    this->type = IfN;
    this->cond = cond;
    this->body = body;
}
IfNode::IfNode(shared_ptr<Node> cond, vector<shared_ptr<Node>> body, vector<shared_ptr<Node>> els){
    this->type = IfN;
    this->cond = cond;
    this->body = body;
    this->els = els;
}


//CycleNode class
shared_ptr<CycleNode> CycleNode::getNode(CycleNode* node){
    delete node;
    auto expr = make_shared<CycleNode>(name, cond, body);
    return expr;
}
CycleNode::CycleNode(){
    this->type = CycleN;
}
CycleNode::CycleNode(string name, vector<shared_ptr<Node>> cond, vector<shared_ptr<Node>> body){
    this->type = CycleN;
    this->name = name;
    this->cond = cond;
    this->body = body;
}


//ReturnNode class
shared_ptr<ReturnNode> ReturnNode::getNode(ReturnNode* node){
    delete node;
    auto expr = make_shared<ReturnNode>(statement);
    return expr;
}
ReturnNode::ReturnNode(){
    this->type = ReturnN;
}
ReturnNode::ReturnNode(shared_ptr<Node> statement){
    this->type = ReturnN;
    this->statement = statement;
}