#include<vector>
#include<utility>
#include<sstream>
#include "elment.h"

using std::vector;
using std::pair;

void elm::insert(string key,string val){
    li.push_back(std::make_pair(key,val));
}

void elm::insert(string key,elm val){
    chi.push_back(std::make_pair(key,val));
}

/*
string elm::getName(){
    return name;
}
*/

string elm::toString(int tb){
    std::ostringstream str;
    for(pair<string,string> i:li){
        for(int j=0;j<tb;++j)   str<<'\t';
        str<<i.first<<" = "<<i.second<<'\n';
    }
    for(pair<string,elm> i:chi){
        for(int j=0;j<tb;++j)   str<<'\t';
        str<<i.first<<" = {\n";
        str<<i.second.toString(tb+1);
        for(int j=0;j<tb;++j)   str<<'\t';
        str<<"}\n";
    }
    return str.str();
}