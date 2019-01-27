#include<string>
#include<vector>
#include<utility>

using std::string;
using std::vector;
using std::pair;

#ifndef ELM
#define ELM

//语句
namespace elm
{

    class stat{

    protected:
        string key;

    public:
        string getKey(){return key;}
        virtual bool isExpr(){return false;};
    };

    //表达式: a = b \ a > b
    class expr:public stat{

    protected:
        string val;
        char oper;
        
    public:
        expr(string,string);
        expr(string,string,char);

        char getOper(){return oper;}
        bool isExpr(){return true;}
        string getVal(){return val;}
    };

    //代码块: a = { b = c }
    class bloc:public stat{

    protected:
        vector<stat*> li;
        
    public:
        bloc(){}
        bloc(string);
        ~bloc();

        bool isExpr(){return false;}
        string toString(int);
        void insert(string key,string val);
        void insert(string key,string val,char oper);
        void insert(bloc val);

    };

} // ele
// class elm{

// protected:

//     vector<stat> li;

// public:

//     // string getName();
//     string toString(int);
//     void insert(string key,string val);
//     void insert(string key,elm val);
// };

#endif