#include "Parser.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  ifstream myfile(argv[1]);
  string file = {istreambuf_iterator<char>(myfile),
                 istreambuf_iterator<char>()};
  Parsing parse;
  parse.scanFile(file);
  return -1;
};
