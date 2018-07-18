#include "RetrievalTest.h"
#include "GeneratedFiles/ui_RetrievalTest.h"
#include "RetrievalConfig.h"
#include "ShrinkImageView.hpp"
#include "../Widgets/SimpleCanvas.hpp"
#include "RetrievalShowItem.hpp"
#include "../utility/MacroDef.h"
#include "../Common/CommonFunctions.h"
#include "../utility/Downloader.hpp"
#include "../LMDBGenerator/LMDBGenerator.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QUrl>
#include <QListWidgetItem>
#include <QTimer>

using namespace pystd;



RetrievalTest::RetrievalTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RetrievalTest)
{
    ui->setupUi(this);

	m_configView = new RetrievalConfig();
	m_downloader = new Downloader();

	QPalette pal;
	pal = ui->m_textBrowser->palette();
	pal.setColor(QPalette::Text, QColor(255, 255, 255));
	pal.setColor(QPalette::Base, QColor(0, 0, 0));
	ui->m_textBrowser->setPalette(pal);


	m_canvas = new SimpleCanvas();
	m_scroll = new QScrollArea();
	m_scroll->setWidget(m_canvas);
	m_scroll->setWidgetResizable(true);
	ui->m_dockOriginalImage->setWidget(m_scroll);
	SINGLE_SLOT_CONNECT(m_canvas, zoomRequest(int), this, zoomRequest(int));

	SINGLE_SLOT_CONNECT(ui->m_btnConfig, clicked(), this, onBtnConfig());
	SINGLE_SLOT_CONNECT(ui->m_btnDir, clicked(), this, selectImageDir());
	SINGLE_SLOT_CONNECT(ui->m_btnShowOrg, clicked(), this, showOriginalImage());

	SINGLE_SLOT_CONNECT(m_downloader, currentProgressChanged(qint64, qint64), this, progressChanged(qint64, qint64));
	SINGLE_SLOT_CONNECT(m_downloader, downloadComplete(bool), this, onDownloadComplete(bool));

	SINGLE_SLOT_CONNECT(ui->m_btnStartRetrieval, clicked(), this, onStartRetrieval());
	SINGLE_SLOT_CONNECT(ui->m_listWidget, itemDoubleClicked(QListWidgetItem *), this, onItemDoubleClicked(QListWidgetItem *));

	m_table = new ShrinkImageView();
	ui->m_dockRetrievalResult->setWidget(m_table);
	m_table->setColumnCount(1);
	m_table->setRowCount(1);

	m_writer = [this](std::string s) {
		QString str(s.c_str());
		if (str == "\n") return;

		this->onUpdateInfo(str);
	};
	
	// for test.
	ui->m_edtImagePath->setText("F:/workspace/project/data/105_0028.jpg");
}

RetrievalTest::~RetrievalTest()
{
    delete ui;
	delete m_configView;
	delete m_downloader;
}

Configure RetrievalTest::config() const
{
	return m_config;
}


QStringList RetrievalTest::retrievalImages(const QString &modulePath,
	const QString &moduleName,
	const Configure &config,
	const QString &targetImagePath,
	unsigned int topK)
{
	QStringList res;

	QString callFunStr = "retrieve_config";
	PyObject *pArg = NULL;
	pArg = Py_BuildValue("sssssss",
		config.rootDir.toStdString().c_str(),
		config.datasetDir.toStdString().c_str(),
		config.modelFile.toStdString().c_str(),
		config.modelDefFile.toStdString().c_str(),
		config.imgTrainList.toStdString().c_str(),
		config.binaryFile.toStdString().c_str(),
		config.featTrainFile.toStdString().c_str());

	CPythonHelper::getInstance()->processPyEvt(modulePath, moduleName, callFunStr, pArg, m_writer);
	//PyEval_CallObject(callFun, pArg);

	callFunStr = "retrieve_images";
	pArg = Py_BuildValue("si",
		targetImagePath.toStdString().c_str(),
		topK);


	PyObject *pVal = CPythonHelper::getInstance()->processPyEvt(modulePath, moduleName, callFunStr, pArg, m_writer);
	int size = PyList_Size(pVal);
	qDebug() << "List size: " << size;

	for (int i = 0; i< size; ++i) {
		PyObject *item = PyList_GetItem(pVal, i);
		if (PyList_Check(item)) {
			qDebug() << QString("Element is type of list.");
			continue;
		}

		char *cstr = PyUnicode_AsUTF8(item);
		res << QString(cstr);
	}

	return res;
}

void RetrievalTest::closeEvent(QCloseEvent *ev)
{

}

void RetrievalTest::onBtnConfig()
{
	m_configView->show();
}

void RetrievalTest::selectImageDir()
{
	QString filename = openImageDialog(this, "Select Image", m_configView->getImageLib(), "*.jpg");
	if (filename.isEmpty()) {
		return;
	}
	ui->m_edtImagePath->setText(filename);
}

void RetrievalTest::showOriginalImage()
{
	qDebug() << "llllll";
	RetrievalMode mode = (RetrievalMode)ui->m_comboBox->currentIndex();
	if (mode == PATH_MODE) {
		QString filename = ui->m_edtImagePath->text();
		if (filename.isEmpty()) {
			QString msg = "You must given image path.";
			QMessageBox::warning(this, "Attention", msg, QMessageBox::Ok);
			return;
		}

		m_canvas->loadPixmap(filename);
	}
	else{
		QUrl url(ui->m_edtUrl->text());
		if (url.isEmpty()) {
			QString msg = "Invalid url.";
			QMessageBox::warning(this, "Attention", msg, QMessageBox::Ok);
			return;
		}

		m_downloader->downloadFileFromURL(url, urlTestImgPath());
		ui->m_btnShowOrg->setEnabled(false);
		ui->m_btnStartRetrieval->setEnabled(false);
		QTimer::singleShot(0, this, SLOT(checkDownloadFinished()));
	}
}

void RetrievalTest::checkDownloadFinished()
{
	if (m_downloader->busy()) {
		QTimer::singleShot(100, this, SLOT(checkDownloadFinished()));
		return;
	}
	
	qDebug() << urlTestImgPath();
	m_canvas->loadPixmap(urlTestImgPath());
	ui->m_btnShowOrg->setEnabled(true);
	ui->m_btnStartRetrieval->setEnabled(true);

	clearProgress();
}

void RetrievalTest::onDownloadComplete(bool status)
{
	if (status) {
		m_canvas->loadPixmap(urlTestImgPath());
	}
}

void RetrievalTest::progressChanged(qint64 curbytes, qint64 totals)
{
	ui->m_progressBar->setMaximum(totals);
	ui->m_progressBar->setValue(curbytes);
}

void RetrievalTest::zoomRequest(int delta)
{
	qDebug() << delta;
	QScrollBar *h_bar = m_scroll->horizontalScrollBar();
	QScrollBar *v_bar = m_scroll->verticalScrollBar();

	int h_bar_max = h_bar->maximum();
	int v_bar_max = v_bar->maximum();

	QCursor cursor = QCursor();
	QPoint pos = cursor.pos();
	QPoint relative_pos = QWidget::mapFromGlobal(pos);

	int cursor_x = relative_pos.x();
	int cursor_y = relative_pos.y();

	int w = m_scroll->width();
	int h = m_scroll->height();

	qreal margin = 0.1;
	qreal move_x = (cursor_x - margin * w) / (w - 2 * margin * w);
	qreal move_y = (cursor_y - margin * h) / (h - 2 * margin * h);

	move_x = qMin(qMax(move_x, 0.0), 1.0);
	move_y = qMin(qMax(move_y, 0.0), 1.0);

	qreal units = delta / (8 * 15);
	qreal scale = 0.08;

	m_canvas->setScale(max(0.08, m_canvas->getScale() + scale * units));
	m_canvas->adjustSize();
	m_canvas->update();

	int d_h_bar_max = h_bar->maximum() - h_bar_max;
	int d_v_bar_max = v_bar->maximum() - v_bar_max;

	qreal new_h_bar_value = h_bar->value() + move_x * d_h_bar_max;
	qreal new_v_bar_value = v_bar->value() + move_y * d_v_bar_max;

	h_bar->setValue(new_h_bar_value);
	v_bar->setValue(new_v_bar_value);
}

void RetrievalTest::onUpdateInfo(const QString &info)
{
	ui->m_textBrowser->append(info);
}


qreal RetrievalTest::scaleFitWindow()
{
	qreal e = 2.0;//  # So that no scrollbars are generated.

	qreal w1 = m_scroll->width() - e;
	qreal h1 = m_scroll->height() - e;
	qreal a1 = w1 / h1;

	// Calculate a new scale value based on the pixmap's aspect ratio.
	qreal w2 = m_canvas->getPixmap()->width() - 0.0;
	qreal h2 = m_canvas->getPixmap()->height() - 0.0;
	qreal a2 = w2 / h2;

	return a2 >= a1 ? w1 / w2 : h1 / h2;
}

void RetrievalTest::updateRetrievalShow(const QStringList &images)
{
	if (images.size() <= 0) {
		return;
	}

	int knums = qMin((int)m_configView->getTopK(), images.size());
	int rows = ceil((float)knums / (float)COLUMN_MAX);

	m_table->clear();
	m_table->setColumnCount(COLUMN_MAX);
	m_table->setRowCount(rows);

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < COLUMN_MAX; i++) {
			if ((j * COLUMN_MAX + i) >= images.size()) {
				return;
			}

			RetrievalCanvas::RetrievalShowItem * c = new RetrievalCanvas::RetrievalShowItem;
			c->loadPixmap(images[j * COLUMN_MAX + i]);
			SINGLE_SLOT_CONNECT(c, mouseDoubleClicked(const QString &), this, onCanvasDoubleClicked(const QString &));
			m_table->setCellWidget(j, i, c);
		}
	}
}

void RetrievalTest::updateImageList(const QStringList &images)
{
	if (images.size() <= 0) {
		return;
	}

	ui->m_listWidget->clear();
	for (int i = 0; i < images.size(); ++i) {
		ui->m_listWidget->addItem(images.at(i));
	}
}


void RetrievalTest::onCanvasDoubleClicked(const QString &filename)
{
	//qDebug() << "RetrievalTest::onCanvasDoubleClicked" << filename;
	m_canvas->loadPixmap(filename);

	if (m_canvas->getPixmap()) {
		m_canvas->setScale(scaleFitWindow());
		m_canvas->repaint();
	}	

}

void RetrievalTest::onItemDoubleClicked(QListWidgetItem *item)
{
	m_canvas->loadPixmap(item->text());
}

void RetrievalTest::onStartRetrieval()
{
	qDebug() << "RetrievalTest::onStartRetrieval";
	//LMDBGenerator *g = new LMDBGenerator();
	//g->show();

	//ui->m_textBrowser->setText("");

	Configure config;
	if (!m_configView->getImageLib().isEmpty()) {
		config.datasetDir = m_configView->getImageLib();
	}

	if (!m_configView->getBinFeaturePath().isEmpty()) {
		config.binaryFile = m_configView->getBinFeaturePath();
	}

	if (!m_configView->getRawFeaturePath().isEmpty()) {
		config.featTrainFile = m_configView->getRawFeaturePath();
	}

	QString targetPath;
	if (ui->m_comboBox->currentIndex() == 0) {
		targetPath = ui->m_edtImagePath->text();
	}
	else if (ui->m_comboBox->currentIndex() == 1) {
		targetPath = urlTestImgPath();
	}
	else {
		return;
	}

	QFileInfo fileinfo(targetPath);
	if (!fileinfo.exists()) {
		return;
	}

	QStringList res = retrievalImages("E:/GitHub/cvprw15-win/py",
		"retrieve_images", config,
		fileinfo.absoluteFilePath(), m_configView->getTopK());

	updateRetrievalShow(res);
	updateImageList(res);
}

QString RetrievalTest::urlTestImgPath()
{
	QString path = QCoreApplication::applicationDirPath();
	path = QDir::toNativeSeparators(path + QDir::separator() + "tmp" + QDir::separator() + "retrieval_test.jpg");
	return path;
}

void RetrievalTest::clearProgress()
{
	ui->m_progressBar->setMaximum(100);
	ui->m_progressBar->setValue(0);
}

