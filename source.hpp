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
  int type;
  TypeContainer(int some_type) : type(some_type){};
  void printData() { std::cout << type << endl; }
  int getType() { return type; };
  vector<int> virtual getTypes(){};
  void virtual printContent(){};
  int virtual getVal(){};
  string virtual getName(){};
  void virtual addType(int some_type){};
  void virtual addTypes(vector<int> to_add_types){};
};

class Int : public TypeContainer {
  int val;

 public:
  Int(char* yytext, int id_type) : val(atoi(yytext)), TypeContainer(id_type){};
  Int(int in_val, int id_type) : val(in_val), TypeContainer(id_type){};
  int getVal() { return val; };
};

class Byte : public TypeContainer {
  int byt;

 public:
  Byte(char* yytext, int id_type) : byt(atoi(yytext)), TypeContainer(id_type){};
  Byte(int val, int id_type) : byt(val), TypeContainer(id_type){};
};

class Id : public TypeContainer {
  string name;

 public:
  Id(char* yytext, int id_type) : name(yytext), TypeContainer(id_type){};
  Id(string yytext, int id_type) : name(yytext), TypeContainer(id_type){};
  string getName() { return name; };
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
  Bool(bool in_val, int id_type) : val(in_val), TypeContainer(id_type){};
};

class String : public TypeContainer {
  string my_str;

 public:
  String(char* yytext, int id_type) : my_str(yytext), TypeContainer(id_type) {}
  void printContent() { cout << my_str << endl; }
};

class Enum : public TypeContainer {
  string id;

 public:
  vector<string> enum_types;
  Enum(char* yytext, int id_type) : id(yytext), TypeContainer(id_type){};
  Enum(string given_id, int id_type) : id(given_id), TypeContainer(id_type){};
  void addTypes(vector<string> to_add) { enum_types = to_add; }
};

class ExpList : public TypeContainer {
  vector<int> types;

 public:
  ExpList(int type) : TypeContainer(type) { types.push_back(type); }
  void addType(int type) { types.push_back(type); }
  vector<int> getTypes() { return types; }
  void addTypes(vector<int> to_add_types) {
    for (int type : to_add_types) {
      types.push_back(type);
    }
  }
  void printContent() {
    for (int i : types) {
      cout << "Exp type is : " << i << " ";
    }
  }
};

#define YYSTYPE TypeContainer*

#endif /* SOURCE_HPP */