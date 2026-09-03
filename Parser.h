#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

#ifndef ParserH
#define ParserH

using namespace std;

class Tokens {
public:
  Tokens();

  enum Type {
    OPERATOR,
    INTEGER,
    IDENTIFIER,
    END_OF_FILE,
    RESERVED_WORD,
    ASSIGNMENT
  };

  struct Token {
    Type type;
    string value;
    int line;
  };

  vector<Token> tokens = {};
};

class Parser {
public:
  int currentIndex;
  unordered_set<string> declaredVariables;
  unordered_set<string> reservedWords;

  void expectToken(string expectedValue);
  void checkDeclaredVariable(string variableName, int line);
  Tokens::Token currentToken();
  void scanFile(const string &filename);
  void parseFile();
  void parseProgram();
  void parseVariableList();
  void parseDeclaration();
  void parseDeclarations();
  void parseInput();
  void parseOutput();
  void parseAssignment();
  void parseComparison();
  void parseStatement();
  void parseIfStatement();
  void parseWhileStatement();
  void parseStatements();
  void parseFactor();
  void parseTerm();
  void parseExpression();
};
class Parsing {
public:
};

#endif // ParserH
