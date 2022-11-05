#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <stdio.h>
#include <iostream>
class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(int count);
    ~myThread();
    int count;      //自己添加类成员
protected:
    void run();
};

#endif // MYTHREAD_H
