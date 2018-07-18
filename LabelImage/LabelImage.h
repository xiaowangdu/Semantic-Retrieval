#ifndef LABELIMAGE_H
#define LABELIMAGE_H

#include <QtWidgets/QWidget>
#include <QMessageBox>
#include <QImage>
#include <QTimer>
#include <QMainWindow>
#include <QImageReader>
#include "GeneratedFiles/ui_LabelImage.h"
#include "UiManager.hpp"
#include "../utility/Settings.hpp"
#include "../utility/Constants.hpp"
#include "../Widgets/fancytabwidget.h"
#include "../LabelImage/Shape.hpp"
#include "../XmlHelper/VocXmlReader.hpp"
#include "../XmlHelper/VocXmlWriter.hpp"
#include "Lib.h"
#include "LabelFile.hpp"

class LabelImage : public QWidget
{
	Q_OBJECT
public:
	enum ZoomMode {
		FIT_WINDOW, FIT_WIDTH, MANUAL_ZOOM
	};

	LabelImage(QWidget *parent);
	~LabelImage();

	QString getFormat() const;
	void setFormat(const QString format);
	bool loadFile(const QString &filepath);
	UiManager *getUiManager();
	void setFancyTabWidget(FancyTabWidget *tabwidget);
	void setTabPageIndex(int index);
	void closeEvent(QCloseEvent *ev);

protected: 
	
	void resizeEvent(QResizeEvent *ev);

public slots:
	void close(bool b);
	void openFile(bool b = false);
	void openDirDialog(bool b = false, const QString &dirpath = "");
	void changeSavedirDialog(bool b = false);
	void openAnnotationDialog(bool b);
	void openNextImg(bool b = false);
	void openPrevImg(bool b);
	void verifyImg(bool b);
	void saveFile(bool b = false);
	void changeFormat(bool b);
	void saveFileAs(bool b = false);
	void closeFile(bool b);
	void resetAll(bool b);
	void chooseColor1(bool b);
	void setCreateMode(bool b);
	void setEditMode(bool b);
	void createShape(bool b);
	void deleteSelectedShape(bool b);
	void copySelectedShape(bool b);
	void toggleAdvancedMode(bool b = true);
	void togglePolygons(bool b);
	void showTutorialDialog(bool b);
	void showInfoDialog(bool b);
	void addZoomIn(bool);
	void addZoomOut(bool);
	void addZoomOrg(bool);
	void setFitWindow(bool b);
	void setFitWidth(bool b);
	void editLabel(bool b);
	void chshapeLineColor(bool b);
	void chshapeFillColor(bool b);
	void addZoom(int increment = 10);
	void loadRecent(const QString& filename);
	void fileitemDoubleClicked(QListWidgetItem *item);
	void zoomRequest(int delta);
	void scrollRequest(int delta, Qt::Orientation orientation);
	void newShape();
	void paintCanvas(int val = 0);
	void shapeSelectionChanged(bool selected = false);
	void toggleDrawingSensitive(bool drawing = true);
	void labelItemChanged(QListWidgetItem *);
	void onMousePositionChange(int, int);
	void addBottomWidget(int index);
	void labelSelectionChanged();

private:
	void initSingleSlotConnect();
	void initFromConfig();
	bool discardChangesDialog();
	QMessageBox::StandardButton errorMessage(const QString &title, const QString &msg);
	bool mayContinue();
	void resetState();
	void importDirImages(const QString &dirpath);
	QStringList scanAllImages(const QString folderPath);
	void saveFileAndHint(const QString &filepath);
	void saveAnnotationFile(const QString &filepath);
	void setClean();
	QString saveFileDialog();
	QString currentPath();
	void status(const QString &msg, unsigned int delay = 5000);
	void loadShapes(const QVector<ShapeData> &shapes);
	void addBoxShape(Shape *const shape);
	void removeBoxShape(Shape *const shape);
	void adjustScale(bool initial = false);
	qreal scaleFitWindow();
	qreal scaleFitWidth();
	void addRecentFile(const QString &filepath);
	void toggleActions(bool value = true);
	void loadPascalXMLByFilename(const QString &xmlPath);
	void populateModeActions();
	bool beginner();
	void updateFileMenu();
	void setDirty();
	void toggleDrawMode(bool edit = true);
	QListWidgetItem * currentItem();
	bool advanced();
	void setZoom(int value);
	void loadPredefinedClasses(const QString & filename);
	

private:
	Ui::Form autoui;
	UiManager *ui;
	QMainWindow *_MainWindow;

	FancyTabWidget *m_fancyTabWidget;
	int m_tabPageIndex = -1;

	Settings m_settings;
	bool m_dirty = false;
	bool m_fitWindow = false;
	bool m_difficult = false;
	bool m_isLoadFromDir = false;
	bool m_noSelectionSlot = false;

	int m_maxRecentCounts = 1;

	QString m_defaultSaveDir;
	QString m_currentFilePath;
	QString m_currentDir;
	QString m_usingFormat = PASCAL_VOC_FORMAT;
	QString m_lastOpenDir;
	QString m_saveDir;

	QString m_prevLabelText = "";
	QString m_lastLabel = "";

	QStringList m_imgList;
	QStringList m_recentFiles;
	QStringList m_labelsPredefined;

	QColor m_lineColor;
	QColor m_fillColor;

	LabelFile * m_labelFile;
	QImage *m_image;

	int m_zoomLevel = 100;
	ZoomMode m_zoomMode = MANUAL_ZOOM;
	bool fitWindow = false;

	bool m_beginner = true;

	//test
	Canvas *canvas;
	//store maps from item to shape.
	QMap<QListWidgetItem *, Shape *> m_itemsToShapes;
};



#endif // LABELIMAGE_H
