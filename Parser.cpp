#include "Parser.h"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

void Exit(int l, string err) {
  cout << "Error on line " << l << ", " << err << endl;
  exit(1);
}

void Parsing::scanFile(string text) {
  file = text;
  currentToken = getToken();
  program();
  exit(0);
};

Tokens::Token Parsing::getToken() {
  Tokens::Token tok;
  string type;
  size_t i = index;
  while (i < file.size() && isspace(static_cast<unsigned char>(file[i]))) {
    if (file[i] == '\n') {
      lineIndex++;
    }
    i++;
  }
  index = i;
  if (i >= file.size()) {
    tok.type = Tokens::END;
    tok.value = "end";
    tok.line = lineIndex;
    index = i;
    return tok;
  }

  char c = file[i];
  size_t y;

  // ID
  if (isalpha(static_cast<unsigned char>(c)) || c == '_') {
    y = i;
    while (y < file.size() &&
           (isalnum(static_cast<unsigned char>(file[y])) || file[y] == '_')) {
      y++;
    }
    index = y;
    type = file.substr(i, y - i);
    if (reserved_words.count(type)) {
      tok.type = Tokens::RESERVED;
      tok.value = type;
      tok.line = lineIndex;
      return tok;
    }
    tok.type = Tokens::ID;
    tok.value = type;
    tok.line = lineIndex;
    return tok;
  }

  // NUM
  if (isdigit(static_cast<unsigned char>(c))) {
    int numDig = 0;
    y = i;
    while (y < file.size() && isdigit(static_cast<unsigned char>(file[y]))) {
      y++;
    }
    type = file.substr(i, y - i);
    for (char d : type) {
      if (isdigit(static_cast<unsigned char>(d))) {
        numDig++;
        if (numDig > 10) {
          Exit(lineIndex, "more than 10 digits");
        }
      }
    }
    tok.type = Tokens::NUM;
    tok.value = type;
    tok.line = lineIndex;
    index = y;
    return tok;
  }
  if (i + 1 < file.size()) {
    type = file.substr(i, 2);
    if (type == ":=" || type == "<>") {
      index += 2;
      tok.type = Tokens::OPERATOR;
      tok.value = type;
      tok.line = lineIndex;
      return tok;
    }
  }

  if (string(":;,<>=+-*/()").find(c) != string::npos) {
    index++;
    tok.type = Tokens::OPERATOR;
    tok.value = file[i];
    tok.line = lineIndex;
    return tok;
  }
  Exit(lineIndex, string("Illegal symbol ") + c);
  exit(1);
}

bool Parsing::doesExist(string type) {
  return (currentToken.type == Tokens::OPERATOR ||
          currentToken.type == Tokens::RESERVED) &&
         currentToken.value == type;
}

void Parsing::expectedType(const string &val) {
  if (!doesExist(val)) {
    Exit(currentToken.line,
         "Error, Expected " + val + " got " + currentToken.value);
  }
  currentToken = getToken();
}

void Parsing::id(bool todecl) {
  if (currentToken.type != Tokens::ID) {
    Exit(currentToken.line, "Expected identifier, got " + currentToken.value);
  }
  if (todecl) {
    if (vars.count(currentToken.value)) {
      Exit(currentToken.line, "redeclaration of " + currentToken.value);
    }
    vars.insert(currentToken.value);
  } else if (!vars.count(currentToken.value)) {
    Exit(currentToken.line, "undeclared var " + currentToken.value);
  }
  currentToken = getToken();
}

void Parsing::program() {
  cout << "PROGRAM" << endl;
  expectedType("program");
  if (currentToken.value != "begin") {
    decl_sec();
  }
  expectedType("begin");
  stmt_sec();
  expectedType("end");
  expectedType(";");
  if (currentToken.type != Tokens::END) {
    Exit(currentToken.line,
         "expected end of file, got extra " + currentToken.value);
  }
}

void Parsing::assign() {
  cout << "ASSIGN" << endl;
  id(false);
  expectedType(":=");
  expr();
  expectedType(";");
}

void Parsing::comp() {
  cout << "COMP" << endl;
  expectedType("(");
  operand();
  if (currentToken.value != "=" && currentToken.value != "<>" &&
      currentToken.value != ">" && currentToken.value != "<") {
    Exit(currentToken.line,
         "Expected comparison operator, got " + currentToken.value);
  }
  currentToken = getToken();
  operand();
  expectedType(")");
}

void Parsing::decl_sec() {
  cout << "DECL_SEC" << endl;
  decl();
  if (currentToken.type == Tokens::ID) {
    decl_sec();
  }
}

void Parsing::decl() {
  cout << "DECL" << endl;
  id_list(true);
  expectedType(":");
  if (!types.count(currentToken.value)) {
    Exit(currentToken.line,
         "Expected a type(int, float, double), got " + currentToken.value);
  }
  currentToken = getToken();
  expectedType(";");
}
void Parsing::expr() {
  cout << "EXPR" << endl;
  factor();
  if (doesExist("+") || doesExist("-")) {
    currentToken = getToken();
    expr();
  }
}

void Parsing::id_list(bool todecl) {
  cout << "ID_LIST" << endl;
  id(todecl);
  if (doesExist(",")) {
    currentToken = getToken();
    id_list(todecl);
  }
}

void Parsing::stmt_sec() {
  cout << "STMT_SEC" << endl;
  stmt();
  if (currentToken.type == Tokens::ID || doesExist("if") ||
      doesExist("while") || doesExist("input") || doesExist("output")) {
    stmt_sec();
  }
}

void Parsing::stmt() {
  cout << "STMT" << endl;
  if (currentToken.type == Tokens::ID) {
    assign();
  } else if (doesExist("if")) {
    ifstmt();
  } else if (doesExist("while")) {
    whilestmt();
  } else if (doesExist("input")) {
    input();
  } else if (doesExist("output")) {
    output();
  } else {
    Exit(currentToken.line, "expected a statement, got " + currentToken.value);
  }
}

void Parsing::ifstmt() {
  cout << "IF_STMT" << endl;
  expectedType("if");
  comp();
  expectedType("then");
  stmt_sec();
  if (currentToken.value == "else") {
    currentToken = getToken();
    stmt_sec();
  }
  expectedType("end");
  expectedType("if");
  expectedType(";");
}

void Parsing::whilestmt() {
  cout << "WHILE_STMT" << endl;
  expectedType("while");
  comp();
  expectedType("loop");
  stmt_sec();
  expectedType("end");
  expectedType("loop");
  expectedType(";");
}

void Parsing::output() {
  cout << "OUTPUT" << endl;
  expectedType("output");
  if (currentToken.type == Tokens::NUM) {
    currentToken = getToken();
  } else {
    id_list(false);
  }
  expectedType(";");
}

void Parsing::input() {
  cout << "INPUT" << endl;
  expectedType("input");
  id_list(false);
  expectedType(";");
}

void Parsing::factor() {
  cout << "FACTOR" << endl;
  operand();
  if (doesExist("*") || doesExist("/")) {
    currentToken = getToken();
    factor();
  }
}

void Parsing::operand() {
  cout << "OPERAND" << endl;
  if (currentToken.type == Tokens::NUM) {
    currentToken = getToken();
  } else if (currentToken.type == Tokens::ID) {
    id(false);
  } else if (doesExist("(")) {
    currentToken = getToken();
    expr();
    expectedType(")");
  } else {
    Exit(currentToken.line,
         "expected (num, id, or '('), got " + currentToken.value);
  }
}
