#include "FileSystemModel.h"
#include <QDebug>
#include <QFileIconProvider>
#include <QPainter>

#ifdef Q_OS_WIN32
#include <qt_windows.h>
#endif

IconProvider::IconProvider()
{
    m_folder = QIcon("F:/workspace/Clementine/data/icons/22x22/folder.png");
    m_hd = QIcon("F:/workspace/Clementine/data/icons/22x22/drive-removable-media-usb-pendrive.png");
    m_default = QIcon("F:/workspace/Clementine/data/icons/22x22/document-new.png");
}

IconProvider::~IconProvider()
{
}

QIcon IconProvider::icon( IconType type ) const
{
    return QFileIconProvider::icon(type);
}

QIcon IconProvider::makeHiddenIcon(const QIcon &icon)
{
    QIcon resIcon;
    if (!icon.isNull()) {
        QList<QSize> sizeList = icon.availableSizes(QIcon::Normal, QIcon::On);
        foreach (const QSize& size, sizeList) {
            QPixmap pixmap = icon.pixmap(size, QIcon::Normal, QIcon::On);

            QPixmap temp(pixmap.size());
            temp.fill(Qt::transparent);

            QPainter p1(&temp);
            p1.setCompositionMode(QPainter::CompositionMode_Source);
            p1.drawPixmap(0, 0, pixmap);
            p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p1.fillRect(temp.rect(), QColor(0, 0, 0, 100));
            p1.end();
            pixmap = temp;

            resIcon.addPixmap(pixmap, QIcon::Normal, QIcon::On);
        }
    }

    return resIcon;
}

QIcon IconProvider::icon( IconType type, bool hidden)
{
    QIcon icon = QFileIconProvider::icon(type);
    if(hidden){
        icon = makeHiddenIcon(icon);
    }

    return icon;
}

QIcon IconProvider::icon( const QFileInfo & info, bool hidden)
{
    QIcon icon = QFileIconProvider::icon(info);
    if(hidden){
        icon = makeHiddenIcon(icon);
    }

    return icon;
}

QIcon IconProvider::icon( const QFileInfo & info) const
{
    //if(info.isDir()) return m_folder;
    //if(info.isRoot()) return m_hd;
    return QFileIconProvider::icon(info);
}

QString IconProvider::type ( const QFileInfo & info ) const
{
    return QFileIconProvider::type(info);
}


FileSystemModel::FileSystemModel(QObject *parent)
    :QFileSystemModel(parent)
{

}

FileSystemModel::~FileSystemModel()
{

}


QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole){
        QFileInfo fileinfo(this->filePath(index));
        if(fileinfo.isHidden()){
            return static_cast<IconProvider*>(this->iconProvider())->icon(fileinfo, true);
        }
    }
    return QFileSystemModel::data(index, role);
}

bool FileSystemModel::setCutIconData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != FileCutRole){
        return QFileSystemModel::setData(index, value, role);
    }

    m_cutIcons[index] =value.value<QIcon>();
    return true;
}

void FileSystemModel::clearCutIcons()
{
    m_cutIcons.clear();
}

void FileSystemModel::unHidden(const QString &filename)
{
    QFileInfo fileInfo(filename);
    if(!fileInfo.exists()){
        return;
    }

#ifdef Q_OS_WIN32
    wchar_t* fileLPCWSTR = (wchar_t*)filename.utf16();

    int attr = GetFileAttributes(fileLPCWSTR);
    SetFileAttributes(fileLPCWSTR, attr & ~FILE_ATTRIBUTE_HIDDEN);

#else
    //platform dependent
#endif
}


void FileSystemModel::setHidden(const QString &filename)
{
    QFileInfo fileInfo(filename);
    if(!fileInfo.exists()){
        return;
    }

#ifdef Q_OS_WIN32
    wchar_t* fileLPCWSTR = (wchar_t*)filename.utf16();

    int attr = GetFileAttributes(fileLPCWSTR);
    if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
        SetFileAttributes(fileLPCWSTR, attr | FILE_ATTRIBUTE_HIDDEN);
    }
#else
    //platform dependent
#endif
}
