#include<filesystem>
#include"fileIO.h"

namespace fs = std::filesystem;
using namespace IO;

fold::fold(){
    state=sta::NoFile;
}

//赋值的dir
fold::fold(fs::path name){
    setPath(name);
    // if(open(name)==err::FailOpen)    state=sta::Error;
    // else if(init()!=err::Success)   state=sta::Error;
    // else state=sta::Ready;
}

IO::err fold::open(){
    fs::directory_iterator lis(dir);
    for(fs::directory_entry pt:lis){
        if(pt.is_directory())   li.push_back(new fold(pt.path()));
        else li.push_back(new file(pt.path()));
    }
    state=sta::UnInit;
}

IO::err fold::init(){
    for(auto pt:li){
        pt->open();
        pt->init();
    }
    state=sta::Ready;
}

vector<nod*>::const_iterator fold::getIter(){
    return li.begin();
}

fold::~fold(){
    for(auto pt:li){
        delete pt;
    }
}