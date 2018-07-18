#include <QtGlobal>

//#include <cxxabi.h>
#ifdef Q_OS_UNIX
#include <execinfo.h>
#endif

#include <iostream>

#include <QCoreApplication>
#include <QDateTime>
#include <QStringList>
#include <QtGlobal>
#include <QFile>

#include "Logging.hpp"

namespace logging {

static Level sDefaultLevel = Level_Debug;
static QMap<QString, Level>* sClassLevels = nullptr;
static QIODevice* sNullDevice = nullptr;

const char* kDefaultLogLevels = "Widget:2,";

static const char* kMessageHandlerMagic = "__logging_message__";
static const int kMessageHandlerMagicLength = (int)strlen(kMessageHandlerMagic);
static QtMessageHandler sOriginalMessageHandler = nullptr;

void (*pWriteOuput)(Level, const QMessageLogContext &, const QString &);

void writeToConsole(Level level, const QMessageLogContext &/*context*/, const QString & message)
{
    if (strncmp(kMessageHandlerMagic, message.toStdString().c_str(), kMessageHandlerMagicLength) == 0) {
        fprintf(stderr, "%s\n", message.toStdString().c_str() + kMessageHandlerMagicLength);
    }
    else{
        QString msg = /*checkAndMakePreMsg(level, " unknown ", -1) +*/ message;
        fprintf(stderr, "%s\n", msg.toStdString().c_str());
    }

}

void writeToFile(Level level, const QMessageLogContext &/*context*/, const QString & message)
{
    static QMutex mutex;
    mutex.lock();

    QString localMsg;
    if (strncmp(kMessageHandlerMagic, message.toStdString().c_str(), kMessageHandlerMagicLength) == 0) {
        localMsg = message.mid(kMessageHandlerMagicLength, message.size());
        //fprintf(stderr, "%s\n", message.toStdString().c_str() + kMessageHandlerMagicLength);
    }
    else{
        localMsg = checkAndMakePreMsg(level, " unknown ", -1) + message;
    }

    QFile file("F:/workspace/log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << localMsg << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString & message)
{
    Level level = Level_Debug;
    switch (type) {
    case QtFatalMsg:
    case QtCriticalMsg:
        level = Level_Error;
        break;
    case QtWarningMsg:
        level = Level_Warning;
        break;
    case QtDebugMsg:
    default:
        level = Level_Debug;
        break;
    }

    pWriteOuput(level, context, message);
    flushall();

    if (type == QtFatalMsg) {
        abort();
    }
}

void init()
{
  delete sClassLevels;
  delete sNullDevice;

  sClassLevels = new QMap<QString, Level>();
  sNullDevice = new NullDevice;

  logSwitchTo(LOG_FILE);

  // Catch other messages from Qt
//  if (!sOriginalMessageHandler) {
//    sOriginalMessageHandler = qInstallMessageHandler(MessageHandler);
//  }

  qInstallMessageHandler(MessageHandler);
}

void logSwitchTo(StandardOutput output)
{
    if(output>1) return;
    if(output == CONSOLE){
        pWriteOuput = writeToConsole;
    }
    else if(output == LOG_FILE){
        pWriteOuput = writeToFile;
    }
}


void setLevels(const QString& levels)
{
  if (!sClassLevels) return;

  for (const QString& item : levels.split(',')) {
    const QStringList class_level = item.split(':');

    QString class_name;
    bool ok = false;
    int level = Level_Error;

    if (class_level.count() == 1) {
      level = class_level.last().toInt(&ok);
    } else if (class_level.count() == 2) {
      class_name = class_level.first();
      level = class_level.last().toInt(&ok);
    }

    if (!ok || level < Level_Error || level > Level_Debug) {
      continue;
    }

    if (class_name.isEmpty() || class_name == "*") {
      sDefaultLevel = (Level)level;
    } else {
      sClassLevels->insert(class_name, (Level)level);
    }
  }
}

QString parsePrettyFunction(const char* pretty_function)
{
  // Get the class name out of the function name.
  QString class_name = pretty_function;
  const int paren = class_name.indexOf('(');
  if (paren != -1) {
    const int colons = class_name.lastIndexOf("::", paren);
    if (colons != -1) {
      class_name = class_name.left(colons);
    } else {
      class_name = class_name.left(paren);
    }
  }

  const int space = class_name.lastIndexOf(' ');
  if (space != -1) {
    class_name = class_name.mid(space + 1);
  }

  return class_name;
}



QString checkAndMakePreMsg(Level level, const QString& class_name, int line)
{
    // Map the level to a string
    QString level_name;
    switch (level) {
    case Level_Debug:
        level_name = " DEBUG ";
        break;
    case Level_Info:
        level_name = " INFO  ";
        break;
    case Level_Warning:
        level_name = " WARN  ";
        break;
    case Level_Error:
        level_name = " ERROR ";
        break;
    case Level_Fatal:
        level_name = " FATAL ";
        break;
    }

    // Check the settings to see if we're meant to show or hide this message.
    Level threshold_level = sDefaultLevel;
    if (sClassLevels && sClassLevels->contains(class_name)) {
        threshold_level = sClassLevels->value(class_name);
    }

    if (level > threshold_level) {
        return QString();
    }

    QString function_line = class_name;
    if (line != -1) {
        function_line += ":" + QString::number(line);
    }

    QString ret;
    ret = kMessageHandlerMagic
        + QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
        + level_name
        + function_line;

    return ret;
}

QDebug createLogger(Level level, const QString& class_name, int line)
{
    QString preMsg = checkAndMakePreMsg(level, class_name, line);
    if(preMsg.isEmpty()){
        //nothing to be done
        return QDebug(sNullDevice);
    }

    QtMsgType type = QtDebugMsg;
    if (level == Level_Fatal) {
        type = QtFatalMsg;
    }

    QDebug ret(type);
    ret.nospace() << preMsg.toStdString().c_str();

    return ret.space();
}



}  // namespace logging

//namespace {

//template <typename T>
//QString print_duration(T duration, const std::string& unit) {
//  return QString("%1%2").arg(duration.count()).arg(unit.c_str());
//}

//}  // namespace

//QDebug operator<<(QDebug dbg, std::chrono::seconds secs) {
//  dbg.nospace() << print_duration(secs, "s");
//  return dbg.space();
//}
