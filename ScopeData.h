

#ifndef COMPE3_SCOPEDATA_H
#define COMPE3_SCOPEDATA_H


#include <string>
#include <iostream>
using std::ostream;
using std::endl;
using std::cout;
using std::string;

class ScopeData {
    string name;
    int realtive_location;
    string type;
public:
    ScopeData(string data_name, int data_location, string data_type);
    ScopeData();
    string getNameCopy()const ;
    int relLocationCopy()const ;
    string getTypeCopy()const ;
    bool operator==(const ScopeData& scope_data);
    friend ostream& operator<<(ostream& out,const ScopeData& scope_data);
};


#endif //COMPE3_SCOPEDATA_H
