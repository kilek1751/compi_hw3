

#include "ScopeData.h"

ScopeData::ScopeData() {
  name = "";
  realtive_location = 0;
  type = "";
}

ScopeData::ScopeData(string data_name, int rel_loc, string data_type) {
  name = data_name;
  realtive_location = rel_loc;
  type = data_type;
}

ostream &operator<<(ostream &out, const ScopeData &scope_data) {
  out << scope_data.name << " " << scope_data.realtive_location << " "
      << scope_data.type;
  return out;
}

bool ScopeData::operator==(const ScopeData &scope_data) {
  bool name_match = scope_data.getNameCopy() == name;
  bool location_match = scope_data.getRelLocationCopy() == realtive_location;
  bool type_match = scope_data.getTypeCopy() == type;
  return name_match && location_match && type_match;
}

string ScopeData::getNameCopy() const { return name; }

int ScopeData::getRelLocationCopy() const { return realtive_location; }

string ScopeData::getTypeCopy() const { return type; }
