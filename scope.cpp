#include "scope.hpp"

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
