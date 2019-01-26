#include<string>
#include<iostream>
#include<fstream>
#include<limits>
#include "fileIO.h"

using namespace IO;
using namespace std;

/*
void file::init(){
    if(state==IO::sta::Un)
}
*/

//FILE
file::file(){
    state=sta::NoFile;
}

file::file(string name){
    if(open(name)==err::FailOpen)    state=sta::Error;
    else if(init()!=err::Success)   state=sta::Error;
    else state=sta::Ready;
}

err file::open(string name){

    //TODO: substring the file name
    this->name=name;

    filePt.open(name);
    if(!filePt.good())    return err::FailOpen;
    state=sta::UnInit;
    return err::Success;
}

err file::init(){
    if(state==sta::NoFile)  return err::NoLoadedFile;
    //TODO: read file and create 'elm'
    err tag=err::Success;
    cont=readElm(tag);
    //TODO: More Visiable Warnings
    if(tag==err::ErrFormat) printf("ERROR FORMAT!\n");
    return tag;
}

elm file::readElm(err &tag){
    printf("STEP INTO\n");
    elm now;
    string key,va1,tmp;
    elm va2;
    while(filePt.good()){
        
        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        if(filePt.peek()=='#')  filePt.getline();
        filePt>>key;
        cout<<"key:"<<key<<endl;
        if(!key.compare("}"))    return now;
        //find the '='
        filePt.ignore(std::numeric_limits<std::streamsize>::max(),'=');
        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        if(!filePt.good()){
            tag=err::ErrFormat;
            return now;
        }
        if(filePt.peek()=='{'){
            filePt.get();
            va2=readElm(tag);
            now.insert(key,va2);
        }else{
            filePt>>va1;
            cout<<"va1:"<<va1<<endl;
            now.insert(key,va1);
            if(!va1.compare(va1.size()-1,1,"}")){
                va1=va1.substr(0,va1.size()-1);
                return now;
            }
        }
    }
    return now;
}

elm file::getElment(){
    return cont;
}