#ifndef RETRIEVALTEST_H
#define RETRIEVALTEST_H

#include <QWidget>
#include <QThread>
#include "CPythonHelper.h"

class RetrievalConfig;
class SimpleCanvas;
class Downloader;
class Canvas;
class QScrollArea;
class ShrinkImageView;
class QListWidgetItem;

namespace Ui {
class RetrievalTest;
}

struct Configure {
	QString rootDir = "E:/GitHub/cvprw15-win/";
	QString datasetDir = "E:/GitHub/dataset/caltech256/";
	QString modelFile = rootDir + "examples/Caltech256/model_all_in_train_v2.0/KevinNet_CALTECH256_48_iter_50000.caffemodel";
	QString modelDefFile = rootDir + "examples/Caltech256/KevinNet_CALTECH256_48_deploy.prototxt";
	QString imgTrainList = rootDir + "examples/Caltech256/model_all_in_train_v2.0/train-file-list.txt";
	QString binaryFile = QString("%1%2/binary-train.mat").arg(rootDir).arg("analysis/caltech256");
	QString featTrainFile = QString("%1%2/feat-train.mat").arg(rootDir).arg("analysis/caltech256");
};

class RetrievalTest : public QWidget
{
    Q_OBJECT
	enum RetrievalMode{
		PATH_MODE, URL_MODE
	};


public:
    explicit RetrievalTest(QWidget *parent = 0);
    ~RetrievalTest();

	Configure config() const;
	QStringList retrievalImages(const QString &modulePath,
		const QString &moduleName,
		const Configure &config,
		const QString &targetImagePath,
		unsigned int topK = 10);
	void closeEvent(QCloseEvent *ev);

public slots:
	void onBtnConfig();
	void selectImageDir();
	void showOriginalImage();
	void checkDownloadFinished();
	void onDownloadComplete(bool);
	void progressChanged(qint64, qint64);
	void onCanvasDoubleClicked(const QString &filename);
	void onItemDoubleClicked(QListWidgetItem *item);
	void onStartRetrieval();
	void zoomRequest(int delta);
	void onUpdateInfo(const QString &info);
	

private:
	QString urlTestImgPath();
	void clearProgress();
	qreal scaleFitWindow();
	void updateRetrievalShow(const QStringList &images);
	void updateImageList(const QStringList &images);

private:
    Ui::RetrievalTest *ui;
	ShrinkImageView * m_table;
	RetrievalConfig *m_configView;
	Configure m_config;

	Downloader *m_downloader;
	SimpleCanvas *m_canvas;
	QScrollArea *m_scroll;

	pystd::StdoutWritePointer m_writer;
	const int COLUMN_MAX = 5;
};

#endif // RETRIEVALTEST_H
