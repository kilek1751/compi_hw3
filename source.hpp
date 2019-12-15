#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

class TypeContainer {
 public:
  vector<int> types;
  TypeContainer(int some_type) { types.push_back(some_type); };
  TypeContainer(const TypeContainer& to_copy) { this->types = to_copy.types; }
  void AddType(int some_type) { types.push_back(some_type); }
  void printData() {
    for (int type : this->types) {
      std::cout << type << endl;
    }
  }
};

class Int : public TypeContainer {
  int val;

 public:
  Int(char* yytext, int id_type) : val(atoi(yytext)), TypeContainer(id_type){};
};

class Id : public TypeContainer {
  string name;

 public:
  Id(char* yytext, int id_type) : name(yytext), TypeContainer(id_type){};
};

class Bool : public TypeContainer {
  bool val;

 public:
  Bool(char* yytext, int id_type) : TypeContainer(id_type) {
    string current_str(yytext);
    if (current_str == "true") {
      val = true;
    } else if (current_str == "false") {
      val = false;
    }
    val = false;
  }
};

class String : public TypeContainer {
  string my_str;

 public:
  String(char* yytext, int id_type) : my_str(yytext), TypeContainer(id_type) {}
};

class Enum : public TypeContainer {
  string id;

 public:
  vector<string> enum_types;
  Enum(char* yytext, int id_type) : id(yytext), TypeContainer(id_type){};
  void addTypes(vector<string> to_add) { enum_types = to_add; }
};

#define YYSTYPE TypeContainer*

#endif /* SOURCE_HPP */