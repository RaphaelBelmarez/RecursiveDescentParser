#include "Parser.h"
#include <fstream>
#include <iostream>

using namespace std;

void Scanner::scanFile() {
  ifstream file("TestingFiles/file1.txt");
  string line;
  while (getline(file, line)) {
  }
};
void Parsing::getToken(string line, int index) {}
void Parsing::program() { getToken(); };
void Parsing::assign() {
  cout << "ASSIGN" << endl;
  return;
}
