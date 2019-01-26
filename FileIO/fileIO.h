#include<string>
#include<fstream>
#include"elment.h"

using std::string;

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
    elm cont;

    elm readElm(IO::err &tag);

public:

    file();
    file(string name);

    //Overwrite nod
    bool good();
    bool isFile(){return true;}
    IO::err open(string name);
    IO::err init();

    elm getElment();
};

class fold:public nod{
    public:
    bool isFile(){return false;}
};