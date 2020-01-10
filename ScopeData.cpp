

#include "ScopeData.h"

ScopeData::ScopeData() {
  name = "";
  realtive_location = 0;
  type = "";
  is_function = false;
  is_enum = false;

}

ScopeData::ScopeData(string data_name, int rel_loc, string data_type,
                     vector<string> &enums, bool is_function,
                     bool is_enum)
    : name(data_name), realtive_location(rel_loc), type(data_type), enums(enums),is_function(is_function),is_enum(is_enum)  {
}

ScopeData::ScopeData(string data_name, int rel_loc, string data_type)
    : name(data_name), realtive_location(rel_loc), type(data_type),is_function(false),is_enum(false)  {
}

ostream &operator<<(ostream &out, const ScopeData &scope_data) {
  out << scope_data.name << " " << scope_data.realtive_location << " "
      << scope_data.type << " " << scope_data.is_enum << " " << scope_data.is_function;
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
    
vector<string> ScopeData::getEnumValues() const { return enums; }

bool ScopeData::isFunction() { return is_function; };
bool ScopeData::isEnum() { return is_enum; };