

#include "Scope.h"
#include <algorithm>
#include <stdexcept>
bool Scope::exist(string id) {
  for (auto const& current_scope : symbol_table) {
    if (current_scope.find(id) != current_scope.end()) {
      return true;
    }
  }
  for (vector<string> curr_vec : enum_ids) {
    for (string enum_id : curr_vec) {
      if (id == enum_id) {
        return true;
      }
    }
  }
  return false;
}

void Scope::insertScope() {
  if (offsetStack.size() == 0) {
    offsetStack.push(0);
  } else {
    offsetStack.push(offsetStack.top());
  }
  symbol_table.push_back(unordered_map<string, ScopeData>());
  insertion_order.push_back(vector<string>());
  enum_ids.push_back(vector<string>());
  func_args_vec.push_back(vector<ScopeData>());
}

void Scope::removeScope() {
  offsetStack.pop();
  symbol_table.pop_back();
  insertion_order.pop_back();
  enum_ids.pop_back();
  func_args_vec.pop_back();
}

void Scope::addScopeData(ScopeData scope_data) {
  (symbol_table.back())[scope_data.getNameCopy()] = scope_data;
  insertion_order.back().push_back(scope_data.getNameCopy());
  vector<string> enum_values = scope_data.getEnumValues();
  if (enum_values.size() == 0) offsetStack.top() += 1;
  for (string enum_id : enum_values) {
    enum_ids.back().push_back(enum_id);
  }
}

void Scope::addFuncData(ScopeData scope_data) {
  (symbol_table.back())[scope_data.getNameCopy()] = scope_data;
  insertion_order.back().push_back(scope_data.getNameCopy());
}

void Scope::printData() {
  int i = (int)insertion_order.size() - 1;
  if (i < 0) return;
  for (vector<vector<string>>::reverse_iterator l_scope =
           insertion_order.rbegin();
       l_scope != insertion_order.rend(); l_scope++) {
    vector<string>& curr = *l_scope;
    vector<ScopeData> enums_to_print;
    for (auto it = curr.begin(); it != curr.end(); it++) {
      string symbol = *it;
      ScopeData& to_print = symbol_table[i][symbol];
      if (to_print.getEnumValues().size() != 0) {
        enums_to_print.push_back(to_print);
      } else {
        printID(to_print.getNameCopy(), to_print.getRelLocationCopy(),
                to_print.getTypeCopy());
      }
    }
    /* print ScopeDatas of enums */
    if (enums_to_print.size() > 0) {
      for (auto enum_to_print : enums_to_print) {
        vector<string> temp = enum_to_print.getEnumValues();
        std::reverse(temp.begin(), temp.end());
        printEnumType(enum_to_print.getNameCopy(), temp);
      }
    }
    i--;
  }
  //    vector<ScopeData> enums;
  //    for (auto const& current_scope : symbol_table) {
  //        for (auto const& data : current_scope) {
  //            if(!data.second.getEnumValues().size()){
  //                printID(data.second.getNameCopy(),
  //                        data.second.getRelLocationCopy(),
  //                        data.second.getTypeCopy());
  //            }else {
  //                vector<string> temp = data.second.getEnumValues();
  //                printEnumType(data.second.getNameCopy(), temp);
  //            }
  //            for(auto enum_to_print: enums ){
  //                vector<string> temp = enum_to_print.getEnumValues();
  //                std::reverse(temp.begin(), temp.end());
  //                printEnumType(enum_to_print.getNameCopy(), temp);
  //            }
  //        }
  //    }
}

void Scope::printLastScopeData() {
  int i = (int)symbol_table.size() - 1;
  for (ScopeData arg : func_args_vec.back()) {
    printID(arg.getNameCopy(), arg.getRelLocationCopy(), arg.getTypeCopy());
  }
  if (i < 0) return;
  vector<string>& last = insertion_order.back();
  vector<ScopeData> enums_to_print;
  for (auto it = last.begin(); it != last.end(); it++) {
    string symbol = *it;
    ScopeData& to_print = symbol_table[i][symbol];
    if (to_print.getEnumValues().size() != 0) {
      enums_to_print.push_back(to_print);
    } else {
      printID(to_print.getNameCopy(), to_print.getRelLocationCopy(),
              to_print.getTypeCopy());
    }
  }
  /* print ScopeDatas of enums */
  if (enums_to_print.size() > 0) {
    for (auto enum_to_print : enums_to_print) {
      vector<string> temp = enum_to_print.getEnumValues();
      std::reverse(temp.begin(), temp.end());
      printEnumType(enum_to_print.getNameCopy(), temp);
    }
  }
  //    vector<ScopeData> enums;
  //    unordered_map<string, ScopeData> last_scope = symbol_table.back();
  //    for (auto const& data : last_scope) {
  //        if(!data.second.getEnumValues().size()){
  //            printID(data.second.getNameCopy(),
  //                    data.second.getRelLocationCopy(),
  //                    data.second.getTypeCopy());
  //        } else {
  //            enums.push_back(data.second);
  //        }
  //    }
  //    for(auto enum_to_print: enums ){
  //        vector<string> temp = enum_to_print.getEnumValues();
  //        std::reverse(temp.begin(), temp.end());
  //        printEnumType(enum_to_print.getNameCopy(), temp);
  //    }
}

void Scope::printTable() {
  for (auto scope : symbol_table) {
    for (auto symbol : scope) {
      std::cout << "name is - " << symbol.first << " is "
                << symbol.second.getNameCopy();
      std::cout << " and the type is - " << symbol.second.getTypeCopy()
                << std::endl;
    }
  }
}

int Scope::getNextOffset() { return offsetStack.top(); }

ScopeData Scope::getDataCopy(string id) {
  for (unordered_map<string, ScopeData> curr_scope : symbol_table) {
    if (curr_scope.find(id) != curr_scope.end()) {
      return (curr_scope.find(id))->second;
    }
  }
  for (vector<string> curr_vec : enum_ids) {
    for (string curr_id : curr_vec) {
      if (curr_id == id) {
        return ScopeData(id, 0, "ENUM");
      }
    }
  }
  throw std::exception();
}

void Scope::insertFuncArgs(vector<ScopeData> func_args) {
  for (ScopeData data : func_args) {
    func_args_vec.back().push_back(data);
  }
}

void discoveringYYSTYPE(int yy) { cout << "YYstype is : " << yy << endl; }
