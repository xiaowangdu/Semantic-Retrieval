#include "utilities.h"

#include <QApplication>
#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QMetaEnum>
#include <QMouseEvent>
#include <QStringList>
#include <QtDebug>
#include <QTemporaryFile>
#include <QtGlobal>
#include <QUrl>
#include <QWidget>
#include <QXmlStreamReader>

QString GetConfigPath(ConfigPath config) {
  switch (config) {
    case Path_Root: {
        return QString("%1/data").arg(QCoreApplication::applicationDirPath());

#ifdef Q_OS_DARWIN
      return mac::GetApplicationSupportPath() + "/" +
             QCoreApplication::organizationName();
#else
      return QString("%1/.config/%2")
          .arg(QDir::homePath(), QCoreApplication::organizationName());
#endif
    } break;

    case Path_CacheRoot: {
      return GetConfigPath(Path_Root) + "/cache";

#if defined(Q_OS_UNIX) && !defined(Q_OS_DARWIN)
      char* xdg = getenv("XDG_CACHE_HOME");
      if (!xdg || !*xdg) {
        return QString("%1/.cache/%2")
            .arg(QDir::homePath(), QCoreApplication::organizationName());
      } else {
        return QString("%1/%2").arg(xdg, QCoreApplication::organizationName());
      }
#else
      return GetConfigPath(Path_Root);
#endif
    } break;

    case Path_Icons:
      return GetConfigPath(Path_Root) + "./";

    case Path_Background:
      return GetConfigPath(Path_Root) + "./";

    case Path_NetworkCache:
      return GetConfigPath(Path_CacheRoot) + "/networkcache";

    case Path_MoodbarCache:
      return GetConfigPath(Path_CacheRoot) + "/moodbarcache";

    case Path_GstreamerRegistry:
      return GetConfigPath(Path_Root) +
             QString("/gst-registry-%1-bin")
                 .arg(QCoreApplication::applicationVersion());

    case Path_DefaultMusicLibrary:
#ifdef Q_OS_DARWIN
      return mac::GetMusicDirectory();
#else
      return QDir::homePath();
#endif

    case Path_LocalSpotifyBlob:
      return GetConfigPath(Path_Root) + "/spotifyblob";

    default:
      qFatal("%s", Q_FUNC_INFO);
      return QString::null;
  }
}
