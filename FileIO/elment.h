#include<string>
#include<vector>
#include<utility>

using std::string;
using std::vector;
using std::pair;

#ifndef ELM
#define ELM

class elm{

protected:

    vector<pair<string,string> > li;
    vector<pair<string,elm> > chi;

public:

    // string getName();
    string toString(int);
    void insert(string key,string val);
    void insert(string key,elm val);
};

#endif