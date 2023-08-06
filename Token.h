#pragma once
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;
class TokenType{
public:
    string name;
    string regexp;
    TokenType();
    TokenType(string name, string regexp);
};
class Token{
public:
    string value;
    TokenType type = TokenType(" ", " ");
    Token();
    Token(string value, TokenType type);
};
vector<TokenType> GetTypesVector();
map<string, TokenType> GetTypes();