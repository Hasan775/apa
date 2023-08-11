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
    bool CheckToKeyWord(string word);
    vector<Token> lexAnalysis();
    vector<Token> FilterTokens(vector<Token> pTokens);
};