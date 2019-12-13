#include <list>
#include <string>
#include <unordered_map>

using std::list;
using std::string;
using std::unordered_map;


class ScopeData {
  string name;
  int realtive_location;
  string type;
  ScopeData(string data_name, int data_location, string data_type);
  ScopeData();
};

class Scope {
  list<list<ScopeData>> scopes;
};


int func(){
    unordered_map<ScopeData, int> map;
    
}
