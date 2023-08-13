#include "Runner.h"
any Runner::run(shared_ptr<Node> node){
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
    else if (node->getType() == IfN){
        auto n = node->getNode(new IfNode);
        runIf(n);
    }
    else if (node->getType() == CycleN){
        auto n = node->getNode(new CycleNode);
        runCycle(n);
    }
    return 0;
}
any Runner::runBinary(shared_ptr<BinaryOperationNode> node){
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
    else if (left.type().name() == typeid(bool).name()){
        res = evalute(any_cast<bool>(left), any_cast<bool>(right), node->op);
    }
    else{
        Error::throwMessage("Can't do any operation with this type");
    }
    return res;
}
any Runner::evalute(int left, int right, string op){
    if (op == "+"){
        return left + right;
    }
    else if (op == "-"){
        return left - right;
    }
    else if (op == "*"){
        return left * right;
    }
    else if (op == "/"){
        return left / right;
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
    else {
        Error::throwMessage("You can't do this operation with string");
        return 0;
    }
}
any Runner::evalute(string left, string right, string op){
    if (op == "+"){
        return left + right;
    }
    else if (op == "=="){
        return left == right;
    }
    else{
        Error::throwMessage("You can't do this operation with string");
        return 0;
    }
}
any Runner::evalute(bool left, bool right, string op){
    if (op == "&&"){
        return left && right;
    }
    else if (op == "||"){
        return left || right;
    }
    else{
        Error::throwMessage("You can't do this operation with string");
        return 0;
    }
}
void Runner::SetVariable(string name, any value){
    variables[name] = value;
}
any Runner::GetVariable(string name){
    return variables[name];
}
any Runner::runCall(shared_ptr<CallNode> call){
    if (call->name == "print"){
        any arg = run(call->operands[0]);
        if (arg.type().name() == typeid(int).name()){
            cout<<any_cast<int>(arg)<<"\n";
        }
        else if (arg.type().name() == typeid(string).name()){
            cout<<any_cast<string>(arg)<<"\n";
        }
        else if (arg.type().name() == typeid(bool).name()){
            cout<<any_cast<bool>(arg)<<"\n";
        }
    }
    if (call->name == "input"){
        string read;
        cin>>read;
        return read;
    }
    if (call->name == "int"){
        any arg = run(call->operands[0]);
        if (arg.type().name() == typeid(string).name()){
            return stoi(any_cast<string>(arg));
        }
        else if (arg.type().name() == typeid(bool).name()){
            return any_cast<bool>(arg);
        }
    }
    return 0;
}
void Runner::runIf(shared_ptr<IfNode> node){
    any cond = run(node->cond);
    if (any_cast<bool>(cond)){
        for (auto expr : node->body){
            run(expr);
        }
    }
    else{
        for (auto expr : node->els){
            run(expr);
        }
    }
}
void Runner::runCycle(shared_ptr<CycleNode> node){
    if (node->name == "while"){
        while(any_cast<bool>(run(node->cond[0]))){
            for (auto expr : node->body){
                run(expr);
            }
        }
    }
    else if (node->name == "for"){
        run(node->cond[0]);
        while(any_cast<bool>(run(node->cond[1]))){
            for (auto expr : node->body){
                run(expr);
            }
            run(node->cond[2]);
        }
    }
}