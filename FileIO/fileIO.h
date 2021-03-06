#include<string>
#include<fstream>
#include<vector>
#include<filesystem>
#include"elment.h"

using std::vector;
using std::string;
using namespace elm;

namespace IO
{
    enum err{NoLoadedFile,FailOpen,Success,ErrFormat};
    enum sta{NoFile,UnOpen,UnInit,Error,Ready};
} // IO


class nod{

protected:

    std::filesystem::path dir;
    IO::sta state;

public:

    //Condition
    bool good();

    string getName();
    virtual bool isFile()=0;

    void setPath(std::filesystem::path);
    virtual IO::err open()=0;
    virtual IO::err init()=0;
};

class file:public nod{

    std::ifstream filePt;
    bloc cont;

    bloc readElm(string name,IO::err &tag);
    int getNext(char *ou,int n,...);

public:

    file();
    file(std::filesystem::path);

    //Overwrite nod
    bool isFile(){return true;}

    IO::err open();
    IO::err init();

    bloc getElment();
};

class fold:public nod{

    vector<nod*> li;

    public:

    fold();
    fold(std::filesystem::path);
    ~fold();

    bool isFile(){return false;}
    IO::err open();
    IO::err init();

    vector<nod*>::const_iterator getIter();
};