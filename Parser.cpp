#include "Parser.h"

map<string, TokenType> tokentypes;
map<string, int> precedence;
map<string, int> GetPrecedence(){
    map<string, int> prec = {};
    prec["="] = 1;
    prec["+"] = 2;
    prec["-"] = 2;
    prec["*"] = 3;
    prec["/"] = 3;
    return prec;
}
Parser::Parser(vector<Token> tokens){
    this->tokens = tokens;
    this->tok = tokens[0];
    tokentypes = GetTypes();
    precedence = GetPrecedence();
}
void Parser::UnexpectedToken(){
    Error::throwMessage("Unexpected token type: " + tok.type.name +  to_string(pos));
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
void Parser::back(){
    if (pos != 0){
        pos -= 1;
        tok = tokens[pos];
    }
    else{
        Error::throwMessage("This is begin of file. You can't go back");
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
        cout<<"hi";
        require(tokentypes["PUNC"]);
    }
    return prog;
}
shared_ptr<Node> Parser::parsePart(){
    auto token = parseAtom();
    shared_ptr<Node> expr = {};
    expr = maybeBinary(token, 0);
    return expr;
}
shared_ptr<Node> Parser::parseAtom(){
    if (match(tokentypes["NUMBER"])){
        return parseNumber();
    }
    if (match(tokentypes["VAR"])){
        return parseVariable();
    }
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
shared_ptr<Node> Parser::maybeBinary(shared_ptr<Node> left, int befprec){
    if(!match(tokentypes["OP"]) && !match(tokentypes["ASSIGN"])){
        return left;
    }
    if(precedence[tok.value] > befprec){

        Token oper = tok;
        next();
        shared_ptr<Node> lside = make_shared<BinaryOperationNode>(left, maybeBinary(parseAtom(), precedence[oper.value]), oper.value);
        return maybeBinary(lside, 0);
    }
    return left;
}