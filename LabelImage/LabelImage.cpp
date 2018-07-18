#include "LabelImage.h"
#include "../utility/Logging.hpp"
#include "../utility/MacroDef.h"
#include "../Common/CommonFunctions.h"
#include <QDebug>
#include <QBuffer>
#include <QFileInfo>
#include <QFileDialog>
#include <QScrollBar>
#include <QStatusBar>
#include <QCursor>
#include <QApplication>

#define FIND_ACTION(Name) ui->findAction(Name)

#define ACTION_TRIGGER_SINGLE_SLOT_CONNECT(Key, Slot) SINGLE_SLOT_CONNECT(ui->findAction(Key), triggered(bool), this, Slot)

LabelImage::LabelImage(QWidget *parent)
	: QWidget(parent),
	_MainWindow(qobject_cast<QMainWindow *>(parent)),
	m_fancyTabWidget(NULL)
{
	autoui.setupUi(this);
	setParent(parent);
	
	m_settings.load();
	loadPredefinedClasses("F:/workspace/spyder_prj_test/data/predefined_classes.txt");

	ui = new UiManager(this);
	ui->initUi();
	

	m_image = new QImage();
	m_labelFile = NULL;

	m_currentFilePath = "";
	m_recentFiles.clear();
	//m_lineColor = QColor();
	//m_fillColor = QColor();
	m_zoomLevel = 100;
	m_fitWindow = false;
	// Add Chris;
	m_difficult = false;
	m_saveDir = "";


	initFromConfig();
	initSingleSlotConnect();


	updateFileMenu();

	if (!m_currentFilePath.isEmpty()) {
		if (QFileInfo(m_currentFilePath).isDir()) {
			QTimer::singleShot(0, this, SLOT(importDirImages(m_currentFilePath)));
		}
		QTimer::singleShot(0, this, SLOT(loadFile(m_currentFilePath)));
	}

	SINGLE_SLOT_CONNECT(ui->m_zoomWidget, valueChanged, this, paintCanvas);
	
	populateModeActions();

	if (!m_currentFilePath.isEmpty() && QFileInfo(m_currentFilePath).isDir()) {
		openDirDialog(false, m_currentFilePath);
	}

	
}

LabelImage::~LabelImage()
{

	
}

QString LabelImage::getFormat() const
{
	return m_usingFormat;
}

void LabelImage::setFormat(const QString format)
{
	if (format == PASCAL_VOC_FORMAT) {
		ui->findAction("save_format")->setText("PascalVOC");
		ui->findAction("save_format")->setIcon(newIcon("format_voc"));
		m_usingFormat = PASCAL_VOC_FORMAT;
	}
	else if (format == YOLO_FORMAT) {
		ui->findAction("save_format")->setText("YOLO");
		ui->findAction("save_format")->setIcon(newIcon("format_yolo"));
		m_usingFormat = YOLO_FORMAT;
	}
}


void LabelImage::initSingleSlotConnect()
{
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("quit", close(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("open", openFile(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("opendir", openDirDialog(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("changeSavedir", changeSavedirDialog(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("openAnnotation", openAnnotationDialog(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("openNextImg", openNextImg(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("openPrevImg", openPrevImg(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("verify", verifyImg(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("save", saveFile(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("save_format", changeFormat(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("saveAs", saveFileAs(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("close", closeFile(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("resetAll", resetAll(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("color1", chooseColor1(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("createMode", setCreateMode(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("editMode", setEditMode(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("create", createShape(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("delete", deleteSelectedShape(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("copy", copySelectedShape(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("advancedMode", toggleAdvancedMode(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("hideAll", togglePolygons(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("showAll", togglePolygons(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("help", showTutorialDialog(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("showInfo", showInfoDialog(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("zoomIn", addZoomIn(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("zoomOut", addZoomOut(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("zoomOrg", addZoomOrg(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("fitWindow", setFitWindow(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("fitWidth", setFitWidth(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("edit", editLabel(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("shapeLineColor", chshapeLineColor(bool));
	ACTION_TRIGGER_SINGLE_SLOT_CONNECT("shapeFillColor", chshapeFillColor(bool));

	SINGLE_SLOT_CONNECT(ui->m_fileListWidget, itemDoubleClicked(QListWidgetItem *), this, fileitemDoubleClicked(QListWidgetItem *));
	SINGLE_SLOT_CONNECT(ui->m_canvas, zoomRequest(int), this, zoomRequest(int));
	SINGLE_SLOT_CONNECT(ui->m_canvas, newShape(), this, newShape());
	SINGLE_SLOT_CONNECT(ui->m_canvas, shapeMoved, this, setDirty);
	SINGLE_SLOT_CONNECT(ui->m_canvas, selectionChanged(bool), this, shapeSelectionChanged(bool));
	SINGLE_SLOT_CONNECT(ui->m_canvas, drawingPolygon(bool), this, toggleDrawingSensitive(bool));
	SINGLE_SLOT_CONNECT(ui->m_canvas, scrollRequest(int, Qt::Orientation), this, scrollRequest(int, Qt::Orientation));
	SINGLE_SLOT_CONNECT(ui->m_canvas, mousePositionChanged(int, int), this, onMousePositionChange(int, int));

	SINGLE_SLOT_CONNECT(ui->m_zoomWidget, valueChanged(int), this, paintCanvas(int));
	
	SINGLE_SLOT_CONNECT(ui->m_labelList, itemActivated(QListWidgetItem *), this, labelSelectionChanged());
	SINGLE_SLOT_CONNECT(ui->m_labelList, itemSelectionChanged(), this, labelSelectionChanged());
	SINGLE_SLOT_CONNECT(ui->m_labelList, itemDoubleClicked(QListWidgetItem *), this, editLabel(bool));
	SINGLE_SLOT_CONNECT(ui->m_labelList, itemChanged(QListWidgetItem *), this, labelItemChanged(QListWidgetItem *));
}

void LabelImage::initFromConfig()
{
	//load config.
	QByteArray bytes = m_settings[SETTING_RECENT_FILES];
	if (!bytes.isEmpty()) {
		QList<QString> list;
		m_settings.decode_element(&bytes, list);
		m_recentFiles = QStringList(list);
	}

	bytes = m_settings[SETTING_WIN_SIZE];
	if (!bytes.isEmpty()) {
		QSize size;
		m_settings.decode_element(&bytes, size);
		resize(size);
	}
	else {
		resize(QSize(1000, 700));
	}

	bytes = m_settings[SETTING_WIN_POSE];
	if (!bytes.isEmpty()) {
		QPoint pos;
		m_settings.decode_element(&bytes, pos);
		move(pos);
	}
	else {
		move(QPoint(0, 0));
	}

	bytes = m_settings[SETTING_SAVE_DIR];
	if (!bytes.isEmpty()) {
		QString dir;
		m_settings.decode_element(&bytes, dir);
		m_saveDir = dir;
	}

	bytes = m_settings[SETTING_LAST_OPEN_DIR];
	if (!bytes.isEmpty()) {
		QString dir;
		m_settings.decode_element(&bytes, dir);
		m_lastOpenDir = dir;
	}
	else {
		if (!m_saveDir.isEmpty() && QFileInfo::exists(m_saveDir)) {
			m_defaultSaveDir = m_saveDir;
			_MainWindow->statusBar()->showMessage(QString("%1 started. Annotation will be saved to %2").arg(__APPNAME__).arg(m_defaultSaveDir));
			_MainWindow->statusBar()->show();
		}
	}

	_MainWindow->restoreState(m_settings[SETTING_WIN_STATE]);
	bytes = m_settings[SETTING_LINE_COLOR];
	if (!bytes.isEmpty()) {
		QColor color;
		m_settings.decode_element(&bytes, color);
		m_lineColor = color;
	}
	else {
		m_lineColor = DEFAULT_LINE_COLOR;
	}
	ui->m_canvas->setDrawingColor(m_lineColor);

	bytes = m_settings[SETTING_FILL_COLOR];
	if (!bytes.isEmpty()) {
		QColor color;
		m_settings.decode_element(&bytes, color);
		m_fillColor = color;
	}
	else {
		m_fillColor = DEFAULT_FILL_COLOR;
	}

	bytes = m_settings[SETTING_ADVANCE_MODE];
	if (!bytes.isEmpty()) {
		bool x;
		m_settings.decode_element(&bytes, x);
		if (x) {
			QAction * actions = ui->findAction("advancedMode");
			actions->setChecked(true);
			toggleAdvancedMode();
		}
	}
}


bool LabelImage::loadFile(const QString &filepath)
{
	resetState();
	ui->m_canvas->setEnabled(false);

	QString path = filepath;
	if (path.isEmpty()){
		QByteArray bytes = m_settings[SETTING_FILENAME];
		if (!bytes.isEmpty()) {
			QString p;
			m_settings.decode_element(&bytes, p);
			path = p;
		}
	}

	if (path.isEmpty()) {
		return false;
	}
	QFileInfo fileinfo(path);
	if (!fileinfo.exists()) {
		return false;
	}

	//if find in list widget, highlight this item.
	if (ui->m_fileListWidget->count() > 0) {
		int index = m_imgList.indexOf(path);
		if (index >= 0) {
			QListWidgetItem *fileWidgetItem = ui->m_fileListWidget->item(index);
			fileWidgetItem->setSelected(true);		
		}
	}

	if (LabelFile::isLabelFile(path)) {
		m_labelFile = new LabelFile();
		//m_lineColor = QColor();
		//m_fillColor = QColor();
	}

	//read image.
	if (!m_image->load(path)) {
		errorMessage("Error opening file",
			QString("<p>Make sure <i>%1</i> is a valid image file.").arg(path));
		status(QString("Error reading %1").arg(path));
		return false;
	}

	status(QString("Loaded %1").arg(fileinfo.fileName()));
	m_currentFilePath = path;
	m_lastOpenDir = fileinfo.absolutePath();

	ui->m_canvas->loadPixmap(QPixmap::fromImage(*m_image));
	//ui->m_canvas->loadPixmap(path);

	if (m_labelFile != NULL) {
		//TODO:
		//parse xml info and load shaps from the result.
	}

	setClean();
	ui->m_canvas->setEnabled(true);
	adjustScale(true);
	paintCanvas();
	addRecentFile(m_currentFilePath);
	toggleActions(true);

	QFileInfo info(m_currentFilePath);
	QString basename = info.baseName();
	QString xmlpath, txtpath;

	if (!m_defaultSaveDir.isEmpty()) {
		xmlpath = QDir::toNativeSeparators(m_defaultSaveDir + QDir::separator() + basename + XML_EXT);
		txtpath = QDir::toNativeSeparators(m_defaultSaveDir + QDir::separator() + basename + TXT_EXT);
	}
	else {
		xmlpath = QDir::toNativeSeparators(info.absolutePath() + QDir::separator() + basename + XML_EXT);
		txtpath = QDir::toNativeSeparators(info.absolutePath() + QDir::separator() + basename + TXT_EXT);
	}

	if (QFileInfo(xmlpath).exists()) {
		loadPascalXMLByFilename(xmlpath);
	}
	else if (QFileInfo(txtpath).exists()) {
		//TODO:
	}

	setWindowTitle(__APPNAME__ + " " + m_currentFilePath);
	if (ui->m_labelList->count()) {
		ui->m_labelList->setCurrentItem(ui->m_labelList->item(ui->m_labelList->count() - 1));
		ui->m_labelList->item(ui->m_labelList->count() - 1)->setSelected(true);
	}

	ui->m_canvas->setFocus();
	return true;
}

UiManager *LabelImage::getUiManager()
{
	return ui;
}

void LabelImage::setFancyTabWidget(FancyTabWidget *tabwidget)
{
	m_fancyTabWidget = tabwidget;
	if (m_fancyTabWidget) {
		SINGLE_SLOT_CONNECT(m_fancyTabWidget, currentChanged(int), this, addBottomWidget(int));
	}
}

void LabelImage::setTabPageIndex(int index)
{
	m_tabPageIndex = index;
}

void LabelImage::closeEvent(QCloseEvent *ev)
{
	if (!mayContinue()) {
		ev->ignore();
	}

	if (m_isLoadFromDir) {
		QString filename = m_currentFilePath.isEmpty() ? "" : m_currentFilePath;
		m_settings.new_element(SETTING_FILENAME, filename);
	}
	else {
		m_settings.new_element(SETTING_FILENAME, QString(""));
	}

	m_settings.new_element(SETTING_WIN_SIZE, size());
	m_settings.new_element(SETTING_WIN_POSE, pos());
	m_settings.new_element(SETTING_WIN_STATE, _MainWindow->saveState());
	m_settings.new_element(SETTING_LINE_COLOR, m_lineColor);
	m_settings.new_element(SETTING_FILL_COLOR, m_fillColor);
	m_settings.new_element(SETTING_RECENT_FILES, (QList<QString>)m_recentFiles);
	m_settings.new_element(SETTING_ADVANCE_MODE, !m_beginner);

	if (!m_defaultSaveDir.isEmpty() && QDir(m_defaultSaveDir).exists()) {
		m_settings.new_element(SETTING_SAVE_DIR, m_defaultSaveDir);
	}
	else {
		m_settings.new_element(SETTING_SAVE_DIR, QString(""));
	}

	if (!m_lastOpenDir.isEmpty() && QDir(m_lastOpenDir).exists()) {
		m_settings.new_element(SETTING_LAST_OPEN_DIR, m_lastOpenDir);
	}
	else {
		m_settings.new_element(SETTING_LAST_OPEN_DIR, QString(""));
	}

	m_settings.new_element(SETTING_AUTO_SAVE, ui->findAction("autoSaving")->isChecked());
	m_settings.new_element(SETTING_SINGLE_CLASS, ui->findAction("singleClassMode")->isChecked());
	m_settings.save();
}

void LabelImage::resizeEvent(QResizeEvent *ev)
{
	if (ui->m_canvas != NULL && !m_image->isNull()
		&& m_zoomMode != MANUAL_ZOOM) {
		adjustScale();
	}

	QWidget::resizeEvent(ev);
}

bool LabelImage::discardChangesDialog()
{
	QString msg = "You have unsaved changes, proceed anyway?";
	return QMessageBox::Yes == QMessageBox::warning(this, "Attention", msg, QMessageBox::Yes | QMessageBox::No);
}

QMessageBox::StandardButton LabelImage::errorMessage(const QString &title, const QString &msg)
{
	return QMessageBox::critical(this, title,
		QString("<p><b>%1</b></p>%2").arg(title).arg(msg));
}

bool LabelImage::mayContinue()
{
	return !(m_dirty && !discardChangesDialog());
}

void LabelImage::resetState()
{
	m_itemsToShapes.clear();
	ui->m_labelList->clear();
	m_currentFilePath = "";
	if (m_labelFile != NULL) {
		delete m_labelFile;
		m_labelFile = NULL;
	}

	ui->m_canvas->resetState();
	ui->m_labelCoordinates->clear();
}

void LabelImage::importDirImages(const QString &dirpath)
{
	if (!mayContinue() || dirpath.isEmpty()) {
		return;
	}

	m_lastOpenDir = dirpath;
	qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << m_lastOpenDir;
	m_currentDir = dirpath;
	m_isLoadFromDir = true;
	m_currentFilePath = "";
	ui->m_fileListWidget->clear();
	m_imgList = scanAllImages(dirpath);
	openNextImg();

	for (int i = 0; i < m_imgList.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem(m_imgList.at(i));
		ui->m_fileListWidget->addItem(item);
	}
}

QStringList LabelImage::scanAllImages(const QString folderPath)
{
	QStringList allfiles, allowedfilespath;
	QStringList ext = getSupportedImgExtensions();

	listDir(folderPath, allfiles);
	for (int i = 0; i < allfiles.size(); ++i) {
		QFileInfo fileinfo(allfiles.at(i));
		if (ext.contains(fileinfo.suffix())) {
			allowedfilespath << QDir::toNativeSeparators(folderPath + QDir::separator() + allfiles.at(i));
		}
	}

	return allowedfilespath;
}

void LabelImage::saveFileAndHint(const QString &filepath)
{
	if (filepath.isEmpty()) {
		errorMessage("error", "File path is Null.");
		return;
	}

	saveAnnotationFile(filepath);
	setClean();
	_MainWindow->statusBar()->showMessage(QString("Saved to  %1").arg(filepath));
	_MainWindow->statusBar()->show();
}

void LabelImage::saveAnnotationFile(const QString &filepath)
{
	if (m_labelFile == NULL) {
		m_labelFile = new LabelFile();
		m_labelFile->setVerified(ui->m_canvas->getVerified());
	}

	QVector<ShapeData> shapes;
	QVector<Shape *> boxes = ui->m_canvas->getShapes();
	for (int i = 0; i < boxes.size(); i++) {
		shapes.append(*((*boxes[i]).extractShapeData()));
	}

	if (m_usingFormat == PASCAL_VOC_FORMAT) {
		QString annotationFilePath = filepath;
		annotationFilePath += XML_EXT;

		qDebug() << "Img: " << m_currentFilePath << " -> Its xml: " << annotationFilePath;
		m_labelFile->savePascalVocFormat(annotationFilePath, shapes, m_currentFilePath);
	}
	else {
		//TODO:
		qDebug() << "save as another type of file.";
	}
}

void LabelImage::setClean()
{
	m_dirty = false;
	FIND_ACTION("save")->setEnabled(false);
	FIND_ACTION("create")->setEnabled(true);
}

QString LabelImage::saveFileDialog()
{
	QString caption = QString("%1 - Choose File").arg(__APPNAME__);
	QString filters = QString("File (*%1)").arg(XML_EXT);
	QString openDialogPath = currentPath();

	QFileDialog dlg(this, caption, openDialogPath, filters);
	dlg.setDefaultSuffix(XML_EXT.right(3)); //.xml
	dlg.setAcceptMode(QFileDialog::AcceptSave);
	dlg.selectFile(openDialogPath);
	dlg.setOption(QFileDialog::DontUseNativeDialog, false);
	if (dlg.exec()) {
		return dlg.selectedFiles()[0];
	}

	return "";
}

QString LabelImage::currentPath()
{
	QFileInfo info(m_currentFilePath);
	if (info.isFile()) {
		return info.absoluteFilePath();
	}

	return QDir(".").absolutePath();
}

void LabelImage::status(const QString &msg, unsigned int delay)
{
	_MainWindow->statusBar()->showMessage(msg, delay);
}

void LabelImage::loadShapes(const QVector<ShapeData> &shapesdata)
{
	QVector<Shape *> s;
	for (int i = 0; i < shapesdata.size(); i++) {
		Shape *shape = new Shape(BOX, shapesdata[i].label);
		for (int j = 0; j < shapesdata[i].points.size(); j++) {
			shape->addPoint(shapesdata[i].points[j]);
		}

		shape->setDifficult(shapesdata[i].difficult.toInt());
		shape->setClose();
		s.append(shape);

		if (shapesdata[i].lineColor.isValid()) {
			shape->setLineColor(shapesdata[i].lineColor);
		}
		else {
			shape->setLineColor(generateColorByText(shapesdata[i].label));
		}

		if (shapesdata[i].fillColor.isValid()) {
			shape->setFillColor(shapesdata[i].fillColor);
		}
		else {
			shape->setFillColor(generateColorByText(shapesdata[i].label));
		}

		addBoxShape(shape);
	}

	ui->m_canvas->loadShapes(s);
}

void LabelImage::addBoxShape(Shape *const shape)
{
	QListWidgetItem *item = new QListWidgetItem(shape->getLabel());
	item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
	item->setCheckState(Qt::Checked);
	item->setBackground(generateColorByText(shape->getLabel()));

	m_itemsToShapes.insert(item, shape);
	ui->m_labelList->addItem(item);

	QVector<QObject *> actions= ui->findGroupObj(ui->getGroupByName("ONSHAPESPRESENT_CONFIG"));
	QAction * tmp = NULL;
	for (int i = 0; i < actions.size(); i++) {
		tmp = qobject_cast<QAction *>(actions[i]);
		if (bool(tmp)) {
			tmp->setEnabled(true);
		}
	}
}

void LabelImage::removeBoxShape(Shape *const shape)
{
	if (shape == NULL) {
		return;
	}

	QList<QListWidgetItem *> p = m_itemsToShapes.keys(shape);
	Q_ASSERT(p.size() == 1);

	ui->m_labelList->takeItem(ui->m_labelList->row(p[0]));

	ui->m_canvas->clearShape(shape);
	m_itemsToShapes.remove(p[0]);
}

void LabelImage::adjustScale(bool initial)
{
	qreal value = 0.0;
	if (initial) {
		value = scaleFitWindow();
	}
	else {
		switch (m_zoomMode) {
		case MANUAL_ZOOM:
		case FIT_WIDTH:
			value = scaleFitWindow();
			break;
		case FIT_WINDOW:
			value = scaleFitWindow();
			break;
		default:
			return;
		}
	}

	ui->m_zoomWidget->setValue(int(100 * value));
}

qreal LabelImage::scaleFitWindow()
{
	qreal e = 2.0;//  # So that no scrollbars are generated.
	qreal w1 = ui->m_scrollArea->width() - e;
	qreal h1 = ui->m_scrollArea->height() - e;
	qreal a1 = w1 / h1;

	// Calculate a new scale value based on the pixmap's aspect ratio.
	qreal w2 = ui->m_canvas->getPixmap()->width() - 0.0;
	qreal h2 = ui->m_canvas->getPixmap()->height() - 0.0;
	qreal a2 = w2 / h2;

	return a2 >= a1 ? w1 / w2 : h1 / h2;
}

qreal LabelImage::scaleFitWidth()
{
	qreal w = ui->m_scrollArea->width() - 2.0;
	return w / ui->m_canvas->getPixmap()->width();
}

void LabelImage::paintCanvas(int)
{
	Q_ASSERT(!m_image->isNull());
	ui->m_canvas->setScale(0.01 * ui->m_zoomWidget->value());
	ui->m_canvas->adjustSize();
	ui->m_canvas->update();
}

void LabelImage::addRecentFile(const QString &filepath)
{
	if (filepath.isEmpty()) {
		return;
	}

	if (m_recentFiles.contains(filepath)) {
		m_recentFiles.removeAll(filepath);
	}
	else if (m_recentFiles.size() >= m_maxRecentCounts) {
		m_recentFiles.pop_back();
	}

	m_recentFiles.insert(0, filepath);
}

void LabelImage::toggleActions(bool value)
{

	//ui->m_zoomWidget->setEnabled(value);
	
	QStringList actionlist = ui->getGroupByName(ZOOMACTIONS_CONFIG);
	actionlist << ui->getGroupByName(ONLOADACTIVE_CONFIG);
	
	QVector<QObject *> actionobjs = ui->findGroupObj(actionlist);
	for (int i = 0; i < actionobjs.size(); ++i) {
		//my types of object
		if (bool(qobject_cast<QWidgetAction *>(actionobjs[i]))) {
			QWidgetAction * p = qobject_cast<QWidgetAction *>(actionobjs[i]);
			p->setEnabled(value);
		}
		else if (bool(qobject_cast<QAction *>(actionobjs[i]))) {
			QAction * p = qobject_cast<QAction *>(actionobjs[i]);
			p->setEnabled(value);
		}
		else if (bool(qobject_cast<QMenu *>(actionobjs[i]))) {
			QMenu * p = qobject_cast<QMenu *>(actionobjs[i]);
			p->setEnabled(value);
		}
		else if (bool(qobject_cast<ZoomWidget *>(actionobjs[i]))) {
			ZoomWidget * p = qobject_cast<ZoomWidget *>(actionobjs[i]);
			p->setEnabled(value);
		}
		else {
			if (actionobjs[i] != NULL) {
				qDebug() << "Type is not allowed.";
				Q_ASSERT(0);
			}
		}
	}
}

void LabelImage::loadPascalXMLByFilename(const QString &xmlPath)
{
	setFormat(PASCAL_VOC_FORMAT);
	VocXmlReader xmlreader(xmlPath);
	loadShapes(xmlreader.getShapesData());
	ui->m_canvas->setVerified(xmlreader.isVerified());
}


void LabelImage::close(bool b)
{
	_MainWindow->close();
}

void LabelImage::openFile(bool b)
{
	
	if (!mayContinue()) {
		return;
	}

	if (m_currentFilePath.isEmpty()) {
		m_currentFilePath = m_lastOpenDir.isEmpty() ?  ".": m_lastOpenDir;
	}

	QFileInfo fileinfo(m_currentFilePath);
	QString path = fileinfo.absolutePath();

	QString filters = getSupportedImgFilters();

	filters = QString("Image & Label files (%1)").arg(filters);
	QString filename = QFileDialog::getOpenFileName(this, QString("%1 - Choose Image or Label file").arg(__APPNAME__), path, filters);

	if (!filename.isEmpty()) {
		loadFile(filename);
	}
	
}

void LabelImage::openDirDialog(bool b, const QString &dirpath)
{
	if (!mayContinue()) {
		return;
	}

	QString defaultOpenDirPath = dirpath.isEmpty() ? "." : dirpath;
	if (!m_lastOpenDir.isEmpty() && QDir(m_lastOpenDir).exists()) {
		defaultOpenDirPath = m_lastOpenDir;
	}
	else {
		defaultOpenDirPath = m_currentFilePath.isEmpty() ? "." : QFileInfo(m_currentFilePath).path();
	}

	QString targetDirPath = QFileDialog::getExistingDirectory(this,
		QString("%1 - Open Directory").arg(__APPNAME__), defaultOpenDirPath,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	importDirImages(targetDirPath);
}

void LabelImage::changeSavedirDialog(bool b)
{
	QString path;
	if (!m_defaultSaveDir.isEmpty()) {
		path = m_defaultSaveDir;
	}
	else {
		path = ".";
	}

	path = QFileDialog::getExistingDirectory(this,
		QString("%1 - Save annotations to the directory").arg(__APPNAME__), path, QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	if (!path.isEmpty()) {
		m_defaultSaveDir = path;
	}

	_MainWindow->statusBar()->showMessage(QString("%1 . Annotation will be saved to %2")
		.arg("Change saved folder").arg(m_defaultSaveDir));
	_MainWindow->statusBar()->show();
}

void LabelImage::openAnnotationDialog(bool b)
{
	qDebug() << "q slot openAnnotationDialog";
}

void LabelImage::openNextImg(bool b)
{
	if (FIND_ACTION("autoSaving")->isChecked()) {
		if (!m_defaultSaveDir.isEmpty()) {
			if (m_dirty) {
				saveFile();
			}
		}
		else {
			changeSavedirDialog();
			return;
		}
	}

	if (!mayContinue()) {
		return;
	}

	if (m_imgList.size() <= 0) {
		return;
	}

	QString filename;
	if (m_currentFilePath.isEmpty()) {
		filename = m_imgList[0];
	}
	//TODO:
	else {
		int currentIndex = m_imgList.indexOf(m_currentFilePath);
		if (currentIndex + 1 < m_imgList.size()) {
			filename = m_imgList[currentIndex + 1];
		}
			
	}

	if (!filename.isEmpty()) {
		loadFile(filename);
	}
}

void LabelImage::openPrevImg(bool b)
{
	if (FIND_ACTION("autoSaving")->isChecked()) {
		if (!m_defaultSaveDir.isEmpty()) {
			if (m_dirty) {
				saveFile();
			}
		}
		else {
			changeSavedirDialog();
			return;
		}
	}

	if (!mayContinue()) {
		return;
	}

	if (m_imgList.size() <= 0) {
		return;
	}

	if (m_currentFilePath.isEmpty()) {
		return;
	}

	QString filename;
	int currentIndex = m_imgList.indexOf(m_currentFilePath);
	if (currentIndex - 1 >= 0) {
		filename = m_imgList[currentIndex - 1];
		if (!filename.isEmpty()) {
			loadFile(filename);
		}
	}
}

void LabelImage::verifyImg(bool b)
{
	qDebug() << "q slot verifyImg";
}

void LabelImage::saveFile(bool b)
{
	if (m_currentFilePath.isEmpty()) {
		return;
	}

	QFileInfo fileinfo(m_currentFilePath);
	const QString imgfilebasename = fileinfo.baseName();
	if (!m_defaultSaveDir.isEmpty()) {
		QFileInfo savedFile(m_defaultSaveDir, imgfilebasename);
		saveAnnotationFile(savedFile.absoluteFilePath());
	}
	else {
		const QString imgfolderpath = fileinfo.absoluteDir().absolutePath();
		QFileInfo savedFile(imgfolderpath, imgfilebasename);
		if (m_labelFile != NULL) {
			saveAnnotationFile(savedFile.absoluteFilePath());
			return;
		}
		saveAnnotationFile(saveFileDialog());
	}
	
}

void LabelImage::changeFormat(bool b)
{
	setFormat(m_usingFormat);
}

void LabelImage::saveFileAs(bool b)
{
	Q_ASSERT(m_image != NULL);
	//saveAnnotationFile(saveFileDialog());
}

void LabelImage::closeFile(bool b)
{
	qDebug() << "q slot closeFile";
}

void LabelImage::resetAll(bool b)
{
	qDebug() << "q slot resetAll";
}

void LabelImage::chooseColor1(bool b)
{
	QColor color = ui->m_colorDialog->getColor(m_lineColor, "Choose line color", DEFAULT_LINE_COLOR);

	if (color.isValid()) {
		m_lineColor = color;
		ui->m_canvas->setDrawingColor(color);
		ui->m_canvas->update();
		setDirty();
	}
}

void LabelImage::setCreateMode(bool b)
{
	qDebug() << "q slot setCreateMode";
	Q_ASSERT(advanced());
	toggleDrawMode(false);
}

void LabelImage::setEditMode(bool b)
{
	Q_ASSERT(advanced());
	toggleDrawMode(true);
	labelSelectionChanged();
}

void LabelImage::createShape(bool b)
{
	if (beginner()) {
		ui->m_canvas->setEditing(false);
		ui->findAction("create")->setEnabled(false);
	}
}


void LabelImage::deleteSelectedShape(bool b)
{
	qDebug() << "q slot deleteSelectedShape";
	removeBoxShape(ui->m_canvas->deleteSelected());
	setDirty();

	if (m_itemsToShapes.size() <= 0) {
		QVector<QObject *> actions = ui->findGroupObj(ui->getGroupByName("ONSHAPESPRESENT_CONFIG"));
		QAction * tmp = NULL;
		for (int i = 0; i < actions.size(); i++) {
			tmp = qobject_cast<QAction *>(actions[i]);
			if (bool(tmp)) {
				tmp->setEnabled(false);
			}
		}
	}
}

void LabelImage::copySelectedShape(bool b)
{
	qDebug() << "q slot copySelectedShape";
	addBoxShape(ui->m_canvas->copySelectedShape());
	shapeSelectionChanged(true);
}

void LabelImage::toggleAdvancedMode(bool b)
{
	qDebug() << "jjjjjjjjjjjjjjjjjjjjjj";
	m_beginner = !b;
	ui->m_canvas->setEditing(true);
	populateModeActions();
	ui->m_editButton->setVisible(!b);

	if (b) {
		ui->findAction("createMode")->setEnabled(true);
		ui->findAction("editMode")->setEnabled(true);
		ui->m_dock->setFeatures(ui->m_dock->features() | ui->m_dockFeatures);
	}
	else {
		ui->m_dock->setFeatures(ui->m_dock->features() ^ ui->m_dockFeatures);
	}
}

void LabelImage::populateModeActions()
{
	QString toolname, menuname;
	if (beginner()) {
		toolname = BEGINNER_CONFIG; menuname = BEGINNERCONTEXT_CONFIG;
	}
	else {
		toolname = ADVANCED_CONFIG; menuname = ADVANCEDCONTEXT_CONFIG;
	}
	
	ui->m_tools->clear();
	QStringList list = ui->getGroupByName(toolname);
	addActionsIn(ui->m_tools, ui->findGroupObj(list));
	ui->m_canvas->getMenu().first->clear();
	
	qDebug() << ui->getGroupByName(menuname);
	addActionsIn(ui->m_canvas->getMenu().first, ui->findGroupObj(ui->getGroupByName(menuname)));
	ui->findMenu("menu_edit")->clear();
	
	QStringList editlist;
	if (beginner()) {
		editlist << "create";
	}
	else {
		editlist << "createMode" << "editMode";
	}
	editlist << ui->getGroupByName(EDITMENU_CONFIG);
	addActionsIn(ui->findMenu("menu_edit"), ui->findGroupObj(editlist));
}

bool LabelImage::beginner()
{
	return m_beginner;
}

void LabelImage::updateFileMenu()
{
	QMenu * menu = ui->findMenu("recentFiles");
	menu->clear();
	for (int i = 0, index = 0; i < m_recentFiles.size(); i++) {
		QString filepath = m_recentFiles.at(i);
		if (filepath != m_currentFilePath && QFileInfo::exists(filepath)) {
			index += 1;
			QIcon icon = newIcon("labels");
			QAction * action = new QAction(icon, QString("&%1 %2").arg(index).arg(QFileInfo(filepath).fileName()), this);
			SINGLE_SLOT_CONNECT(action, triggered, this, loadRecent(filepath));
			menu->addAction(action);
		}

	}
}

void LabelImage::setDirty()
{
	m_dirty = true;
	ui->findAction("save")->setEnabled(true);
}



void LabelImage::toggleDrawMode(bool edit)
{
	ui->m_canvas->setEditing(edit);
	ui->findAction("createMode")->setEnabled(edit);
	ui->findAction("editMode")->setEnabled(!edit);
}

void LabelImage::labelSelectionChanged()
{
	QListWidgetItem *item = currentItem();
	if (item && ui->m_canvas->editing()) {
		m_noSelectionSlot = true;
		ui->m_canvas->selectShape(m_itemsToShapes[item]);
		Shape * s = m_itemsToShapes[item];
		ui->m_diffcButton->setChecked(s->getDifficult());
	}
}

QListWidgetItem * LabelImage::currentItem()
{
	QList<QListWidgetItem *> items = ui->m_labelList->selectedItems();
	if (items.size() > 0) {
		return items[0];
	}

	return NULL;
}

bool LabelImage::advanced()
{
	return !beginner();
}

void LabelImage::setZoom(int value)
{
	ui->findAction("fitWidth")->setChecked(false);
	ui->findAction("fitWindow")->setChecked(false);
	m_zoomMode = MANUAL_ZOOM;
	ui->m_zoomWidget->setValue(value);
}

void LabelImage::loadPredefinedClasses(const QString & filename)
{
	m_labelsPredefined = readFileFromTxt(filename);
}

void LabelImage::addBottomWidget(int index)
{
	//SR_MAINWIN->addToolBar(Qt::BottomToolBarArea, tb);
	//QLayout *layout = SR_MAINWIN->fancyTabWidget()->currentWidget()->layout();

	//ToolBar * tt = new ToolBar("test");
	//tt->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//tt->addAction(new QAction("op\nop"));
	//layout->addWidget(tt);

	//layout->addWidget(tb);
	if (m_tabPageIndex != -1 && index == m_tabPageIndex) {
		QLayout *layout = m_fancyTabWidget->currentWidget()->layout();

		if (ui->m_tools) {
			layout->addWidget(ui->m_tools);
		}

	}
}

void LabelImage::togglePolygons(bool b)
{
	QMapIterator<QListWidgetItem *, Shape *> iter(m_itemsToShapes);
	while (iter.hasNext()) {
		iter.next();
		(*iter.key()).setCheckState(b ? Qt::Checked : Qt::Unchecked);
	}
}

void LabelImage::showTutorialDialog(bool b)
{
	qDebug() << "q slot showTutorialDialog";
}

void LabelImage::showInfoDialog(bool b)
{
	qDebug() << "q slot showInfoDialog";
}

void LabelImage::addZoomIn(bool)
{
	addZoom(10);
}

void LabelImage::addZoomOrg(bool)
{
	setZoom(100);
}

void LabelImage::addZoomOut(bool)
{
	addZoom(-10);
}

void LabelImage::addZoom(int increment)
{
	qDebug() << "q slot addZoom";
	setZoom(ui->m_zoomWidget->value() + increment);
}

void LabelImage::setFitWindow(bool b)
{
	qDebug() << "q slot setFitWindow";
}

void LabelImage::setFitWidth(bool b)
{
	qDebug() << "q slot setFitWidth";
}

void LabelImage::editLabel(bool b)
{
	qDebug() << "q slot editLabel";
	if (!ui->m_canvas->editing()) {
		return;
	}

	QListWidgetItem * item = currentItem();
	QString text = ui->m_labelDialog->popUp(item->text());
	if (!text.isEmpty()) {
		item->setText(text);
		item->setBackground(generateColorByText(text));
		setDirty();
	}

}

void LabelImage::chshapeLineColor(bool b)
{
	qDebug() << "q slot chshapeLineColor";
}

void LabelImage::chshapeFillColor(bool b)
{
	qDebug() << "q slot chshapeFillColor";
}

void LabelImage::loadRecent(const QString& filename)
{
	if (mayContinue()) {
		loadFile(filename);
	}
}

void LabelImage::fileitemDoubleClicked(QListWidgetItem *item)
{
	int currentIndex = m_imgList.indexOf(item->text());
	if (currentIndex < m_imgList.size()) {
		QString filename = m_imgList[currentIndex];
		if (!filename.isEmpty()) {
			loadFile(filename);
		}
	}
}

void LabelImage::zoomRequest(int delta)
{
	QScrollBar *h_bar = ui->m_scrollArea->horizontalScrollBar();
	QScrollBar *v_bar = ui->m_scrollArea->verticalScrollBar();

	int h_bar_max = h_bar->maximum();
	int v_bar_max = v_bar->maximum();

	QCursor cursor = QCursor();
	QPoint pos = cursor.pos();
	QPoint relative_pos = QWidget::mapFromGlobal(pos);

	int cursor_x = relative_pos.x();
	int cursor_y = relative_pos.y();

	int w = ui->m_scrollArea->width();
	int h = ui->m_scrollArea->height();

	qreal margin = 0.1;
	qreal move_x = (cursor_x - margin * w) / (w - 2 * margin * w);
	qreal move_y = (cursor_y - margin * h) / (h - 2 * margin * h);

	move_x = qMin(qMax(move_x, 0.0), 1.0);
	move_y = qMin(qMax(move_y, 0.0), 1.0);

	qreal units = delta / (8 * 15);
	qreal scale = 10;
	addZoom(scale * units);

	int d_h_bar_max = h_bar->maximum() - h_bar_max;
	int d_v_bar_max = v_bar->maximum() - v_bar_max;

	qreal new_h_bar_value = h_bar->value() + move_x * d_h_bar_max;
	qreal new_v_bar_value = v_bar->value() + move_y * d_v_bar_max;

	h_bar->setValue(new_h_bar_value);
	v_bar->setValue(new_v_bar_value);
}

void LabelImage::scrollRequest(int delta, Qt::Orientation orientation)
{
	qreal units = -delta / (8 * 15);
	QScrollBar *bar = NULL;
	if (orientation == Qt::Horizontal) {
		bar = ui->m_scrollArea->horizontalScrollBar();
	}
	else if(orientation == Qt::Vertical) {
		bar = ui->m_scrollArea->verticalScrollBar();
	}
	else {
		return;
	}
	bar->setValue(bar->value() + bar->singleStep() * units);
}

void LabelImage::newShape()
{

	QString labeltext;
	if (!ui->m_useDefaultLabelCheckbox->isChecked() ||
		ui->m_defaultLabelTextLine->text().isEmpty()) {
		if (m_labelsPredefined.size() > 0) {
			if (ui->m_labelDialog != NULL) {
				delete ui->m_labelDialog;
				ui->m_labelDialog = NULL;
			}
			ui->m_labelDialog = new LabelDialog(m_labelsPredefined);
		}

		if (ui->findAction("singleClassMode")->isChecked() && !m_lastLabel.isEmpty()) {
			labeltext = m_lastLabel;
		}
		else {
			labeltext = ui->m_labelDialog->popUp(m_prevLabelText);
			m_lastLabel = labeltext;
		}
	}
	else {
		labeltext = ui->m_defaultLabelTextLine->text();
	}

	//add chris
	ui->m_diffcButton->setChecked(false);
	if (labeltext.isEmpty()) {
		ui->m_canvas->resetAllLines();
	}
	else {
		m_prevLabelText = labeltext;
		QColor generate_color = generateColorByText(labeltext);
		Shape *shape = ui->m_canvas->setLastLabel(labeltext, generate_color, generate_color);
		addBoxShape(shape);

		if (beginner()) {
			ui->m_canvas->setEditing(true);
			ui->findAction("create")->setEnabled(true);
		}
		else {
			ui->findAction("editMode")->setEnabled(true);
		}

		setDirty();
		if (!m_labelsPredefined.contains(labeltext)) {
			m_labelsPredefined << labeltext;
		}
	}

}
void LabelImage::shapeSelectionChanged(bool selected)
{
	qDebug() << "q slot shapeSelectionChanged";
	if (m_noSelectionSlot) {
		m_noSelectionSlot = false;
	}
	else {
		Shape * shape = ui->m_canvas->getSelectedShape();
		if (shape) {
			QListWidgetItem * item = m_itemsToShapes.key(shape, NULL);
			if (item != NULL) {
				item->setSelected(true);
			}
		}
		else {
			ui->m_labelList->clearSelection();
		}
	}
	
	ui->findAction("delete")->setEnabled(selected);
	ui->findAction("copy")->setEnabled(selected);
	ui->findAction("edit")->setEnabled(selected);
	ui->findAction("shapeLineColor")->setEnabled(selected);
	ui->findAction("shapeFillColor")->setEnabled(selected);
}

void LabelImage::toggleDrawingSensitive(bool drawing)
{
	qDebug() << "q slot toggleDrawingSensitive" << !drawing;
	ui->findAction("editMode")->setEnabled(!drawing);
	if (!drawing && beginner()) {
		qDebug() << "Cancel creation.";
		ui->m_canvas->setEditing(true);
		ui->m_canvas->restoreCursor();
		ui->findAction("create")->setEnabled(true);
	}
}
void LabelImage::labelItemChanged(QListWidgetItem * item)
{
	Shape * shape = m_itemsToShapes[item];
	QString label = item->text();
	if (label != shape->getLabel()) {
		shape->setLabel(item->text());
		shape->setLineColor(generateColorByText(shape->getLabel()));
		setDirty();
	}
	else {
		ui->m_canvas->setShapeVisible(shape, item->checkState() == Qt::Checked);
	}
}

void LabelImage::onMousePositionChange(int x, int y)
{
	QLabel *label = ui->m_labelCoordinates;
	label->setText(QString("X: %1; Y: %2").arg(x).arg(y));
}