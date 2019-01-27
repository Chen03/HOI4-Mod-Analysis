#include<vector>
#include<utility>
#include<sstream>
#include "elment.h"

using std::vector;
using std::pair;
using namespace elm;

void bloc::insert(string key,string val){
    li.push_back(new expr(key,val));
}

void bloc::insert(string key,string val,char oper){
    li.push_back(new expr(key,val,oper));
}

void bloc::insert(bloc val){
    li.push_back(new bloc(val));
}

expr::expr(string ke,string va){
    key=ke,val=va;
}

expr::expr(string ke,string va,char op):expr(ke,va){
    oper=op;
}

bloc::bloc(string ke){
    key=ke;
}
/*
string elm::getName(){
    return name;
}
*/

string bloc::toString(int tb){
    std::ostringstream str;
    for(vector<stat*>::iterator pt=li.begin();pt!=li.end();++pt){
        for(int j=0;j<tb;++j)   str<<'\t';
        if((*pt)->isExpr())
        str<<(*pt)->getKey()<<" "<<((expr*)(*pt))->getOper()<<" "<<((expr*)(*pt))->getVal()<<'\n';
        else{
            str<<((bloc*)(*pt))->getKey<<" = {\n";
            str<<((bloc*)(*pt))->toString(tb+1);
            for(int j=0;j<tb;++j)   str<<'\t';
            str<<"}\n";
        }
    }
    // for(pair<string,elm> i:chi){
    //     for(int j=0;j<tb;++j)   str<<'\t';
    //     str<<i.first<<" = {\n";
    //     str<<i.second.toString(tb+1);
    //     for(int j=0;j<tb;++j)   str<<'\t';
    //     str<<"}\n";
    // }
    return str.str();
}