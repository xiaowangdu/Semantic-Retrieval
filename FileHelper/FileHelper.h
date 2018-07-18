#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QWidget>
#include <QMap>

namespace Ui {
class FileHelper;
}

class FileBrowser;
class QFileInfo;
class MarkedThread;

class FileHelper : public QWidget
{
    Q_OBJECT

public:
    explicit FileHelper(QWidget *parent = 0);
    ~FileHelper();
	void closeEvent(QCloseEvent *ev);


public slots:
    void addNewFileView();
    void deleteFileView(qint64 wid);
    void onUpdateFileInfo(const QFileInfo& fileInfo, const QIcon &icon);
    void onThreadFinished(qint64 id);

private:
    void signalSlotConnect(FileBrowser *win);
    void caculateFolderSize(const QFileInfo &fileInfo);
    QString sizeFormat2String(qint64 fileSize);

private:
    Ui::FileHelper *ui;
    QMap<qint64, FileBrowser *> m_views;

    MarkedThread *m_thread;

    static const unsigned int maxFileViews;
    static const unsigned int minFileViews;
};

#endif // FILEHELPER_H
