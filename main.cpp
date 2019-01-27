#include<iostream>
#include<fstream>
#include"FileIO\fileIO.h"
#include"FileIO\elment.h"

using std::ofstream;

int main(){
    ofstream out;
    out.open("test.out");
    file a;
    IO::err tag=IO::err::Success;
    tag=a.open("1.in");
    if(tag!=IO::err::Success)   printf("OPEN FAILED.");
    tag=a.init();
    bloc tmp = a.getElment();
    out<<tmp.toString(0);
    return 0;
}