#include "UiManager.hpp"
#include "Lib.h"
#include "LabelImage.h"
#include "../MainWindow/MainWindow.h"
#include "../utility/Logging.hpp"

#include <QStatusBar>
#include <QSplitter>
#include <QTabWidget>

#define VECTOR_NULL QVector<QAction *>()
#define VECTOR_ONE(Type, Value) QVector<Type>(1, Value)
#define VECTOR_ONE_ACTION(Val) VECTOR_ONE(QAction *, Value)
#define VECTOR_ONE_Menu(Val) VECTOR_ONE(QMenu *, Value)

#define CONST_STRING_ARRAY_SIZE(Array) sizeof(Array)/sizeof(QString)

const ActionDetail actions_config[] = {
	ActionDetail("&Quit", "Ctrl+Q", "quit", "Quit application", "quit"),
	ActionDetail("&Open", "Ctrl+O", "open", "Open image or label file", "open"),
	ActionDetail("&Open Dir", "Ctrl+u", "open", "Open Dir", "opendir"),
	ActionDetail("&Change Save Dir", "Ctrl+r", "open", "Change default saved Annotation dir", "changeSavedir"),
	ActionDetail("&Open Annotation", "Ctrl+Shift+O", "open", "Open Annotation", "openAnnotation"),
	ActionDetail("&Next Image", "d", "next", "Open Next", "openNextImg"),
	ActionDetail("&Prev Image", "a", "prev", "Open Prev", "openPrevImg"),
	ActionDetail("&Verify Image", "space", "verify", "Verify Image", "verify"),
	ActionDetail("&Save", "Ctrl+S", "save", "Save labels to file", "save", false),
	ActionDetail("&PascalVOC", "Ctrl+", "format_voc", "Change save format", "save_format"),
	ActionDetail("&Save As", "Ctrl+Shift+S", "save-as", "Save labels to a different file", "saveAs"),
	ActionDetail("&Close", "Ctrl+W", "close", "Close current file", "close"),
	ActionDetail("&ResetAll", "", "resetall", "Reset all", "resetAll"),
	ActionDetail("Box Line Color", "Ctrl+L", "color_line", "Choose Box line color", "color1"),
	ActionDetail("Create\nRectBox", "w", "new", "Start drawing Boxs", "createMode", false),
	ActionDetail("&Edit\nRectBox", "Ctrl+J", "edit", "Move and edit Boxs", "editMode", false),
	ActionDetail("Create\nRectBox", "w", "new", "Draw a new Box", "create", false),
	ActionDetail("Delete\nRectBox", "Delete", "delete", "Delete", "delete", false),
	ActionDetail("&Duplicate\nRectBox", "Ctrl+D", "copy", "Create a duplicate of the selected Box", "copy", false),
	ActionDetail("&Advanced Mode", "Ctrl+Shift+A", "expert", "Switch to advanced mode", "advancedMode", true, true),
	ActionDetail("&Hide\nRectBox", "Ctrl+H", "hide", "Hide all Boxs", "hideAll", false),
	ActionDetail("&Show\nRectBox", "Ctrl+A", "hide", "Show all Boxs", "showAll", false),
	ActionDetail("&Tutorial", "", "help", "Show demos", "help"),
	ActionDetail("&Information", "", "help", "Information", "showInfo"),
	ActionDetail("&Zoom In", "Ctrl++", "zoom-in", "Increase zoom level", "zoomIn", false),
	ActionDetail("&Zoom Out", "Ctrl+-", "zoom-out", "Decrease zoom level", "zoomOut", false),
	ActionDetail("&Original size", "Ctrl+=", "zoom", "Zoom to original size", "zoomOrg", false),
	ActionDetail("&Fit Window", "Ctrl+F", "fit-window", "Zoom follows window size", "fitWindow", false, true),
	ActionDetail("Fit &Width", "Ctrl+Shift+F", "fit-width", "Zoom follows window width", "fitWidth", false, true),
	ActionDetail("&Edit Label", "Ctrl+E", "edit", "Modify the label of the selected Box", "edit", false),
	ActionDetail("Shape &Line Color", "", "color_line", "Change the line color for this specific shape", "shapeLineColor", false),
	ActionDetail("Shape &Fill Color", "", "color", "Change the fill color for this specific shape", "shapeFillColor", false),

};

const QString menus_file_config[] = {
	"open",	"opendir",	"changeSavedir", "openAnnotation", "recentFiles", "save", "save_format", "saveAs", "close", "resetAll", "quit"
};

const QString menus_view_config[] = {
	"autoSaving",	"singleClassMode",	"labels", "advancedMode", "", "hideAll", "showAll", "", "zoomIn", "zoomOut", "zoomOrg", "", "fitWindow", "fitWidth"
};

const QString menus_help_config[] = {
	"help",	"showInfo"
};

const QString fileMenuActions_config[] = {
	"open",	"opendir",	"save",	"saveAs", "close",	"resetAll", "quit"
};

const QString editMenu_config[] = {
	"edit",	"copy",	"delete", "", "color1"
};

const QString beginnerContext_config[] = {
	"create", "edit", "copy", "delete"
};

const QString advancedContext_config[] = {
	"createMode", "editMode", "edit", "copy", "delete", "shapeLineColor", "shapeFillColor"
};

const QString onLoadActive_config[] = {
	"close", "create", "createMode", "editMode"
};

const QString onShapesPresent_config[] = {
	"saveAs", "hideAll", "showAll"
};

const QString beginner_config[] = {
	"open", "opendir", "changeSavedir", "openNextImg", "openPrevImg", "verify", "save", "save_format", "", "create", "copy", "delete", "", "zoomIn", "zoom", "zoomOut", "fitWindow", "fitWidth"
};

const QString zoomActions_config[] = {
	"zoomWidget", "zoomIn", "zoomOut", "zoomOrg", "fitWindow", "fitWidth"
};

const QString advanced_config[] = {
	"open", "opendir", "changeSavedir", "openNextImg", "openPrevImg", "save", "save_format", "", "createMode", "editMode", "", "hideAll", "showAll"
};

UiManager::UiManager(QWidget *parent)
	: m_win(parent)
{
	Q_ASSERT(m_win != NULL);
	setSrMainWin(qobject_cast<QMainWindow *>(m_win->parent()));

	registerConfigTable(MENUS_FILE_CONFIG, menus_file_config, CONST_STRING_ARRAY_SIZE(menus_file_config));
	registerConfigTable(MENUS_VIEW_CONFIG, menus_view_config, CONST_STRING_ARRAY_SIZE(menus_view_config));
	registerConfigTable(MENUS_HELP_CONFIG, menus_help_config, CONST_STRING_ARRAY_SIZE(menus_help_config));
	registerConfigTable(FILEMENUACTIONS_CONFIG, fileMenuActions_config, CONST_STRING_ARRAY_SIZE(fileMenuActions_config));
	registerConfigTable(EDITMENU_CONFIG, editMenu_config, CONST_STRING_ARRAY_SIZE(editMenu_config));
	registerConfigTable(BEGINNERCONTEXT_CONFIG, beginnerContext_config, CONST_STRING_ARRAY_SIZE(beginnerContext_config));
	registerConfigTable(ADVANCEDCONTEXT_CONFIG, advancedContext_config, CONST_STRING_ARRAY_SIZE(advancedContext_config));
	registerConfigTable(ONLOADACTIVE_CONFIG, onLoadActive_config, CONST_STRING_ARRAY_SIZE(onLoadActive_config));
	registerConfigTable(ONSHAPESPRESENT_CONFIG, onShapesPresent_config, CONST_STRING_ARRAY_SIZE(onShapesPresent_config));
	registerConfigTable(BEGINNER_CONFIG, beginner_config, CONST_STRING_ARRAY_SIZE(beginner_config));
	registerConfigTable(ZOOMACTIONS_CONFIG, zoomActions_config, CONST_STRING_ARRAY_SIZE(zoomActions_config));
	registerConfigTable(ADVANCED_CONFIG, advanced_config, CONST_STRING_ARRAY_SIZE(advanced_config));

}

UiManager::~UiManager() {
	
}

void UiManager::initUi()
{
	m_labelDialog = new LabelDialog(QStringList(), m_win);
	QSplitter *splitermain = new QSplitter(Qt::Horizontal, m_win);
	QSplitter *spliterright = new QSplitter(Qt::Vertical, splitermain);

	m_listLayout = new QVBoxLayout(m_win);
	m_listLayout->setContentsMargins(0, 0, 0, 0);

	m_useDefaultLabelCheckbox = new QCheckBox("Use default label");
	m_useDefaultLabelCheckbox->setChecked(false);

	m_defaultLabelTextLine = new QLineEdit();
	m_useDefaultLabelQHBoxLayout = new QHBoxLayout();
	m_useDefaultLabelQHBoxLayout->addWidget(m_useDefaultLabelCheckbox);
	m_useDefaultLabelQHBoxLayout->addWidget(m_defaultLabelTextLine);

	m_useDefaultLabelContainer = new QWidget();
	m_useDefaultLabelContainer->setLayout(m_useDefaultLabelQHBoxLayout);

	// Create a widget for edit and diffc button
	m_diffcButton = new QCheckBox("difficult");
	m_diffcButton->setChecked(false);

	m_editButton = new QToolButton();
	m_editButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	// Add some of widgets to listLayout
	m_listLayout->addWidget(m_editButton);
	m_listLayout->addWidget(m_diffcButton);
	m_listLayout->addWidget(m_useDefaultLabelContainer);

	// Create and add a widget for showing current label items
	m_labelList = new QListWidget();
	m_labelListContainer = new QWidget();
	m_labelListContainer->setLayout(m_listLayout);

	m_listLayout->addWidget(m_labelList);

	m_dock = new QDockWidget("Box Labels", m_win);
	m_dock->setObjectName("Labels");
	m_dock->setWidget(m_labelListContainer);

	m_fileListWidget = new QListWidget();
	m_filelistLayout = new QVBoxLayout();
	m_filelistLayout->setContentsMargins(0, 0, 0, 0);
	m_filelistLayout->addWidget(m_fileListWidget);

	m_fileListContainer = new QWidget();
	m_fileListContainer->setLayout(m_filelistLayout);
	m_filedock = new QDockWidget("File List", m_win);
	m_filedock->setObjectName("Files");
	m_filedock->setWidget(m_fileListContainer);

	spliterright->addWidget(m_dock);
	spliterright->addWidget(m_filedock);

	m_colorDialog = new ColorDialog(m_win);

	m_labelCoordinates = new QLabel("");
	SR_MAINWIN->statusBar()->addPermanentWidget(m_labelCoordinates);

	m_canvas = new Canvas(m_win);
	QScrollArea * scroll = new QScrollArea();
	m_scrollArea = scroll;
	scroll->setWidget(m_canvas);
	scroll->setWidgetResizable(true);

	splitermain->addWidget(scroll);
	splitermain->addWidget(spliterright);

	QList<int> widgetSizes;
	widgetSizes << 2 * SR_MAINWIN->size().width() / 3 << SR_MAINWIN->size().width() / 3;
	splitermain->setSizes(widgetSizes);

	QHBoxLayout *wrapper = new QHBoxLayout(m_win);
	wrapper->setContentsMargins(0, 0, 0, 0);
	wrapper->addWidget(splitermain);


	m_dockFeatures = QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable;
	m_filedock->setFeatures(m_filedock->features() ^ m_dockFeatures);
	m_dock->setFeatures(m_dock->features() ^ m_dockFeatures);

	bool cond = initActions();

	QAction * a = findAction("edit");
	m_editButton->setDefaultAction(a);

	QWidgetAction *zoom = new QWidgetAction(SR_MAINWIN);
	addToContainer("zoom", zoom);

	m_zoomWidget = new ZoomWidget();
	zoom->setDefaultWidget(m_zoomWidget);
	m_zoomWidget->setWhatsThis(QString("Zoom in or out of the image. Also accessible with %1 and %2 from the canvas.")
		.arg(formatShortcut("Ctrl+[-+]").arg(formatShortcut("Ctrl+Wheel"))));
	addToContainer("zoomWidget", m_zoomWidget);
	m_zoomWidget->setEnabled(false);

	QAction *labels = m_dock->toggleViewAction();
	labels->setText("Show/Hide Label Panel");
	labels->setShortcut(QKeySequence("Ctrl+Shift+L"));
	addToContainer("labels", labels);

	QMenu *labelMenu = new QMenu();
	QStringList slist;
	slist << "edit" << "delete";
	addActionsIn(labelMenu, findGroupObj(slist));
	addToContainer("labelMenu", (QObject *)labelMenu);

	m_labelList->setContextMenuPolicy(Qt::CustomContextMenu);

	QMenu *recentFiles = new QMenu("Open &Recent");
	//QMenu *recentFiles = assembleMenu(file, "Open &Recent", QVector<QMenu *>());
	addToContainer("recentFiles", recentFiles);

	QAction *autoSaving = new QAction("Auto Saving", SR_MAINWIN);
	addToContainer("autoSaving", autoSaving);

	QAction *singleClassMode = new QAction("Single Class Mode", SR_MAINWIN);
	addToContainer("singleClassMode", singleClassMode);

	QMenu *menu_file = addWinMenu(SR_MAINWIN, "&File", VECTOR_NULL);
	QStringList keylist = stringArray2List(menus_file_config, CONST_STRING_ARRAY_SIZE(menus_file_config));
	addActionsIn(menu_file, findGroupObj(keylist));
	addToContainer("menu_file", menu_file);

	QMenu *menu_edit = addWinMenu(SR_MAINWIN, "&Edit", VECTOR_NULL);
	//it's changed, so added by main window.
	//[LabelImage::populateModeActions]
	addToContainer("menu_edit", menu_edit);

	QMenu *menu_view = addWinMenu(SR_MAINWIN, "&View", VECTOR_NULL);
	keylist = stringArray2List(menus_view_config, CONST_STRING_ARRAY_SIZE(menus_view_config));
	addActionsIn(menu_view, findGroupObj(keylist));
	addToContainer("menu_view", menu_view);

	QMenu *menu_help = addWinMenu(SR_MAINWIN, "&Help", VECTOR_NULL);
	keylist = stringArray2List(menus_help_config, CONST_STRING_ARRAY_SIZE(menus_help_config));
	addActionsIn(menu_help, findGroupObj(keylist));
	addToContainer("menu_help", menu_help);

	m_tools = newToolBar("Tools", VECTOR_NULL);

	print_map();
//	Q_ASSERT(0);

	SR_MAINWIN->statusBar()->showMessage(QString("%1 started.").arg(__APPNAME__));
	SR_MAINWIN->statusBar()->show();
}

void UiManager::setSrMainWin(QMainWindow *win)
{
	SR_MAINWIN = qobject_cast<MainWindow *>(win);
}

QMainWindow *UiManager::getSrMainWin() const
{
	return SR_MAINWIN;
}

bool UiManager::addToContainer(const QString &key, QObject * const value)
{
	if (m_actions.count(key) != 0) {
		qDebug() << "action (key = " << key << ") already exist.";
		return false;
	}

	m_actions.insert(key, value);
	return true;
}

QStringList UiManager::getGroupByName(const QString &configname)
{
	QStringList res;
	if (configname.isEmpty()) {
		return res;
	}
	if (m_configTable.count(configname) <= 0) {
		return res;
	}

	ConfigArrayInfo bug = m_configTable[configname];

	return stringArray2List(bug.pointerTo, bug.size);
}


QVector<QObject *> UiManager::findGroupObj(const QStringList &keylist)
{
	QVector<QObject *> res;
	
	for (int i = 0; i < keylist.size(); ++i) {
		res.append(findObject(keylist.at(i)));
	}
	return res;
}

ToolBar *UiManager::newToolBar(const QString &name, QVector<QAction *> actions) 
{
	ToolBar * tb = new ToolBar(name);
	tb->setObjectName(QString("%1ToolBar").arg(name));
	// tb->setOrientation(Qt.Vertical);
	tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	addActionsIn(tb, actions);

	//SR_MAINWIN->addToolBar(Qt::BottomToolBarArea, tb);
	//QLayout *layout = SR_MAINWIN->fancyTabWidget()->currentWidget()->layout();

	//ToolBar * tt = new ToolBar("test");
	//tt->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//tt->addAction(new QAction("op\nop"));
	//layout->addWidget(tt);

	//layout->addWidget(tb);
	return tb;
}

void UiManager::registerConfigTable(const QString &name, const QString *configarray, unsigned int size)
{
	ConfigArrayInfo tmp;
	tmp.pointerTo = configarray;
	tmp.size = size;
	
	m_configTable.insert(name, tmp);
}

QAction *UiManager::findAction(const QString &key)
{
	return qobject_cast<QAction *>(findObject(key));
}

QMenu *UiManager::findMenu(const QString &key)
{
	return qobject_cast<QMenu *>(findObject(key));
}

QObject *UiManager::findObject(const QString &key)
{
	if (key.isEmpty()) {
		qDebug("try to find QObjecct (key = %s).", key);
		//TODO:
		return NULL;
	}

	if (m_actions.count(key) == 0) {
		qDebug("QObjecct (key = %s) not exist.", key);
		//TODO:
		return NULL;
	}


	return *m_actions.find(key);
}

bool UiManager::initActions() 
{
	Q_ASSERT(SR_MAINWIN != NULL);

	int counts = sizeof(actions_config) / sizeof(ActionDetail);
	if (counts == 0) {
		qDebug() << "No action be initialized.";
		return false;
	}

	for (int i = 0; i < counts; i++) {
		ActionDetail tmp = actions_config[i];
		QString key = tmp.actionKey;

		if (m_actions.count(key) != 0) {
			qDebug() << "action (key = " << key << ") already exist.";
			return false;
		}

		QAction * action = newAction(tmp, SR_MAINWIN);
		m_actions.insert(key, action);
	}

	return true;
}

void UiManager::clearActions()
{
	QMapIterator<QString, QObject *> iter(m_actions);
	while (iter.hasNext()) {
		iter.next();
		if (iter.value() != NULL) {
			delete (iter.value());
			m_actions[iter.key()] = NULL;
		}
	}

	m_actions.clear();
}


void UiManager::print_map()
{
	qDebug() << m_actions.size();
	QMapIterator<QString, QObject *> i(m_actions);
	while (i.hasNext()) {
		i.next();
		qDebug() << i.key() << ": " << i.value();
	}
}