#include "FileHelper.h"
#include "ui_FileHelper.h"
#include "FileBrowser.h"
#include <QDateTime>
#include <QMap>
#include <QDir>
#include <QResizeEvent>
#include <QFileInfo>
#include <QDebug>

const unsigned int FileHelper::maxFileViews = 5;
const unsigned int FileHelper::minFileViews = 1;

FileHelper::FileHelper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileHelper),
    m_thread(NULL)
{
    ui->setupUi(this);
//    widget = new FileList();
//    ui->m_splitter->addWidget(widget);

    addNewFileView();
}

FileHelper::~FileHelper()
{
    delete ui;
}

void FileHelper::closeEvent(QCloseEvent *ev)
{
	QWidget::closeEvent(ev);
}

void FileHelper::signalSlotConnect(FileBrowser *win)
{
    connect(win, SIGNAL(newFileView()), this, SLOT(addNewFileView()));
    connect(win, SIGNAL(deleteFileView(qint64)), this, SLOT(deleteFileView(qint64)));
}

void FileHelper::addNewFileView()
{
    if(m_views.size() >= maxFileViews){
        return;
    }

    qint64 id = QDateTime::currentMSecsSinceEpoch();
    FileBrowser *widget = new FileBrowser(id, ui->m_splitter);
    //widget->setPath(QDir::homePath());
    connect(widget, SIGNAL(updateFileInfo(const QFileInfo&, const QIcon &)), this, SLOT(onUpdateFileInfo(const QFileInfo&, const QIcon &)));
    ui->m_splitter->addWidget(widget);

    signalSlotConnect(widget);

    m_views[id] = widget;
}

void FileHelper::deleteFileView(qint64 wid)
{
    if(m_views.size() <= minFileViews){
        return;
    }

    FileBrowser *win = m_views[wid];
    QSize size = win->size();
    if(win != NULL){
        delete win;
    }

    m_views.remove(wid);
}

void FileHelper::caculateFolderSize(const QFileInfo &fileInfo)
{

    qint64 id = QDateTime::currentMSecsSinceEpoch();
    QStringList dirs;
    dirs << fileInfo.absoluteFilePath();
    if(m_thread){
        m_thread->quit();
        m_thread->wait();
    }

    m_thread = new MarkedThread(id, dirs);
    connect(m_thread, SIGNAL(threadFinished(qint64)), this, SLOT(onThreadFinished(qint64)));
    m_thread->start();
}

void FileHelper::onThreadFinished(qint64 /*id*/)
{
    qDebug() << "onCopyThreadFinished";
    if(m_thread){
        qint64 size = m_thread->m_totalSize;
        QString sizeInfo = sizeFormat2String(size);
        ui->m_size->setText(sizeInfo);
        delete m_thread;
        m_thread = NULL;
    }
}

QString FileHelper::sizeFormat2String(qint64 fileSize)
{
    QString sizeInfo;
    if(fileSize / 1024  == 0){
        sizeInfo = QString::number(fileSize) + " Bytes";
    }
    else if(fileSize / (1024*1024)  == 0){
        sizeInfo = QString::number(fileSize / 1024) + " K";
    }
    else if(fileSize / (1024*1024*1024)  == 0){
        sizeInfo = QString::number(fileSize / (1024*1024)) + " M";
    }
    else{
        sizeInfo = QString::number(fileSize / (1024*1024*1024)) + " G";
    }

    return sizeInfo;
}

void FileHelper::onUpdateFileInfo(const QFileInfo& fileInfo, const QIcon &icon)
{
    ui->m_name->setText(fileInfo.fileName());
    QString sizeInfo;
    if(fileInfo.isDir()){
        sizeInfo = "0";
        //caculateFolderSize(fileInfo);
    }
    else{
        qint64 fileSize = fileInfo.size();
        sizeInfo = sizeFormat2String(fileSize);
    }

    ui->m_size->setText(sizeInfo);
    ui->m_modTime->setText(fileInfo.lastModified().toLocalTime().toString("hh:mm yyyy.MM.dd"));

    ui->m_imageLabel->drawIcon(icon);
}
