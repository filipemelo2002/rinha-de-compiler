#include <iostream>
#include <fstream>
#include <json/json.h>
#include "SyntaxTreeParser.h"

using namespace Json;
using namespace std;

int main (int argc, char **argv) {
  
  string filePath = "";

  for (int i =0; i < argc; i++) {
    if (strcmp(argv[i], "--file") == 0 && (i+1) < argc) {
      filePath = argv[i+1];
    }
  }

  if (filePath.length() == 0) {
    cerr << "Missing file path.";
    return -1;
  }

  clog<< "Reading file at " + filePath << endl;

  ifstream file(filePath);
  Value tree;
  file >> tree;

  SyntaxTreeParser parser = SyntaxTreeParser();
  
  parser.process(tree);

  return 0;
}