#include "Parser.h"

map<string, TokenType> tokentypes;
map<string, int> precedence;
map<string, int> GetPrecedence(){
    map<string, int> prec = {};
    prec["="] = 1;
    prec[">"] = 3;
    prec["<"] = 3;
    prec[">="] = 3;
    prec["<="] = 3;
    prec["=="] = 3;
    prec["+"] = 9;
    prec["-"] = 9; 
    prec["*"] = 10;
    prec["/"] = 10;
    return prec;
}
Parser::Parser(vector<Token> tokens){
    this->tokens = tokens;
    this->tok = tokens[0];
    tokentypes = GetTypes();
    precedence = GetPrecedence();
}
void Parser::UnexpectedToken(){
    Error::throwMessage("Unexpected token type: " + tok.type.name + " on pos " +  to_string(pos)+ ";value is equal to" + tok.value);
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
        require(tokentypes["PUNC"], ";");
    }
    return prog;
}
vector<shared_ptr<Node>> Parser::delimited(string start, string stop, string separator, bool islastseparatorrequired){
    vector<shared_ptr<Node>> exprs = {};
    bool isfirst = true;
    require(tokentypes["PUNC"], start);
    while (!match(tokentypes["PUNC"], stop))
    {
        exprs.push_back(parsePart());
        if (match(tokentypes["PUNC"], stop)){
            break;
        }
        require(tokentypes["PUNC"], separator);
    }
    next();
    return exprs;
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
    if (match(tokentypes["STRING"])){
        return parseString();
    }
    if (match(tokentypes["ID"])){
        return parseKeyword();
    }
    if (match(tokentypes["VAR"])){
        if (peek().type.name == tokentypes["PUNC"].name &&  peek().value == "("){
            return parseCall();   
        }
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
shared_ptr<Node> Parser::parseString(){
    auto str = make_shared<StringNode>(tok.value.substr(1, tok.value.size() - 2));
    next();
    return str;
}
shared_ptr<Node> Parser::parseBool(){
    shared_ptr<BoolNode> bl;
    if (tok.value == "true"){
        bl = make_shared<BoolNode>(true);
    }
    else{
        bl = make_shared<BoolNode>(false);
    }
    next();
    return bl;
}
shared_ptr<Node> Parser::parseVariable(){
    auto var = make_shared<VariableNode>(tok.value);
    next();
    return var;
}
shared_ptr<Node> Parser::parseCall(){
    auto name = tok.value;
    next();
    auto call = make_shared<CallNode>(name, delimited("(", ")", ",", false));
    return call;
}
shared_ptr<Node> Parser::parseIf(){
    require(tokentypes["ID"], "if");
    require(tokentypes["PUNC"], "(");
    auto cond = parsePart();
    require(tokentypes["PUNC"], ")");
    auto body = delimited("{", "}", ";", true);
    shared_ptr<IfNode> ifn;
    if (match(tokentypes["ID"], "else")){
        next();
        vector<shared_ptr<Node>> els = {};
        if (match(tokentypes["ID"], "if")){
            els.push_back(parseIf());
        }
        else{
            els = delimited("{", "}", ";", true);
        }
        ifn  = make_shared<IfNode>(cond, body, els);
    }
    else{
        ifn  = make_shared<IfNode>(cond, body);
    }
    return ifn;
}
shared_ptr<Node> Parser::parseKeyword(){
    if (tok.value == "true" || tok.value =="false"){
        return parseBool();
    }
    if (tok.value == "if"){
        return parseIf();
    }
    return nullptr;
}
shared_ptr<Node> Parser::maybeBinary(shared_ptr<Node> left, int befprec){
    if(!match(tokentypes["OP"])){
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