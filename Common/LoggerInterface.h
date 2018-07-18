#ifndef LOGGERINTERFACE_H
#define LOGGERINTERFACE_H

#include <QObject>

//enum ProcessLog{
//    PRO_CONSOLE, PRO_FILE, PRO_CONTROL
//};

class QProcess;

class LoggerInterface : public QObject
{
    Q_OBJECT
public:
    LoggerInterface();

    virtual void setProcess(QProcess *) = 0;
    virtual void initConsoleLogger(){}
    virtual void initFileLogger(const QString &){}
    virtual void initControlLogger(QWidget *){}
    virtual void clearLoggers(){}

};

#endif // LOGGERINTERFACE_H
