#pragma once
#include <QObject>
#include <QCheckBox>
#include <QScrollArea>
#include <QDockWidget>
#include <QWidgetAction>
#include <QToolButton>
#include <QMainWindow>
#include <QLabel>
#include "../Widgets/ToolBar.hpp"
#include "ColorDialog.hpp"
#include "LabelDialog.hpp"
#include "ZoomWidget.hpp"
#include "Canvas.hpp"

struct ConfigArrayInfo {
	const QString* pointerTo;
	int size;
};

class MainWindow;

class UiManager  {
	

public:
	QWidget *m_win;

	LabelDialog *m_labelDialog;
	ZoomWidget *m_zoomWidget;
	ColorDialog *m_colorDialog;
	Canvas *m_canvas;

	QVBoxLayout *m_listLayout;
	QCheckBox *m_useDefaultLabelCheckbox;
	QCheckBox *m_diffcButton;
	QLineEdit *m_defaultLabelTextLine;
	QHBoxLayout *m_useDefaultLabelQHBoxLayout;
	QWidget *m_useDefaultLabelContainer;
	QWidget *m_labelListContainer;
	QWidget *m_fileListContainer;

	QToolButton *m_editButton;
	QListWidget *m_labelList;

	QDockWidget *m_dock;
	QDockWidget *m_filedock;
	QScrollArea *m_scrollArea;
	QWidgetAction *m_zoom;
	ToolBar *m_tools;

	QListWidget *m_fileListWidget;
	QVBoxLayout *m_filelistLayout;
	QDockWidget::DockWidgetFeatures m_dockFeatures;

	QLabel *m_labelCoordinates;

	//store actions and menus, it can be found by key.
	QMap<QString, QObject *> m_actions;

public:
	UiManager(QWidget *parent);
	~UiManager();

	void initUi();
	void setSrMainWin(QMainWindow *win);
	QMainWindow *getSrMainWin() const;
	bool addToContainer(const QString &key,  QObject * const value);
	

	ToolBar *newToolBar(const QString &name, QVector<QAction *> actions);
	QAction *findAction(const QString &key);
	QMenu *findMenu(const QString &key);
	QObject *findObject(const QString &key);
	QStringList getGroupByName(const QString &configname);
	QVector<QObject *> findGroupObj(const QStringList &keylist);
	
	
private:
	void registerConfigTable(const QString &name, const QString *p, unsigned int size);
	

private:	
	bool initActions();
	void clearActions();

	void print_map();

private:
	QMap<QString, ConfigArrayInfo> m_configTable;
	MainWindow * SR_MAINWIN;
};
