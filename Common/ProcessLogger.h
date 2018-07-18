#ifndef PROCESSLOGGER_H
#define PROCESSLOGGER_H

#include "LoggerInterface.h"
#include "ProcessLogging.h"


class QProcess;
class QTextBrowser;

class ProcessLogger : public LoggerInterface
{
    Q_OBJECT
public:
    ProcessLogger();

    ~ProcessLogger();

    void initConsoleLogger();
    void initFileLogger(const QString &filename);
    void initControlLogger(QWidget *control);
    void setProcess(QProcess *);
    void clearLoggers();

private slots:
    void prepareFlush();

private:
    QProcess *m_process;
    QVector<ProcessLogging *> m_loggers;

//    ProcessLogging *m_consoleLogging;
//    ProcessLogging *m_textBrowserLogging;
//    ProcessLogging *m_fileLogging;
};

#endif // PROCESSLOGGER_H
