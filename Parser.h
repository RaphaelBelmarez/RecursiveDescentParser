#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#ifndef Parser

using namespace std;

class Tokens {
public:
  enum TokenType { OPERATOR };

  struct Token {
    TokenType type;
    string value;
    int line;
  };
};
class Parsing {
public:
  Tokens::Token currentToken;
  int index;
  int line;

  void program();
  void decl_sec();
  void decl();
  void id_list();
  void id();
  void stmt_sec();
  void stmt();
  void assign();
  void ifstmt();
  void whilestmt();
  void input();
  void output();
  void expr();
  void factor();
  void operand();
  void num();
  void comp();
  void type();

  void getToken(string line, int index);

protected:
  unordered_set<string> reserved_words = {"program", "begin", "end",   "if",
                                          "then",    "else",  "input", "output",
                                          "int",     "while", "loop"};
  unordered_map<string, int> vars;
};
class Scanner : public Parsing {
public:
  void scanFile();
  void scanLine(string line);
  int index;
  Tokens::Token *currTok = &currentToken;
};
#endif // !Parser
