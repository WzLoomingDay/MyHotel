#ifndef DELEGATE_H
#define DELEGATE_H

#include <QWidget>

class Delegate : public QWidget
{
    Q_OBJECT

public:
    Delegate(QWidget *parent = 0);
    ~Delegate();
};

#endif // DELEGATE_H
