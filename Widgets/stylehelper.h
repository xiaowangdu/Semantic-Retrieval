#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QColor>
#include <QStyle>

#include "../utility/qt_blurimage.h"

QT_BEGIN_NAMESPACE
class QPalette;
class QPainter;
class QRect;
QT_END_NAMESPACE

// Helper class holding all custom color values

class StyleHelper {
 public:
  static const unsigned int DEFAULT_BASE_COLOR = 0x666666;

  // Height of the project explorer navigation bar
  static qreal sidebarFontSize();

  // This is our color table, all colors derive from baseColor
  static QColor requestedBaseColor() { return m_requestedBaseColor; }
  static QColor baseColor(bool lightColored = false);
  static QColor panelTextColor(bool lightColored = false);
  static QColor highlightColor(bool lightColored = false);
  static QColor shadowColor(bool lightColored = false);
  static QColor borderColor(bool lightColored = false);

  static QColor sidebarHighlight() { return QColor(255, 255, 255, 40); }
  static QColor sidebarShadow() { return QColor(0, 0, 0, 40); }

  // Sets the base color and makes sure all top level widgets are updated
  static void setBaseColor(const QColor& color);

  // Gradients used for panels
  static void verticalGradient(QPainter* painter, const QRect& spanRect,
                               const QRect& clipRect,
                               bool lightColored = false);
  static bool usePixmapCache() { return true; }

  static void drawIconWithShadow(const QIcon& icon, const QRect& rect,
                                 QPainter* p, QIcon::Mode iconMode,
                                 int radius = 3,
                                 const QColor& color = QColor(0, 0, 0, 130),
                                 const QPoint& offset = QPoint(1, -2));

 private:
  static QColor m_baseColor;
  static QColor m_requestedBaseColor;
};

//using Utils::StyleHelper;
#endif  // STYLEHELPER_H
