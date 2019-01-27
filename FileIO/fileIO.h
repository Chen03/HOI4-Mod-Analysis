#include<string>
#include<fstream>
#include"elment.h"

using std::string;
using namespace elm;

namespace IO
{
    enum err{NoLoadedFile,FailOpen,Success,ErrFormat};
    enum sta{NoFile,UnInit,Error,Ready};
} // IO


class nod{

protected:

    string name;
    IO::sta state;

public:

    //Condition
    bool good();

    string getName(){return name;}
    virtual IO::err open(string name)=0;
    virtual bool isFile()=0;
    virtual IO::err init()=0;
};

class file:public nod{

    std::ifstream filePt;
    bloc cont;

    bloc readElm(string name,IO::err &tag);
    int getNext(char *ou,int n,...);

public:

    file();
    file(string name);

    //Overwrite nod
    bool good();
    bool isFile(){return true;}
    IO::err open(string name);
    IO::err init();

    bloc getElment();
};

class fold:public nod{
    public:
    bool isFile(){return false;}
};