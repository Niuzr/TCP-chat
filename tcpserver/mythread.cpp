#include "mythread.h"

myThread::myThread(int count) : QThread()   //构造函数
{
  this->count=count;
}
void myThread::run(){

    while(true){
       count++;
       std::cout<<"the number is:"<<count<<std::endl;
       QThread::msleep(1000);
    }
}

myThread::~myThread()
{

}
