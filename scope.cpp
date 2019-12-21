

#include "Scope.h"
#include <stdexcept>
bool Scope::exist(string id) {
  for (auto const& current_scope : symbol_table) {
    if (current_scope.find(id) != current_scope.end()) {
      return true;
    }
  }
  return false;
}

void Scope::insertScope() {
    if(offsetStack.size() == 0){
        offsetStack.push(0);
    }else{
        offsetStack.push(offsetStack.top());
    }
    symbol_table.push_back(unordered_map<string, ScopeData>());
}

void Scope::removeScope() {
    offsetStack.pop();
    symbol_table.pop_back();
}

void Scope::addScopeData(ScopeData scope_data) {
    (symbol_table.back())[scope_data.getNameCopy()] = scope_data;
    offsetStack.top() += 1;
}

void Scope::addFuncData(ScopeData scope_data) {
    (symbol_table.back())[scope_data.getNameCopy()] = scope_data;
}

void Scope::printData() {
  for (auto const& current_scope : symbol_table) {
    for (auto const& data : current_scope) {
      if(!data.second.getEnumValues().size()){
          printID(data.second.getNameCopy(),
                  data.second.getRelLocationCopy(),
                  data.second.getTypeCopy());
      }else {
          vector<string> temp = data.second.getEnumValues();
          printEnumType(data.second.getNameCopy(), temp);
      }
    }
  }
}

void Scope::printLastScopeData() {
  unordered_map<string, ScopeData> last_scope = symbol_table.back();
  for (auto const& data : last_scope) {
      if(!data.second.getEnumValues().size()){
          printID(data.second.getNameCopy(),
                  data.second.getRelLocationCopy(),
                  data.second.getTypeCopy());
      }else {
          vector<string> temp = data.second.getEnumValues();
          printEnumType(data.second.getNameCopy(), temp);
      }
  }
}

int Scope::getNextOffset() {
    return offsetStack.top();
}

ScopeData Scope::getDataCopy(string id) {
  for (unordered_map<string, ScopeData> curr_scope : symbol_table) {
    if (curr_scope.find(id) != curr_scope.end()) {
      return (curr_scope.find(id))->second;
    }
  }
    throw std::exception();
}

void discoveringYYSTYPE(int yy) { cout << "YYstype is : " << yy << endl; }
