#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "Token.h"
#include "Node.h"
#include "Parser.h"
#include "Runner.h"
using namespace std;
void printAST(shared_ptr<Node> n, string offset){
    cout<<offset<<"type: "<<n->getType()<<",\n";
    if (n->getType() == ExpressinN){
        shared_ptr<ExpressionNode> node = n->getNode(new ExpressionNode());
        cout<<offset<<"body: ["<<"\n";
        for (shared_ptr<Node> no : node->nodes){
            cout<<offset<<"{"<<"\n";
            printAST(no, offset + "    ");
            cout<<offset<<"},"<<"\n";
        }
        cout<<offset<<"]"<<"\n";
    }
    else if (n->getType() == NumberN){
        shared_ptr<NumberNode> node = n->getNode(new NumberNode());
        cout<<offset<<"value: "<<node->value<<"\n";
    }
    else if (n->getType() == StringN){
        shared_ptr<StringNode> node = n->getNode(new StringNode());
        cout<<offset<<"value: "<<node->value<<"\n";
    }
    else if (n->getType() == BoolN){
        shared_ptr<BoolNode> node = n->getNode(new BoolNode());
        cout<<offset<<"value: "<<node->value<<"\n";
    }
    else if (n->getType() == BinaryOperationN){
        shared_ptr<BinaryOperationNode> node = n->getNode(new BinaryOperationNode());
        cout<<offset<<"left: {\n";
        printAST(node->left, offset + "    ");
        cout<<offset<<"},\n";
        cout<<offset<<"right: {\n";
        printAST(node->right, offset + "    ");
        cout<<offset<<"},\n";
        cout<<offset<<"operator: "<<node->op<<"\n";
    }
    else if (n->getType() == VariableN){
        shared_ptr<VariableNode> node = n->getNode(new VariableNode());
        cout<<offset<<"name: "<<node->name<<",\n";
    }
    else if (n->getType() == CallN){
        shared_ptr<CallNode> node = n->getNode(new CallNode());
        cout<<offset<<"body: ["<<"\n";
        for (shared_ptr<Node> op : node->operands){
            cout<<offset<<"{"<<"\n";
            printAST(op, offset + "    ");
            cout<<offset<<"},"<<"\n";
        }
        cout<<offset<<"]"<<"\n";
    }
    else if (n->getType() == IfN){
        shared_ptr<IfNode> node = n->getNode(new IfNode());
        cout<<offset<<"condition: {"<<"\n";
        printAST(node->cond, offset + "    ");
        cout<<offset<<"},"<<"\n";
        cout<<offset<<"body: ["<<"\n";
        for (shared_ptr<Node> bo : node->body){
            cout<<offset<<"{"<<"\n";
            printAST(bo, offset + "    ");
            cout<<offset<<"},"<<"\n";
        }
        for (shared_ptr<Node> e : node->els){
            cout<<offset<<"{"<<"\n";
            printAST(e, offset + "    ");
            cout<<offset<<"},"<<"\n";
        }
        cout<<offset<<"]"<<"\n";
    }
}
string ReadFile(){
    string line, code = "";

    ifstream File;
    File.open("../code.txt");
    while (File) {
        code += File.get();
    }
    File.close();
    return code.substr(0, code.size() - 1);
}
int main(){
    Lexer lexer = Lexer();
    string code = ReadFile();
    lexer.code = code;
    vector<Token> tokens = lexer.lexAnalysis();
    tokens = lexer.FilterTokens(tokens);
    Parser parser = Parser(tokens);
    vector<shared_ptr<Node>> vn= parser.parseTopLevel();
    shared_ptr<Node> exprn = make_shared<ExpressionNode>(vn);
    Runner runner = Runner();
    cout<<"\n";
    runner.run(exprn);
}