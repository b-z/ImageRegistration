#ifndef REGISTRATIONTHREAD_H
#define REGISTRATIONTHREAD_H

#include <QThread>

class RegistrationThread : public QThread
{
    Q_OBJECT

public:
    RegistrationThread(QObject *parent);
    ~RegistrationThread();

private:
    
};

#endif // REGISTRATIONTHREAD_H
