#ifndef ROOMTHREAD_H
#define ROOMTHREAD_H
#include <QThread>

class RoomThread : public QThread
{
public:
    RoomThread(QObject *parent);
protected:
    void run();
};


#endif // ROOMTHREAD_H
