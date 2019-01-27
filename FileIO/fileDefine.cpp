#include<string>
#include<iostream>
#include<fstream>
#include<limits>
#include<filesystem>
#include "fileIO.h"

using namespace IO;
using namespace std;
using namespace elm;

/*
void file::init(){
    if(state==IO::sta::Un)
}
*/

//FILE
file::file(){
    state=sta::NoFile;
}

//赋值的dir
file::file(string name){
    dir=std::filesystem::path(name);
    state=IO::sta::UnOpen;

    // if(open(name)==err::FailOpen)    state=sta::Error;
    // else if(init()!=err::Success)   state=sta::Error;
    // else state=sta::Ready;
}

err file::open(){
    //TODO: substring the file name
    filePt.open(dir);
    if(!filePt.good())    return err::FailOpen;
    state=sta::UnInit;
    return err::Success;
}

err file::init(){
    if(state==sta::NoFile)  return err::NoLoadedFile;
    //TODO: read file and create 'elm'
    err tag=err::Success;
    cont=readElm("",tag);
    //TODO: More Visiable Warnings
    if(tag==err::ErrFormat) printf("ERROR FORMAT!\n");
    return tag;
}

//TODO: Rewrite input module
const int N=210;
bloc file::readElm(string name,err &tag){
    printf("STEP INTO\n");
    bloc now(name);
    char key[N],va1[N],top;
    bloc va2;
    while(filePt.good()){
        
        //Skip
        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        while(filePt.peek()=='#'){
            filePt.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            while(filePt.peek()<=32&&filePt.good())    filePt.get();
        }
        if(filePt.eof())    return now;
        
        //get key
        getNext(key,6,' ','=','<','>','\n','\t');
        cerr<<"key:"<<key<<endl;//debug
        if(key[0]=='}')    return now;

        //find the '='
        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        if(!filePt.good()){
            tag=err::ErrFormat;
            return now;
        }
        top=filePt.get();

        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        if(!filePt.good()){
            tag=err::ErrFormat;
            return now;
        }
        if(filePt.peek()=='{'){
            filePt.get();
            va2=readElm(key,tag);
            now.insert(va2);
        }else{
            if(filePt.peek()=='"'){
                filePt.get();
                va1[0]='"';
                va1[1+getNext(va1+1,1,'"')]='"';
                // cerr<<"DEBUG va1"<<va1<<endl;
            }else getNext(va1,4,'\n',' ','\t','}');
            cout<<"va1:"<<va1<<endl;
            now.insert(key,va1,top);
        }
    }
    return now;
    
ERRFO:
    tag=err::ErrFormat;
    return now;
}

int file::getNext(char *ou,int n,...){
    fill(ou,ou+200,'\0');
    int pt=0;
    int *ar=&n+1;
    int i;
    while(filePt.good()){
        for(i=0;i<n;++i)    if(filePt.peek()==ar[i])    return pt;
        ou[pt++]=filePt.get();
    }
    return pt;
}

/*
elm file::readElm(err &tag){
    printf("STEP INTO\n");
    elm now;
    string key,va1;
    elm va2;
    while(filePt.good()){
        
        //Skip
        while(filePt.peek()<=32&&filePt.good())    filePt.get();
        while(filePt.peek()=='#'){
            filePt.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            while(filePt.peek()<=32&&filePt.good())    filePt.get();
        }
        
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
            if(filePt.peek()=='"'){
                filePt.get();
                char tmp[200];tmp[0]='"';
                filePt.getline(&tmp[1],198,'"');
                va1.clear();
                va1.append(tmp);
                va1.append(1,'\"');
            }else filePt>>va1;
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
*/

bloc file::getElment(){
    return cont;
}