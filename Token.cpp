#include "Token.h"
using namespace std;

TokenType::TokenType(){
    this->name = "NULL";
    this->regexp = "";
}
TokenType::TokenType(string name, string regexp){
    this->name = name;
    this->regexp = regexp;
}
vector<TokenType> tokenTypes = {
    TokenType("PUNC", "[\\(\\)\\[\\];,]"),
    TokenType("OP", "[\\+\\-\\*\\/]"),
    TokenType("ASSIGN", "="),
    TokenType("NUMBER", "[0-9]+"),
    TokenType("VAR", "[a-zA-Z0-9]+"),
    TokenType("SPACE", "\\s"),
    TokenType("STRING", "\"[^\\n^\"]+\""),
};
vector<TokenType> GetTypesVector(){
    return tokenTypes;
}
map<string, TokenType> GetTypes(){
    map<string, TokenType> typesmap = {};
    for (auto type : tokenTypes){
        typesmap[type.name] = type;
    }
    return typesmap;
}
Token::Token(){
    this->value = "";
    this->type = TokenType();
}
Token::Token(string value, TokenType type){
    this->value = value;
    this->type = type;
}