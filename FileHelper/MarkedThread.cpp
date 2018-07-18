#include "MarkedThread.h"
#include <QDebug>

MarkedThread::MarkedThread(qint64 id)
    :m_id(id), m_totalSize(0), m_fileSizeTemp(0)
{
    connect(this, SIGNAL(finished()), this, SLOT(onThreadFinished()));
}

MarkedThread::MarkedThread(qint64 id, const QStringList &dirs)
    :m_id(id), m_directorys(dirs), m_totalSize(0), m_fileSizeTemp(0)
{
    connect(this, SIGNAL(finished()), this, SLOT(onThreadFinished()));
}

MarkedThread::~MarkedThread()
{
}

void MarkedThread::onThreadFinished()
{
    emit threadFinished(m_id);
}


QStringList MarkedThread::listFiles(const QString &sourceFolder, const QString & copyToFolder)
{
    QStringList mapInfoList;
    std::function<bool(const QString&, const QString&)> folderContents;
    folderContents = [&](const QString &sourceFolder, const QString &destFolder)->bool {
        QDir sourceDir(sourceFolder);

        if (!sourceDir.exists())
            return false;

        QFileInfoList fileInfoList = sourceDir.entryInfoList(QDir::NoDotAndDotDot | QDir::NoSymLinks
                                                             | QDir::Dirs | QDir::Files);
        foreach (const QFileInfo &fileInfo, fileInfoList) {
            QString srcFilePath = fileInfo.filePath();
            QString dstFilePath = destFolder.isEmpty() ? fileInfo.fileName() : destFolder + QDir::separator() + fileInfo.fileName();
            if (fileInfo.isDir()) {
                if (!folderContents(srcFilePath, dstFilePath))
                    return false;
            } else {
                m_totalSize += fileInfo.size();
                if(m_totalSize - m_fileSizeTemp >= SIZEHINTSTEP) {
                    emit fileSizeFlush(m_id, m_totalSize);
                    m_fileSizeTemp = m_totalSize;
                }

                QString destPath = copyToFolder+QDir::separator()+dstFilePath;
                if(copyToFolder.isEmpty()){
                    destPath = "";
                }
                QString mapInfo = QString("%1|%2").arg(fileInfo.canonicalFilePath()).arg(destPath);
                mapInfoList.append(mapInfo);

            }
        }

        return true;
    };

    if (folderContents(sourceFolder, QString())){
        return mapInfoList;
    }
    else{
        return QStringList();
    }
}

//scan files and caculate total size.
QStringList MarkedThread::scanFiles(const HandlePairs &handlePairs)
{
    qDebug() << "MarkedThread::scanFiles" << handlePairs.size();
    QStringList duplicateMapInfo;
    if(handlePairs.size() <= 0){
        return QStringList();
    }

    m_totalSize = m_fileSizeTemp = 0;
    for(int i = 0; i < handlePairs.size(); ++i){
        QString destDir = QDir::fromNativeSeparators(handlePairs[i].second);

        QString path = QDir::fromNativeSeparators(handlePairs[i].first);
        QFileInfo fileinfo(path);
        if(fileinfo.isFile()){
            m_totalSize += fileinfo.size();
            if(m_totalSize - m_fileSizeTemp >= SIZEHINTSTEP) {
                emit fileSizeFlush(m_id, m_totalSize);
                m_fileSizeTemp = m_totalSize;
            }

            QString destFilePath = destDir;
            if(destDir.isEmpty()){
                destFilePath = "";
            }
            duplicateMapInfo += QString("%1|%2").arg(fileinfo.canonicalFilePath()).arg(destFilePath);
        }
        else {
            duplicateMapInfo += listFiles(path, destDir);
        }
    }

    if(!duplicateMapInfo.isEmpty())
        emit scanFinished(m_id, m_totalSize, duplicateMapInfo);

    return duplicateMapInfo;
}

void MarkedThread::scanFiles()
{
    if(m_directorys.isEmpty()){
        return;
    }

    HandlePairs handlePairs;
    foreach (const QString &dir, m_directorys) {
        HandlePair handlePair(dir, "");
        handlePairs.append(handlePair);
    }

    scanFiles(handlePairs);
}

void MarkedThread::main()
{
    scanFiles();
}

// auto run task expected by subclass.
void MarkedThread::run()
{
    main();
}
