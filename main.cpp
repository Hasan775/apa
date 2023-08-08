#include <iostream>
#include <regex>
#include <string>
#include "Lexer.h"
#include "Token.h"
#include "Node.h"
#include "Parser.h"
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
}
int main(){
    Lexer lexer = Lexer();
    string code = "5 = 6 + 7;\nvariable = 5 + 7 * 3 + 1;";
    lexer.code = code;
    vector<Token> tokens = lexer.lexAnalysis();
    tokens = lexer.FilterTokens(tokens);
    for (auto i : tokens){
        cout<<"["<<i.type.name<<": "<<i.value<<"]"<<"\n";
    }
    Parser parser = Parser(tokens);
    vector<shared_ptr<Node>> vn= parser.parseTopLevel();
    shared_ptr<Node> n4 = make_shared<ExpressionNode>(vn);
    cout<<"{\n";
    printAST(n4, "    ");
    cout<<"}";
}