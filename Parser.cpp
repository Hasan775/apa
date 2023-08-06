#include "Parser.h"

map<string, TokenType> tokentypes;

Parser::Parser(vector<Token> tokens){
    this->tokens = tokens;
    this->tok = tokens[0];
    tokentypes = GetTypes();
}
void Parser::UnexpectedToken(){
    Error::throwMessage("Unexpected token type: " + tok.type.name);
}
bool Parser::match(TokenType type){
    if (tok.type.name == type.name){
        return true;
    }
    return false;
}
bool Parser::match(TokenType type, string value){
    if (tok.type.name == type.name && tok.value == value){
        return true;
    }
    return false;
}
void Parser::require(TokenType type){
    if (match(type)){
        next();
    }
    else{
        UnexpectedToken();
    }
}
void Parser::require(TokenType type, string value){
    if (match(type, value)){
        next();
    }
    else{
        UnexpectedToken();
    }
}
bool Parser::isEOF(){
    if (pos >= tokens.size()){
        return true;
    }
    return false;
}
Token Parser::next(){
    if (!isEOF()){
        pos += 1;
        if (pos < tokens.size()){
            tok = tokens[pos];
            return tok;
        }
        return tok;
    }
    else{
        Error::throwMessage("There is no more tokens in file");
        pos += 1;
        return tokens[pos - 1];
    }
}
Token Parser::peek(){
    if (!isEOF()){
        return tokens[pos + 1];
    }
    else{
        Error::throwMessage("There is no more tokens in file");
        return tokens[pos];
    }
}
vector<shared_ptr<Node>> Parser::parseTopLevel(){
    vector<shared_ptr<Node>> prog = {};
    while (!isEOF())
    {
        prog.push_back(parsePart());
        require(tokentypes["PUNC"]);
    }
    return prog;
}
shared_ptr<Node> Parser::parsePart(){
    auto token = parseAtom();
    shared_ptr<Node> expr = {};
    expr = maybeBinary(token);
    return expr;
}
shared_ptr<Node> Parser::parseAtom(){
    if (match(tokentypes["NUMBER"])){
        return parseNumber();
    }
    if (match(tokentypes["VAR"])){
        return parseVariable();
    }
    cout<<"1";
    UnexpectedToken();
    return nullptr;
}
shared_ptr<Node> Parser::parseNumber(){
    auto num = make_shared<NumberNode>(stoi(tok.value));
    next();
    return num;
}
shared_ptr<Node> Parser::parseVariable(){
    auto num = make_shared<VariableNode>(tok.value);
    next();
    return num;
}
shared_ptr<Node> Parser::maybeBinary(shared_ptr<Node> left){
    if(!match(tokentypes["OP"]) && !match(tokentypes["ASSIGN"])){
        return left;
    }
    auto oper = tok;
    next();
    auto right = parsePart();
    return make_shared<BinaryOperationNode>(left, right, oper.value);
}