#ifndef FILEVIEWLIST_H
#define FILEVIEWLIST_H

#include <QListView>
#include <QUrl>
#include <QMimeData>
#include <QMessageBox>
#include "Thread.h"

#ifdef Q_OS_WIN32
#include <qt_windows.h>
#endif

class CopyWithWatcher;
class ProgressBar;
class MarkedThread;


class FileList : public QListView {
    Q_OBJECT
public:
    enum CopyOperationMode{
        UNKNOWN, SKIP, OVERWRITE
    };

    FileList(QWidget* parent = nullptr);

    CopyOperationMode copyMode()const;
    void setCopyMode(CopyOperationMode mode);
    static QString preferredDropEffectMimeType();

signals:
    void updateFileInfo(const QFileInfo& fileInfo, const QIcon &icon);


protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent* e);

    void dragMoveEvent(QDragMoveEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);

private:
    void watchClipboard();

    void performDrag();
    bool hasValidUrls();
    bool hasValidUrls(const QMimeData* mimeData);
    bool isCutNow();

    QByteArray int2ByteArray(DWORD exp);
    void copyFileToClipboard(const QStringList &paths);
    void copyFileToClipboard(const QList<QUrl> &urls);
    void cutFileToClipboard(const QStringList &paths);
    void cutFileToClipboard(const QList<QUrl> &urls);
    QStringList pathListFromClipboard();

    QItemSelection itemSelected()const;
    bool targetDirIsSubDir(const QString &src, const QString &target);
    QString makeNewName(const QString &src, const QString &destPath, const HandlePairs &previousNewNames);
    int miniMessageBox(QMessageBox::Icon type, QWidget *parent, const QString &title,
                   const QString& text,
                   QFlags<QMessageBox::StandardButton> buttons, int &state);

    HandlePairs makeCopyPairs(const QStringList &paths, const QString &target);
    void doCopyTask(const QStringList &paths, const QString &target);
    void doCutTask(const QStringList &paths, const QString &target);

private slots:
    void onCopyAction();
    void onCutAction();
    void onPasteAction();
    void onDeleteAction();
    void showInBrowser();
    void onScanFinished(qint64, qint64, QStringList);
    void updateBar(qint64 id, qint64 bytesProcessed, qint64 bytesTotal);
    void onCopyThreadFinished(qint64 id);
    void sizeHint(qint64 id, qint64 tempFileSize);
    void onDeleteProgress(qint64 id, const QString &currrentFileName, qint64 bytesLeave, qint64 totalBytes);
    void onItemClicked(const QModelIndex &index);

    QStringList pathsFromSelection() const;
    QList<QUrl> urlListFromSelection() const;
    void clearClipboard();


private:
    QPoint m_startPos;
    QMenu* m_menu;

    CopyOperationMode m_copyMode = UNKNOWN;
    QAction *m_copy;
    QAction *m_cut;
    QAction *m_paste;
    QAction *m_delete;

    CopyWithWatcher *m_copyWatcher;

    QMap<qint64, MarkedThread *>m_idToThread;
    QMap<qint64, ProgressBar*>m_idToBar;

};

#endif  // FILEVIEWLIST_H
