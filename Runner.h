#include <any>
#include<vector>
#include <map>
#include <type_traits>
#include"Node.h"
class Runner{
public:
    map<string, any> variables;
    any run(shared_ptr<Node> node){
        if (node->getType() == ExpressinN){
            auto n = node->getNode(new ExpressionNode);
            for(auto no : n->nodes){
                run(no);
            }
            return 0;
        }
        else if (node->getType() == NumberN){
            auto n = node->getNode(new NumberNode);
            return n->value;
        }
        else if (node->getType() == StringN){
            auto n = node->getNode(new StringNode);
            return n->value;
        }
        else if (node->getType() == BoolN){
            auto n = node->getNode(new BoolNode);
            return n->value;
        }
        else if (node->getType() == BinaryOperationN){
            auto n = node->getNode(new BinaryOperationNode);
            return runBinary(n);
        }
        else if (node->getType() == VariableN){
            auto n = node->getNode(new VariableNode);
            return GetVariable(n->name);
        }
        else if (node->getType() == CallN){
            auto n = node->getNode(new CallNode);
            return runCall(n);
        }
        return 0;
    }
    any runBinary(shared_ptr<BinaryOperationNode> node){
        if (node->op == "="){
            if (node->left->getType() != VariableN){
                Error::throwMessage("Can't assign anything to a non-variable");
                return 0;
            }
            shared_ptr<VariableNode> var = node->left->getNode(new VariableNode);
            SetVariable(var->name, run(node->right));
            return 0;
        }
        any left = run(node->left);
        any right = run(node->right);
        if (left.type().name() != right.type().name()){
            Error::throwMessage("Can't operate with anything with different types");
        }
        any res;
        if (left.type().name() == typeid(int).name()){
            res = evalute(any_cast<int>(left), any_cast<int>(right), node->op);
        }
        else if (left.type().name() == typeid(string).name()){
            res = evalute(any_cast<string>(left), any_cast<string>(right), node->op);
        }
        else{
            Error::throwMessage("Can't do any operation with this type");
        }
        return res;
    }
    any evalute(int left, int right, string op){
        if (op == "+"){
            return left + right;
        }
        else if (op == "-"){
            return left - right;
        }
        else if (op == "*"){
            return left * right;
        }
        else if (op == ">"){
            return left > right;
        }
        else if (op == "<"){
            return left < right;
        }
        else if (op == ">="){
            return left >= right;
        }
        else if (op == "<="){
            return left <= right;
        }
        else if (op == "=="){
            return left == right;
        }
        else{
            return left / right;
        }
    }
    any evalute(string left, string right, string op){
        if (op == "+"){
            return left + right;
        }
        else{
            Error::throwMessage("You can't do this operation with string");
            return 0;
        }
    }
    void SetVariable(string name, any value){
        variables[name] = value;
    }
    any GetVariable(string name){
        return variables[name];
    }
    any runCall(shared_ptr<CallNode> call){
        if (call->name == "print"){
            any arg = run(call->operands[0]);
            if (arg.type().name() == typeid(int).name()){
                cout<<any_cast<int>(arg);
            }
            else if (arg.type().name() == typeid(string).name()){
                cout<<any_cast<string>(arg);
            }
            else if (arg.type().name() == typeid(bool).name()){
                cout<<any_cast<bool>(arg);
            }
        }
        if (call->name == "input"){
            string read;
            cin>>read;
            return read;
        }
        return 0;
    }
};