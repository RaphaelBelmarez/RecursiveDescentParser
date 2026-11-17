#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#ifndef Parser

using namespace std;
static const set<string> types = {"int", "float", "double"};
class Tokens {
public:
  enum tokType { ID, NUM, RESERVED, OPERATOR, END };

  /*enum TokenType {
    PROGRAM,
    DECL_SEC,
    DECL,
    ID_LIST,
    ID,
    STMT_SEC,
    STMT,
    ASSIGN,
    IFSTMT,
    WHILESTMT,
    INPUT,
    OUTPUT,
    EXPR,
    FACTOR,
    OPERAND,
    NUM,
    COMP,
    TYPE,
    RESERVED,
    OPERATOR
  };
*/
  struct Token {
    tokType type;
    string value;
    int line;
  };
};
class Parsing {
public:
  Parsing() {}
  ~Parsing() {}

  Tokens::Token currentToken;
  void expectedType(const string &type);

  size_t index = 0;
  int lineIndex = 1;

  string line;
  string file;

  void scanFile(string text);
  void program();
  void decl_sec();
  void decl();
  void id_list(bool todecl);
  void id(bool todecl);
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

  bool doesExist(string type);

  Tokens::Token getToken();

protected:
  unordered_set<string> reserved_words = {
      "program", "begin", "end",   "if",   "then", "else",   "input",
      "output",  "int",   "while", "loop", "int",  "double", "float"};

  unordered_set<string> vars;
  unordered_map<string, string> varType;

  /*unordered_map<string, Tokens::TokenType> selectTokens = {
      {"PROGRAM", Tokens::PROGRAM},
      {"DECL", Tokens::DECL},
      {"DECL_SEC", Tokens::DECL_SEC},
      {"ID_LIST", Tokens::ID_LIST},
      {"ID", Tokens::ID},
      {"STMT_SEC", Tokens::STMT_SEC},
      {"STMT", Tokens::STMT},
      {"ASSIGN", Tokens::ASSIGN},
      {"IFSTMT", Tokens::IFSTMT},
      {"WHILESTMT", Tokens::WHILESTMT},
      {"INPUT", Tokens::INPUT},
      {"OUTPUT", Tokens::OUTPUT},
      {"EXPR", Tokens::EXPR},
      {"FACTOR", Tokens::FACTOR},
      {"OPERAND", Tokens::OPERAND},
      {"NUM", Tokens::NUM},
      {"COMP", Tokens::COMP},
      {"TYPE", Tokens::TYPE},
      {"RESERVED", Tokens::RESERVED},
      {"OPERATOR", Tokens::OPERATOR}};
  */
  unordered_set<string> functions;
};
#endif // !Parser
