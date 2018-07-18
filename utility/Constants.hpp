#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <limits>
#include <QString>
#include <QColor>

const QString __APPNAME__ = "Semantic Retrieval";
const QString SETTING_FILENAME = "filename";
const QString SETTING_RECENT_FILES = "recentFiles";
const QString SETTING_WIN_SIZE = "window/size";
const QString SETTING_WIN_POSE = "window/position";
const QString SETTING_WIN_GEOMETRY = "window/geometry";
const QString SETTING_LINE_COLOR = "line/color";
const QString SETTING_FILL_COLOR = "fill/color";
const QString SETTING_ADVANCE_MODE = "advanced";
const QString SETTING_WIN_STATE = "window/state";
const QString SETTING_SAVE_DIR = "savedir";
const QString SETTING_LAST_OPEN_DIR = "lastOpenDir";
const QString SETTING_AUTO_SAVE = "autosave";
const QString SETTING_SINGLE_CLASS = "singleclass";

const QColor DEFAULT_LINE_COLOR = QColor(0, 255, 0, 128);
const QColor DEFAULT_FILL_COLOR = QColor(255, 0, 0, 128);
const QColor DEFAULT_SELECT_LINE_COLOR = QColor(255, 255, 255);
const QColor DEFAULT_SELECT_FILL_COLOR = QColor(0, 128, 255, 155);
const QColor DEFAULT_VERTEX_FILL_COLOR = QColor(0, 255, 0, 255);
const QColor DEFAULT_HVERTEX_FILL_COLOR = QColor(255, 0, 0);

const QColor DEFAULT_HIGHLIGHT_SELECTED = QColor(47, 227, 117, 80);

const Qt::CursorShape CURSOR_DEFAULT = Qt::ArrowCursor;
const Qt::CursorShape CURSOR_POINT = Qt::PointingHandCursor;
const Qt::CursorShape CURSOR_DRAW = Qt::CrossCursor;
const Qt::CursorShape CURSOR_MOVE = Qt::ClosedHandCursor;
const Qt::CursorShape CURSOR_GRAB = Qt::OpenHandCursor;

const qint64 INT64MAX = std::numeric_limits<long long>::max();
const qint64 INT64MIN = std::numeric_limits<long long>::min();
const int INT32MAX = std::numeric_limits<int>::max();
const int INT32MIN = std::numeric_limits<int>::min();
const float FLOATMAX = std::numeric_limits<float>::max();
const float FLOATMIN = std::numeric_limits<float>::min();

const QString XML_EXT = ".xml";
const QString TXT_EXT = ".txt";
const QString PASCAL_VOC_FORMAT = "PascalVoc";
const QString YOLO_FORMAT = "Yolo";
const QString ENCODE_METHOD = "utf-8";

const unsigned int LINE = 2;
const unsigned int BOX = 4;

/******************************************Config Name*****************************************/
const QString MENUS_FILE_CONFIG = "menus_file_config";
const QString MENUS_VIEW_CONFIG = "menus_view_config";
const QString MENUS_HELP_CONFIG = "menus_help_config";
const QString FILEMENUACTIONS_CONFIG = "fileMenuActions_config";
const QString EDITMENU_CONFIG = "editMenu_config";
const QString BEGINNERCONTEXT_CONFIG = "beginnerContext_config";
const QString ADVANCEDCONTEXT_CONFIG = "advancedContext_config";
const QString ONLOADACTIVE_CONFIG = "onLoadActive_config";
const QString ONSHAPESPRESENT_CONFIG = "onShapesPresent_config";
const QString BEGINNER_CONFIG = "beginner_config";
const QString ZOOMACTIONS_CONFIG = "zoomActions_config";
const QString ADVANCED_CONFIG = "advanced_config";


#endif