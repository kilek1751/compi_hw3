

#ifndef COMPE3_SCOPE_H
#define COMPE3_SCOPE_H

#include <list>
#include <stack>
#include <set>
#include <unordered_map>
#include "ScopeData.h"
#include "hw3_output.hpp"
#include "source.hpp"

using namespace output;

using std::list;
using std::pair;
using std::stack;
using std::unordered_map;

class Scope {
  vector<unordered_map<string, ScopeData>> symbol_table;
  vector<vector<string>> insertion_order;
  stack<int> offsetStack;
  vector<vector<pair<string,string>>> enum_ids;
  vector<vector<string>> func_args_vec;
  vector<string> global_enums;
  vector<string> identifiers;

 public:
  bool exist(string id);
  void insertScope();
  ScopeData getDataCopy(string id);
  void removeScope();
  void addScopeData(ScopeData scope_data);
  void addFuncData(ScopeData scope_data);
  void printLastScopeData();
  void printData();
  int getNextOffset();
  void printTable();
  void insertFuncArgs(vector<ScopeData> func_args);
  string getParentEnumId(string enum_id);
  void insertGlobalEnum(string glob_enum);
  bool findGlobalEnum(string glob_enum);
//  void insertIdentifiers(string ids);
//  bool IdOnly(string id);
//  bool isEnumContainer(string id);
  // void discoveringYYSTYPE(int yy);
};

#endif  // COMPE3_SCOPE_H
