#include<iostream>
#include"FileIO\fileIO.h"
#include"FileIO\elment.h"

int main(){
    file a;
    IO::err tag=IO::err::Success;
    tag=a.open("C://Users//Administrator//Documents//Tencent Files//1456707418//FileRecv//test.txt");
    if(tag!=IO::err::Success)   printf("OPEN FAILED.");
    tag=a.init();
    elm tmp = a.getElment();
    std::cout<<tmp.toString(0);
    return 0;
}