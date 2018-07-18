#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QFileIconProvider>

class IconProvider : public QFileIconProvider
{
public:
    IconProvider();
    ~IconProvider();

    //enum IconType { Computer, Desktop, Trashcan, Network, Drive, Folder, File };

    QIcon icon( IconType type, bool hidden = false);
    QIcon icon( IconType type ) const;
    QIcon icon( const QFileInfo & info, bool hidden = false);
    QIcon icon( const QFileInfo & info ) const;
    QString type( const QFileInfo & info ) const;

private:
    QIcon makeHiddenIcon(const QIcon &icon);

private:
    QIcon m_folder;
    QIcon m_hd;
    QIcon m_default;
};

class FileSystemModel : public QFileSystemModel
{
public:
    enum Roles {
        FileCutRole = QFileSystemModel::FilePermissions + 1,

    };

    FileSystemModel(QObject *parent = 0);
    ~FileSystemModel();

    bool setCutIconData(const QModelIndex &idx, const QVariant &value, int role = FileCutRole);
    void clearCutIcons();

    static void setHidden(const QString &filename);
    static void unHidden(const QString &filename);

protected:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;


private:
    QMap<QModelIndex, QIcon> m_cutIcons;
};

#endif // FILESYSTEMMODEL_H
