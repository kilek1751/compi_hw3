

#ifndef COMPE3_SCOPE_H
#define COMPE3_SCOPE_H

#include <list>
#include <unordered_map>
#include "ScopeData.h"
#include "hw3_output.hpp"
#include "source.hpp"

using namespace output;

using std::list;
using std::make_pair;
using std::pair;
using std::unordered_map;

class Scope {
  vector<unordered_map<string, ScopeData>> symbol_table;
  // list<list<ScopeData>> scopes;
  // unordered_map<string, pair<ScopeData, int>> Symbol_map;
  // int current_scope_level = 0;

 public:
  bool exist(string id);
  void insertScope();
  void removeScope();
  void addScopeData(ScopeData scope_data);
  void printLastScopeData();
  void printData();
  int Scope::getNextOffset();
  friend ostream& operator<<(ostream& out, const Scope& scope);
  // void discoveringYYSTYPE(int yy);
};

#endif  // COMPE3_SCOPE_H
