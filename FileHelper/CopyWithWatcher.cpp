#include "CopyWithWatcher.h"

#include <QDir>
#include <QFile>

CopyWithWatcher::CopyWithWatcher(QObject *parent)
    : QObject(parent)
{

}



bool CopyWithWatcher::copy(const QString &sourceFile, const QString &destFile, bool overwrite)
{
    if(sourceFile == destFile && !overwrite)

    if (!QFile::exists(sourceFile)) {
        qWarning("File copy: Empty or null file name");
        return false;
    }

    QFileInfo dst(destFile);
    if (dst.isFile() && dst.exists()) {
        if(overwrite == false){
            return true;
        }
        else{
            QFile::setPermissions(destFile, QFile::ReadOther | QFile::WriteOther);
            QFile::remove(destFile);
        }
    }

    if(dst.isDir()){
        qCritical("Exist a folder, its name same as the destination file");
        return false;
    }

    QDir dir = dst.dir();
    if (!dir.exists())
        dir.mkpath(dir.path());

    QFile srcFile(sourceFile);
    if (!srcFile.open(QIODevice::ReadOnly)){
        qWarning("File copy open: Source file open failed");
        return false;
    }

    QFile dstFile(destFile);
    if (!dstFile.open(QIODevice::WriteOnly)){
        qWarning("File copy open: Destination file open failed");
        srcFile.close();
        return false;
    }

    char block[512*1024];
    qint64 totalRead = 0;
    emit copyProgress(totalRead, srcFile.size());
    while (!srcFile.atEnd()) {
        qint64 in = srcFile.read(block, sizeof(block));
        if (in <= 0)
            break;
        totalRead += in;
        if (in != dstFile.write(block, in)) {
            dstFile.close();
            srcFile.close();
            qCritical("Failure to write block");
            return false;
        }
        emit copyProgress(totalRead, srcFile.size());
    }
    if (totalRead != srcFile.size()) {
        dstFile.close();
        srcFile.close();
        qCritical("Copy file length not match");
        return false;
    }

    QFile::setPermissions(destFile, srcFile.permissions());

    dstFile.close();
    srcFile.close();
    return true;
}
