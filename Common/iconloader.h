#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QIcon>

class IconLoader {
 public:
  enum IconType {
    Base = 0,
    Provider = 1,
    Other = 2
  };

  static void init();
  static QIcon load(const QString& name, const IconType& icontype);

 private:
  IconLoader() {}

  static QList<int> _sizes;
  static QString _customIconPath;
  static QList<QString> _iconSubPath;
  static bool _useSysIcons;
};

#endif  // ICONLOADER_H
