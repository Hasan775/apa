#pragma once
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include "Token.h"
using namespace std;
class Lexer{
public:
    string code;
    vector<Token> lexAnalysis();
    vector<Token> FilterTokens(vector<Token> pTokens);
};