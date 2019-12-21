

#include "Scope.h"
bool Scope::exist(string id) {
  for (auto const& current_scope : symbol_table) {
    if(current_scope.find(id) != current_scope.end()){
      return true;
    }
  }
  return false;
}

void Scope::insertScope() {
  symbol_table.push_back(unordered_map<string,ScopeData>());
  // scopes.emplace_back(list<ScopeData>());
  // current_scope_level++;
}

void Scope::removeScope() {
  symbol_table.pop_back();
  // scopes.pop_back();
  // current_scope_level--;
}

void Scope::addScopeData(ScopeData scope_data) {
  (symbol_table.back())[scope_data.getName()] = scope_data;
  // if (symbol_map.find(scope_data.getNameCopy()) != symbol_map.end()) {
  //   cout << "Error already inside symbol table" << endl;
  //   return;
  // }
  // scopes.back().emplace_back(ScopeData(scope_data));
  // symbol_map[scope_data.getNameCopy()] =
  //     make_pair(scope_data, current_scope_level);
}

void Scope::printData() {
  for (auto const& current_scope : symbol_table) {
    for (auto const& data : current_scope) {
      printID(data.second.getNameCopy(), data.second.getRelLocationCopy(),
              data.second.getTypeCopy());
    }
  }
}

void Scope::printLastScopeData() {
  unordered_map<string,ScopeData> last_scope = symbol_map.back();
  for (auto const& data : current_scope) {
    printID(data.second.getNameCopy(), data.second.getRelLocationCopy(),
            data.second.getTypeCopy());
  }
}

void Scope::getNextOffset(){
  int count = 0;
  for (auto const& current_scope : symbol_table ) {
    count += current_scope.size();
  }
  return count+1;
}

// ostream &operator<<(ostream &out, const Scope &scope) {
//   int i = 0;
//   for (auto current_scope : scope.scopes) {
//     out << "Scope number: " << i << endl;
//     for (auto data : current_scope) {
//       out << data << endl;
//     }
//     i++;
//   }
//   return out;
// }

void discoveringYYSTYPE(int yy) { cout << "YYstype is : " << yy << endl; }
