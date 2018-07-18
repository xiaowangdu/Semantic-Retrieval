#ifndef LOGGING_H
#define LOGGING_H

#include <chrono>
#include <string>

#include <QDebug>

#ifdef QT_NO_DEBUG_STREAM
#define qLog(level) \
  while (false) QNoDebug()
#else
#define qLog(level)                                                        \
  logging::createLogger(logging::Level_##level,                            \
                        logging::parsePrettyFunction(__FUNCTION__), \
                        __LINE__)
#endif

namespace logging {

enum Level {
  Level_Fatal = -1,
  Level_Error = 0,
  Level_Warning,
  Level_Info,
  Level_Debug,
};

enum StandardOutput {
  CONSOLE = 0,
  LOG_FILE,
  CONTROL,
};

class NullDevice : public QIODevice {
 protected:
  qint64 readData(char*, qint64) { return -1; }
  qint64 writeData(const char*, qint64 len) { return len; }
};


void init();
void logSwitchTo(StandardOutput output);
void setLevels(const QString& levels);

QString parsePrettyFunction(const char* pretty_function);
QString checkAndMakePreMsg(Level level, const QString& class_name, int line);
QDebug createLogger(Level level, const QString& class_name, int line);

extern const char* kDefaultLogLevels;
}

QDebug operator<<(QDebug debug, std::chrono::seconds secs);

#endif  // LOGGING_H
