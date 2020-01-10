#include "Scope.h"
#include "source.hpp"

extern int yylineno;

class Handler {
  bool is_main_defined;
  string last_function_ret_type;
  Scope& table;

 public:
  Handler(Scope& parser_table);

  void programStart();

  void defineMain();
  void mainDefined();

  void updateLastFunctionRetType(TypeContainer* ret);

  void functionDeclaration();

  void createAndInsertFunction(TypeContainer* ret, TypeContainer* id,
                               TypeContainer* formals);

  TypeContainer* enumDeclaration(TypeContainer* id, TypeContainer* enum_list);

  TypeContainer* formalList(TypeContainer* formal_decl,
                            TypeContainer* formal_list);

  TypeContainer* enumratorList(TypeContainer* enum_list,
                               TypeContainer* enumrator);

  void insertVariable();

  void insertEnum();

  TypeContainer* functionCall(TypeContainer* func_id, TypeContainer* exp_list);

  TypeContainer* functionCallNoParams(TypeContainer* func_id);

  TypeContainer* expBinopH(TypeContainer* lhs, TypeContainer* rhs);

  TypeContainer* expBinopL(TypeContainer* lhs, TypeContainer* rhs);

  void returnStatement(TypeContainer* exp);

  void expNumB();

  void expNot();

  void expAnd();

  void expOr();

  TypeContainer* expRelop(TypeContainer* lhs, TypeContainer* rhs);

  TypeContainer* expReleq(TypeContainer* lhs, TypeContainer* rhs);

  void casting();
};