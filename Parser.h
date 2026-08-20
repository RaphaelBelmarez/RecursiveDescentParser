#include <iostream>
#include <fstream>
#include <vector>

#include "Parser.cpp"

#IFNDEF ParserH 
#DEFINE ParserH

using namespace std;

class Token{
  public:
    enum TokenType{
      OPERATOR,
      INTEGER,
      IDENTIFIER,
      END_OF_FILE,
      RESERVED_WORD,
      ASSIGNMENT
};

struct Token{
  TokenType type;
  string value;
  int line;
};

vector<Token> tokens;

};

int currentIndex;
unordered_set<string> declaredVariables;
unordered_set<string> reservedWords;

#endif // ParserH
