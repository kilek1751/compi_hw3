

#ifndef COMPE3_SCOPEDATA_H
#define COMPE3_SCOPEDATA_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

class ScopeData {
  string name;
  int realtive_location;
  string type;
  vector<string> enums;

 public:
  ScopeData(string data_name, int data_location, string data_type,
            vector<string>& enums);
  ScopeData(string data_name, int rel_loc, string data_type);
  ScopeData();
  string getNameCopy() const;
  int getRelLocationCopy() const;
  string getTypeCopy() const;
  vector<string> getEnumValues() const;
  bool operator==(const ScopeData& scope_data);
  friend ostream& operator<<(ostream& out, const ScopeData& scope_data);
};

#endif  // COMPE3_SCOPEDATA_H
