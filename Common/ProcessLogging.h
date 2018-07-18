#ifndef PROCESSLOGGING_H
#define PROCESSLOGGING_H
#include <QDebug>
#include "LoggerInterface.h"

class QProcess;
class QTextBrowser;

class ProcessLogging :public QObject
{
    Q_OBJECT
public:
    QProcess *m_process;

    ProcessLogging(QProcess *process);
    virtual void writeOutput(const QString&){}

};

class ConsoleLogging :public ProcessLogging
{
    Q_OBJECT
public:
    ConsoleLogging(QProcess *process);
    void writeOutput(const QString& data);

};

class FileLogging :public ProcessLogging
{
    Q_OBJECT
public:
    FileLogging(QProcess *, const QString &filename);
    void writeOutput(const QString& data);

private:
    QString m_fileName;
};

class TextBrowserLogging :public ProcessLogging
{
    Q_OBJECT
public:
    TextBrowserLogging(QProcess *, QTextBrowser *textBrowser);
    void writeOutput(const QString& data);

private:
    QTextBrowser *m_textBrowser;
};

#endif // LOGGER_H
