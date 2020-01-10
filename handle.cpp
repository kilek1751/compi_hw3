
#include "handle.h"
#include "Scope.h"
#include "hw3_output.hpp"
#include "source.hpp"

vector<ScopeData> createFuncArgsVec2(TypeContainer* formals);
string getFunctionParametersString2(Scope& table, string id);
void notDefined2(Scope& table, TypeContainer* con);
string getActualType2(Scope& table, TypeContainer* some_data);
vector<string> parseFuncParams2(string type);
bool areTypesEqual(string type1, string type2);
void numCheck2(Scope& table, TypeContainer* con);
TypeContainer* binOpType2(TypeContainer* lhs, TypeContainer* rhs);

Handler::Handler(Scope& parser_table)
    : table(parser_table), last_function_ret_type(""), is_main_defined(false) {}

void Handler::programStart() {
  table.insertScope();
  vector<string> print_func_args;
  vector<string> printi_func_args;
  print_func_args.push_back("STRING");
  printi_func_args.push_back("INT");
  string print_func_type = makeFunctionType("VOID", print_func_args);
  string printi_func_type = makeFunctionType("VOID", printi_func_args);
  table.addFuncData(
      ScopeData("print", 0, print_func_type, print_func_args, true, false));
  table.addFuncData(
      ScopeData("printi", 0, printi_func_type, printi_func_args, true, false));
}

void Handler::defineMain() { this->is_main_defined = true; }

void Handler::mainDefined() {
  if (!is_main_defined) {
    errorMainMissing();
    exit(0);
  }
  ScopeData main_data = table.getDataCopy("main");
  if (main_data.getTypeCopy() != "()->VOID") {
    errorMainMissing();
    exit(0);
  }
}

void Handler::updateLastFunctionRetType(TypeContainer* ret) {
  this->last_function_ret_type = ret->getType();
}

void Handler::functionDeclaration(){};

void Handler::createAndInsertFunction(TypeContainer* ret, TypeContainer* id,
                                      TypeContainer* formals) {
  vector<string> formals_ids = ((FormalListClass*)formals)->getNames();
  // formals_ids can shadow others ??
  vector<string> formals_types = formals->getTypes();
  string func_type = makeFunctionType(ret->getType(), formals_types);
  vector<ScopeData> created_args = createFuncArgsVec2(formals);
  vector<string> WORKONTHIS;
  // ScopeData new_data = ScopeData(id->getName(), 0, func_type);
  ScopeData new_data =
      ScopeData(id->getName(), 0, func_type, formals_types, true, false);
  table.addFuncData(new_data);
  table.insertScope();
  table.insertFuncArgs(created_args);
}

TypeContainer* Handler::enumDeclaration(TypeContainer* id,
                                        TypeContainer* enum_list) {
  vector<string> enum_names = ((FormalListClass*)enum_list)->getNames();
  int scope_level = 0;
  ScopeData new_data = ScopeData(id->getName(), scope_level, "ENUM_CONTAINER",
                                 enum_names, false, true);
  table.addScopeData(new_data);
  return new FormalListClass(id->getName(),
                             ((FormalListClass*)enum_list)->getIds());
}

TypeContainer* Handler::formalList(TypeContainer* formal_decl,
                                   TypeContainer* formal_list) {
  vector<string> vec1 = ((FormalListClass*)formal_decl)->getNames();
  vector<string> vec2 = ((FormalListClass*)formal_list)->getNames();
  string formal_id = vec1[0];
  ((FormalListClass*)formal_decl)
      ->addIds(((FormalListClass*)formal_list)->getIds());
  return formal_decl;
}

TypeContainer* Handler::enumratorList(TypeContainer* enum_list,
                                      TypeContainer* enumrator) {
  ((FormalListClass*)enumrator)
      ->addIds(((FormalListClass*)enum_list)->getIds());
  return enumrator;
}

void Handler::insertVariable() {}

void Handler::insertEnum() {}

TypeContainer* Handler::functionCall(TypeContainer* func_id,
                                     TypeContainer* exp_list) {
  ScopeData func_data = table.getDataCopy(func_id->getName());
  vector<string> func_def_types = func_data.getEnumValues();
  vector<string> explist_params = exp_list->getTypes();
  if (func_def_types.size() != explist_params.size()) {
    errorPrototypeMismatch(yylineno, func_id->getName(), func_def_types);
    exit(0);
  }
  for (int i = 0; i < func_def_types.size(); i++) {
    bool res = areTypesEqual(func_def_types[i], explist_params[i]);
    if (!res) {
      errorPrototypeMismatch(yylineno, func_id->getName(), func_def_types);
      exit(0);
    }
  }
  string call_type = getActualType2(table, func_id);
  if (call_type == "INT") {
    return new Int(0, call_type);
  } else if (call_type == "BOOL") {
    return new Bool(true, call_type);
  } else if (call_type == "BYTE") {
    return new Byte(0, call_type);
  } else {
    string no_str = "";
    return new Enum(no_str, call_type);
  }
}

TypeContainer* Handler::functionCallNoParams(TypeContainer* func_id) {
  ScopeData func_data = table.getDataCopy(func_id->getName());
  vector<string> func_params = func_data.getEnumValues();
  if (func_params.size() != 0) {
    errorPrototypeMismatch(yylineno, func_id->getName(), func_params);
    exit(0);
  }
  string call_type = getActualType2(table, func_id);
  if (call_type == "INT") {
    return new Int(0, call_type);
  } else if (call_type == "BOOL") {
    return new Bool(true, call_type);
  } else if (call_type == "BYTE") {
    return new Byte(0, call_type);
  } else {
    string no_str = "";
    return new Enum(no_str, call_type);
  }
}

TypeContainer* Handler::expBinopH(TypeContainer* lhs, TypeContainer* rhs) {
  numCheck2(table, lhs);
  numCheck2(table, rhs);
  return binOpType2(lhs, rhs);
}

TypeContainer* Handler::expBinopL(TypeContainer* lhs, TypeContainer* rhs) {
  return expBinopH(lhs, rhs);
}

void Handler::returnStatement(TypeContainer* exp) {
  if (exp == NULL) {
    if (last_function_ret_type != "VOID") {
      errorMismatch(yylineno);
      exit(0);
    }
    return;
  }
  if (last_function_ret_type == "VOID") {
    errorMismatch(yylineno);
    exit(0);
  }
  string exp_type = getActualType2(table, exp);
  if (!(last_function_ret_type == "INT" && exp_type == "BYTE")) {
    if (exp_type != last_function_ret_type) {
      errorMismatch(yylineno);
      exit(0);
    }
  }
}

void Handler::expNumB() {}

void Handler::expNot() {}

void Handler::expAnd() {}

void Handler::expOr() {}

TypeContainer* Handler::expRelop(TypeContainer* lhs, TypeContainer* rhs) {
  numCheck2(table, lhs);
  numCheck2(table, rhs);
  return new Bool(true, "BOOL");
}

TypeContainer* Handler::expReleq(TypeContainer* lhs, TypeContainer* rhs) {
  return expRelop(lhs, rhs);
}

void Handler::casting() {}

/*

problems : $1->getName() does return error if called again

*/

void numCheck2(Scope& table, TypeContainer* con) {
  string type = getActualType2(table, con);
  if (type != "INT" && type != "BYTE") {
    errorMismatch(yylineno);
    exit(0);
  }
}

bool areTypesEqual(string type1, string type2) {
  if (type1 == type2) {
    return true;
  }
  if (type1 == "INT" && type2 == "BYTE") {
    return true;
  }
  return false;
}

TypeContainer* binOpType2(TypeContainer* lhs, TypeContainer* rhs) {
  string type_one = lhs->getType();
  string type_two = rhs->getType();
  if (type_one == "INT" || type_two == "INT") {
    return new Int(lhs->getVal() + rhs->getVal(), "INT");
  }
  return new Int(lhs->getVal() + rhs->getVal(), "BYTE");
}

string getRetType2(ScopeData some_func) {
  string type = some_func.getTypeCopy();
  std::size_t location = type.find("->");
  type = type.substr(location + 2);
  return type;
}

vector<string> functionTypeToVector2(string function_type) {
  function_type = function_type.substr(0, function_type.find("->"));
  function_type = function_type.substr(1, function_type.length() - 1);
  std::string s = function_type;
  std::string delimiter = ",";
  vector<string> output_vector;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    output_vector.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  return output_vector;
}

vector<ScopeData> createFuncArgsVec2(TypeContainer* formals) {
  vector<Id> id_vec = ((FormalListClass*)formals)->getIds();
  vector<ScopeData> output_vec;
  int i = -1;
  for (Id id : id_vec) {
    output_vec.push_back(ScopeData(id.getName(), i, id.getType()));
    i--;
  }
  return output_vec;
}

vector<string> parseFuncParams2(string type) {
  vector<string> params;
  string param_string = type.substr(1, type.size() - 2);
  int count = 0;
  for (char c : param_string) {
    if (c == ',') count++;
  }
  int param_num =
      count;  //(int)std::count(param_string.begin(), param_string.end(), ',');
  int pos = 0;
  for (int i = 0; i < param_num; i++) {
    pos = (int)type.find(",");
    params.push_back(param_string.substr(0, pos - 1));
    param_string = param_string.substr(pos);
  }
  params.push_back(param_string);
  return params;
}

string StringFromVec2(vector<string> params) {
  if (params.size() == 0) return "()";
  string temp = "(";
  for (string param : params) {
    temp += param + ',';
  }
  return temp.substr(0, temp.size() - 1) + ')';
}

string getRetType2(string type) {
  int pos = (int)type.find("->");
  if (pos == std::string::npos) {
    return "";
  }
  return type.substr(pos + 2, type.size() - 2);
}

string getFunctionParametersString2(Scope& table, string id) {
  ScopeData func_data = table.getDataCopy(id);
  string type = func_data.getTypeCopy();
  std::size_t location = type.find("->");
  type = type.substr(0, location);
  return type;
}

string getActualType2(Scope& table, TypeContainer* some_data) {
  string type = some_data->getType();
  if (type == "ID") {
    notDefined2(table, some_data);
    type = table.getDataCopy(some_data->getName()).getTypeCopy();
    std::size_t location = type.find("->");
    if (location == std::string::npos) {
      return type;
    }
    type = type.substr(location + 2);
  }
  return type;
}

void notDefined2(Scope& table, TypeContainer* con) {
  if (table.exist(con->getName()) == false ||
      table.getDataCopy(con->getName()).isEnum()) {
    errorUndef(yylineno, con->getName());
    exit(0);
  }
}