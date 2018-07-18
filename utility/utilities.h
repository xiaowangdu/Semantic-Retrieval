#ifndef CORE_UTILITIES_H_
#define CORE_UTILITIES_H_

#include <memory>

#include <QColor>
#include <QFile>
#include <QLocale>
#include <QCryptographicHash>
#include <QSize>
#include <QString>
#include <QUrl>


enum ConfigPath {
  Path_Root,
  Path_Icons,
  Path_Background,
  Path_NetworkCache,
  Path_GstreamerRegistry,
  Path_DefaultMusicLibrary,
  Path_LocalSpotifyBlob,
  Path_MoodbarCache,
  Path_CacheRoot,
};
QString GetConfigPath(ConfigPath config);


#endif  // CORE_UTILITIES_H_
