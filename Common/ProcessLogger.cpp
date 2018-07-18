#include "ProcessLogger.h"
#include <QTextBrowser>
#include <QProcess>
#include <QTextCodec>

ProcessLogger::ProcessLogger()
    :m_process(NULL)
{

}

void ProcessLogger::setProcess(QProcess *process)
{
    if(process == NULL){
        return;
    }

    m_process = process;
    connect(m_process, SIGNAL(readyRead()), this, SLOT(prepareFlush()));
}

void ProcessLogger::clearLoggers()
{
    for(int i = 0; i < m_loggers.size(); ++i){
        if(m_loggers[i])
            delete m_loggers[i];
    }

    m_loggers.clear();
}

void ProcessLogger::initConsoleLogger()
{
    ConsoleLogging *consoleLogging = new ConsoleLogging(m_process);
    m_loggers.append(consoleLogging);
}

void ProcessLogger::initFileLogger(const QString &filename)
{
    FileLogging * fileLogging = new FileLogging(m_process, filename);
    m_loggers.append(fileLogging);
}

void ProcessLogger::initControlLogger(QWidget *control)
{
    QTextBrowser *textBrowser = qobject_cast<QTextBrowser *>(control);
    TextBrowserLogging *textBrowserLogging = new TextBrowserLogging(m_process, textBrowser);
    m_loggers.append(textBrowserLogging);
    //connect(this, SIGNAL(flushOutput(const QString&)), m_textBrowserLogging, SLOT(writeOutput(const QString&)));
}

void ProcessLogger::prepareFlush()
{
    QByteArray data = m_process->readAll();
    QString unicodeInfo = QTextCodec::codecForLocale()->toUnicode(data);

    for(int i = 0; i < m_loggers.size(); ++i){
        m_loggers[i]->writeOutput(unicodeInfo);
    }
}

ProcessLogger::~ProcessLogger()
{
    clearLoggers();
}
