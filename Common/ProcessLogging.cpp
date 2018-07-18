#include "ProcessLogging.h"
#include "../utility/Logging.hpp"
#include <QProcess>
#include <QTextCodec>
#include <QTextBrowser>
#include <QFile>

ProcessLogging::ProcessLogging(QProcess *process)
    :m_process(process)
{
}


ConsoleLogging::ConsoleLogging(QProcess *process)
    :ProcessLogging(process)
{
}

void ConsoleLogging::writeOutput(const QString& data)
{
    //QString unicodeInfo = QTextCodec::codecForLocale()->toUnicode(data);
    qLog(Info) << data;
}


FileLogging::FileLogging(QProcess *process, const QString& filename)
    :ProcessLogging(process), m_fileName(filename)
{
}

void FileLogging::writeOutput(const QString& data)
{
    //QString unicodeInfo = QTextCodec::codecForLocale()->toUnicode(data);

    static QMutex mutex;
    mutex.lock();

    m_fileName = m_fileName.isEmpty()? "F:/workspace/proc_log.txt" : m_fileName;
    QFile file(m_fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << data << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

TextBrowserLogging::TextBrowserLogging(QProcess *process, QTextBrowser *textBrowser)
    :ProcessLogging(process), m_textBrowser(textBrowser)
{
}

void TextBrowserLogging::writeOutput(const QString& data)
{
    m_textBrowser->append(data);;
}
