#include "iconloader.h"
#include "appearance.h"
#include "../utility/Logging.hpp"
#include "../utility/utilities.h"

#include <QtDebug>
#include <QDir>
#include <QSettings>

QList<int> IconLoader::_sizes;
QString IconLoader::_customIconPath;
QList<QString> IconLoader::_iconSubPath;
bool IconLoader::_useSysIcons;

void IconLoader::init()
{
  _sizes.clear();
  _sizes << 22 << 32 << 48;
  _customIconPath = GetConfigPath(Path_Icons);
  _iconSubPath.clear();
  qLog(Debug) << _customIconPath;
  _iconSubPath << "/icons" << "";
  qLog(Debug) << _iconSubPath;
  QSettings settings;
  settings.beginGroup(Appearance::kSettingsGroup);
  _useSysIcons = settings.value("b_use_sys_icons", false).toBool();
}

QIcon IconLoader::load(const QString& name, const IconType& icontype)
{
  QIcon ret;
  if (name.isEmpty()) {
    qLog(Warning) << "Icon name is null";
    return ret;
  }

#if QT_VERSION >= 0x040600
  if (_useSysIcons) {
    ret = QIcon::fromTheme(name);
    if (!ret.isNull()) return ret;
  }
#endif

  // Set the icon load location based on IConType
  switch (icontype) {
  case Base:
  case Provider: {
    const QString customIconLocation = _customIconPath
        + _iconSubPath.at(icontype);
    if (QDir(customIconLocation).exists()) {
      // Try to load icons from the custom icon location initially
      const QString locate(customIconLocation + "/%1x%2/%3.png");
	  const QString locateIco(customIconLocation + "/%1x%2/%3.ico");
      for (int size : _sizes) {
        QString filename(locate.arg(size).arg(size).arg(name));
		QString filenameIco(locateIco.arg(size).arg(size).arg(name));
        if (QFile::exists(filename)){
            ret.addFile(filename, QSize(size, size));
        }
		else if (QFile::exists(filenameIco)) {
			ret.addFile(filenameIco, QSize(size, size));
		}
      }

      if (!ret.isNull()) return ret;
    }

    // Otherwise use our fallback theme
    const QString path(":" + _iconSubPath.at(icontype) + "/%1x%2/%3.png");
    for (int size : _sizes) {
      QString filename(path.arg(size).arg(size).arg(name));

      if (QFile::exists(filename)){
          ret.addFile(filename, QSize(size, size));
      }
    }
    break;
  }

  default:
    // Should never be reached
    qLog(Warning) << "Couldn't recognize IconType" << name;
  }

    // Load icon from system theme only if it hasn't been found
  if (ret.isNull()) {
#if QT_VERSION >= 0x040600
    ret = QIcon::fromTheme(name);
    if (!ret.isNull()) return ret;
#endif
    qLog(Warning) << "Couldn't load icon" << name;
  }

  return ret;
}
