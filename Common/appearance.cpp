#include "appearance.h"

#include <QApplication>
#include <QSettings>

const char* Appearance::kSettingsGroup = "Appearance";
const char* Appearance::kUseCustomColorSet = "use-custom-set";
const char* Appearance::kForegroundColor = "foreground-color";
const char* Appearance::kBackgroundColor = "background-color";

const QPalette Appearance::kDefaultPalette = QPalette();

Appearance::Appearance(QObject* parent) : QObject(parent) {
  QSettings s;
  s.beginGroup(kSettingsGroup);
  QPalette p = QApplication::palette();
  background_color_ =
      s.value(kBackgroundColor, p.color(QPalette::WindowText)).value<QColor>();
  foreground_color_ =
      s.value(kForegroundColor, p.color(QPalette::Window)).value<QColor>();
}

void Appearance::LoadUserTheme() {
  QSettings s;
  s.beginGroup(kSettingsGroup);
  bool use_a_custom_color_set = s.value(kUseCustomColorSet).toBool();
  if (!use_a_custom_color_set) return;

  ChangeForegroundColor(foreground_color_);
  ChangeBackgroundColor(background_color_);
}

void Appearance::ResetToSystemDefaultTheme() {
  QApplication::setPalette(kDefaultPalette);
}

void Appearance::ChangeForegroundColor(const QColor& color) {
  // Get the application palette
  QPalette p = QApplication::palette();

  // Modify the palette
  p.setColor(QPalette::WindowText, color);
  p.setColor(QPalette::Text, color);

  // Make the modified palette the new application's palette
  QApplication::setPalette(p);
  foreground_color_ = color;
}

void Appearance::ChangeBackgroundColor(const QColor& color) {
  // Get the application palette
  QPalette p = QApplication::palette();

  // Modify the palette
  p.setColor(QPalette::Window, color);
  p.setColor(QPalette::Base, color);

  // Make the modified palette the new application's palette
  QApplication::setPalette(p);
  background_color_ = color;
}
