#include "Lexer.h"
#include "Error.h"
vector<string> keywords = {"true",
"false",
"if",
"else",
"while",
"for",
"func",
"return",
"continue",
"break"};
bool Lexer::CheckToKeyWord(string word){
    for (auto keyword : keywords){
        if (keyword == word){
            return true;
        }
    }
    return false;
}
vector<Token> Lexer::lexAnalysis(){
    vector<TokenType> tokentypes = GetTypesVector();
    vector<Token> tokens = {};
    int last = code.size() + 1;
    int line = 1, pos = 0;
    while (code.size() != 0){
        if (last == code.size()){
            Error::throwMessage("Sintax don't match language rules on line " + to_string(line) + " pos " + to_string(pos + 1));
            return {};
        }
        last = code.size();
        for (int i = 0; i < tokentypes.size(); i++){
            TokenType tokentype = tokentypes[i];
            cmatch result;
            regex regular("^" + tokentype.regexp);
            regex_search(code.c_str(), result, regular);
            if (result.size() != 0){
                if (tokentype.name == "ID" && !CheckToKeyWord(result[0])){
                    continue;
                }
                if (result[0] == "\n"){
                    line += 1;
                    pos = 0;
                }
                else{
                    pos += result[0].length();
                }
                Token ntoken = Token(result[0], tokentype);
                code = code.substr(result[0].length(), code.size() - result[0].length());
                tokens.push_back(ntoken);
                break;
            }
        }
    }
    return tokens;
}
vector<Token> Lexer::FilterTokens(vector<Token> pTokens){
    vector<Token> ntokens = {};
    for (auto token : pTokens){
        if (token.type.name != "SPACE"){
            ntokens.push_back(token);
        }
    }
    return ntokens;
}