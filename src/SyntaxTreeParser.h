#include <json/json.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Json;

class SyntaxTreeParser {
  public:
  
    void process(const Value& node) {

      string filename = node["location"]["filename"].asString() + ".cpp";

      ofstream file(filename);

      if (file.is_open()) {
        clog << "Compiling source to ./" + filename;

        file << "#include <iostream>";
        file << "using namespace std;";
        file << "int main() {";
        
        this->traverse(node, file);

        file << "return 0;";
        file << "}";

        file.close();
      } else {
        cerr << "Failed to create or open file at ./" + filename << endl;
      }
    }

  private:
    map<string, void(SyntaxTreeParser::*)(const Value&, ofstream&)> hooks = {
      {"Print", &SyntaxTreeParser::handlePrint}
    };

    void traverse(const Value& node, ofstream& file) {
      
      if (this->hooks.count(node["kind"].asString()) > 0) { 
        (this->*hooks[node["kind"].asString()])(node, file);
      } 


      for (const auto& key : node.getMemberNames()) {
        if (!node[key].isObject()) continue;
        this->traverse(node[key], file);
      }

    }

    void handlePrint(const Value& node, ofstream& file) {
      string printableNode = "";
      if (node["value"]["kind"].asString() == "Str") {
        printableNode = "cout << \"" + node["value"]["value"].asString() + "\";"; 
      }
      
      file << printableNode;
    }
};
