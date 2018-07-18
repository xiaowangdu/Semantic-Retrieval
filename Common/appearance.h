#ifndef CORE_APPEARANCE_H_
#define CORE_APPEARANCE_H_

#include <QColor>
#include <QPalette>

class Appearance : public QObject {
 public:
  explicit Appearance(QObject* parent = nullptr);
  // Load the user preferred theme, which could the default system theme or a
  // custom set of colors that user has chosen
  void LoadUserTheme();
  void ResetToSystemDefaultTheme();
  void ChangeForegroundColor(const QColor& color);
  void ChangeBackgroundColor(const QColor& color);

  static const char* kSettingsGroup;
  static const char* kUseCustomColorSet;
  static const char* kForegroundColor;
  static const char* kBackgroundColor;
  static const QPalette kDefaultPalette;

 private:
  QColor foreground_color_;
  QColor background_color_;
};

#endif  // CORE_APPEARANCE_H_
