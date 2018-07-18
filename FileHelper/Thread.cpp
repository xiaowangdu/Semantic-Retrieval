#include "Thread.h"
#include "CopyWithWatcher.h"
#include <QApplication>
#include <QMimeData>
#include <QDebug>

PasteThread::PasteThread(qint64 id, HandlePairs &handlePairs, bool overwrite)
    :m_handlePairs(handlePairs), m_overwriteState(overwrite),
     MarkedThread(id)
{

}

void PasteThread::sendProcessProgressChangeMsg(qint64 bytesProcessed, qint64 /*bytesTotal*/)
{
    emit processProgress(m_id, m_fileSizeAlreadyDone + bytesProcessed, m_totalSize);
}


void PasteThread::main()
{
    QStringList duplicateMapInfo = scanFiles(m_handlePairs);

    m_fileSizeAlreadyDone = 0;
    CopyWithWatcher copyWatcher;
    connect(&copyWatcher, SIGNAL(copyProgress(qint64, qint64)), this, SLOT(sendProcessProgressChangeMsg(qint64, qint64)));
    foreach (const QString &mapInfo, duplicateMapInfo) {
        QStringList s = mapInfo.split('|');
        QString srcFile = s[0];
        QString dstFile = s[1];

        if(copyWatcher.copy(srcFile, dstFile, m_overwriteState)){
            //qDebug() << m_fileSizeAlreadyDone;
            m_fileSizeAlreadyDone += QFileInfo(srcFile).size();
        }
    }


}


CutPasteThread::CutPasteThread(qint64 id, HandlePairs &handlePairs, const QList<QUrl>& clipboardUrls, bool overwrite)
    :PasteThread(id, handlePairs, overwrite), m_handlePairs(handlePairs), m_globalClipboardChanged(false), m_currentClipboardUrls(clipboardUrls),m_overwriteState(overwrite)
{

}

void CutPasteThread::onGlobalClipboardChange(QClipboard::Mode mode)
{
    if(mode == QClipboard::Clipboard){
        QClipboard *cb = QApplication::clipboard();

        const QMimeData* mimeData = cb->mimeData();
        if(mimeData->urls() != m_currentClipboardUrls){
            m_globalClipboardChanged = true;
        }
    }
}

void CutPasteThread::deleteDir(const HandlePairs &pairs)
{

    foreach (const HandlePair &pair, pairs) {
        QDir d(pair.first);
        if(d.exists()){
            d.removeRecursively();
        }
    }
}

void CutPasteThread::main()
{
    qDebug() << "--------->" << m_handlePairs.size();
    QStringList duplicateMapInfo = scanFiles(m_handlePairs);

    m_fileSizeAlreadyDone = 0;
    CopyWithWatcher copyWatcher;
    connect(&copyWatcher, SIGNAL(copyProgress(qint64, qint64)), this, SLOT(sendProcessProgressChangeMsg(qint64, qint64)));
    foreach (const QString &mapInfo, duplicateMapInfo) {
        QStringList s = mapInfo.split('|');
        QString srcFile = s[0];
        QString dstFile = s[1];
        qDebug() << mapInfo;

        if(copyWatcher.copy(srcFile, dstFile, m_overwriteState)){
            QFile file(srcFile);
            if(!file.remove()){
                file.setPermissions(QFile::ReadOther | QFile::WriteOther);
                if(!file.remove()) continue;
            }
            //qDebug() << m_fileSizeAlreadyDone;
            m_fileSizeAlreadyDone += QFileInfo(srcFile).size();
        }
    }

    deleteDir(m_handlePairs);

    if(!m_globalClipboardChanged){
        emit requestClearClipboard();
    }
}

DeleteThread::DeleteThread(qint64 id, const QStringList &files)
    :m_filesDel(files),
     MarkedThread(id)
{

}

void DeleteThread::deleteDir(const QStringList &dirs)
{
    foreach (const QString &dir, dirs) {
        QDir d(dir);
        if(d.exists()){
            d.removeRecursively();
        }
    }
}

void DeleteThread::main()
{
    if(m_filesDel.isEmpty()){
        return;
    }

    HandlePairs handlePairs;
    foreach (const QString &file, m_filesDel) {
        HandlePair handlePair(file, "");
        handlePairs.append(handlePair);
    }

    QStringList duplicateMapInfo = scanFiles(handlePairs);

    m_fileSizeAlreadyDone = 0;
    if(duplicateMapInfo.isEmpty()){
        //no files under the dir, delete dir.
        goto Label_goto;
    }

    foreach (const QString &mapInfo, duplicateMapInfo) {
        QStringList s = mapInfo.split('|');
        QString delFile = s[0];

        QFile file(delFile);
        emit deleteProgress(m_id, file.fileName(), m_totalSize - m_fileSizeAlreadyDone, m_totalSize);

        if(!file.remove()){
            file.setPermissions(QFile::ReadOther | QFile::WriteOther);
            if(!file.remove()) continue;
        }
        m_fileSizeAlreadyDone += file.size();
    }

Label_goto:
    deleteDir(m_filesDel);
}
