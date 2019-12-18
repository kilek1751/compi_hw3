

#include "Scope.h"

void Scope::insertScope() {
  scopes.emplace_back(list<ScopeData>());
  current_scope_level++;
}

void Scope::removeScope() {
  scopes.pop_back();
  current_scope_level--;
}

void Scope::addScopeData(ScopeData scope_data) {
  if (symbol_map.find(scope_data.getNameCopy()) != symbol_map.end()) {
    cout << "Error already inside symbol table" << endl;
    return;
  }
  scopes.back().emplace_back(ScopeData(scope_data));
  symbol_map[scope_data.getNameCopy()] =
      make_pair(scope_data, current_scope_level);
}

void Scope::printData() {
  for (auto current_scope : scopes) {
    for (ScopeData data : current_scope) {
      printID(data.getNameCopy(), data.getRelLocationCopy(),
              data.getTypeCopy());
    }
  }
}

void Scope::printLastScopeData() {
  list<ScopeData> last_scope = scopes.back();
  for (ScopeData data : last_scope) {
    printID(data.getNameCopy(), data.getRelLocationCopy(), data.getTypeCopy());
  }
}

ostream &operator<<(ostream &out, const Scope &scope) {
  int i = 0;
  for (auto current_scope : scope.scopes) {
    out << "Scope number: " << i << endl;
    for (auto data : current_scope) {
      out << data << endl;
    }
    i++;
  }
  return out;
}

void discoveringYYSTYPE(int yy) { cout << "YYstype is : " << yy << endl; }
