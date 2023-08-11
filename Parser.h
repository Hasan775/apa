#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Node.h"
#include "Error.h"
class Parser{
public:
    vector<Token> tokens;
    Token tok;
    int pos = 0;
    Parser(vector<Token> tokens);
    void UnexpectedToken();
    bool match(TokenType type);
    bool match(TokenType type, string value);
    void require(TokenType type);
    void require(TokenType type, string value);
    Token next();
    bool isEOF();
    Token peek();
    vector<shared_ptr<Node>> parseTopLevel();
    vector<shared_ptr<Node>> delimited(string start, string stop, string separator);
    shared_ptr<Node> parsePart();
    shared_ptr<Node> parseNumber();
    shared_ptr<Node> parseString();
    shared_ptr<Node> parseBool();
    shared_ptr<Node> parseVariable();
    shared_ptr<Node> parseCall();
    shared_ptr<Node> parseKeyword();
    shared_ptr<Node> parseAtom();
    shared_ptr<Node> maybeBinary(shared_ptr<Node> left, int befprec);
};