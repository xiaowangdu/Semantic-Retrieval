#include "FileList.h"
#include "commonfunctions.h"
#include "../Common/iconloader.h"
#include <QContextMenuEvent>
#include <QFileSystemModel>
#include <QMenu>
#include <QDrag>
#include <QClipboard>
#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <QLayout>
#include <QDateTime>
#include <QProgressDialog>
#include <QMessageBox>
#include "ProgressBar.h"
#include "CopyWithWatcher.h"
#include "QMessageBoxComponent.h"
#include "FileSystemModel.h"


#define ICON(IconName) QIcon(QPixmap(QString("F:/workspace/Clementine/data/icons/48x48/%1.png").arg(IconName)))



FileList::FileList(QWidget* parent)
    : QListView(parent), m_menu(new QMenu(this)), m_copyWatcher(new CopyWithWatcher)
{

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    m_copy = m_menu->addAction(IconLoader::load("edit-copy", IconLoader::Base),
                   tr("Copy"), this,
                   SLOT(onCopyAction()));
    m_cut = m_menu->addAction(IconLoader::load("edit-cut", IconLoader::Base),
                   tr("Cut"), this, SLOT(onCutAction()));
    m_paste = m_menu->addAction(IconLoader::load("edit-paste", IconLoader::Base),
                   tr("Paste"), this,
                   SLOT(onPasteAction()));
    m_menu->addSeparator();

    m_delete = m_menu->addAction(ICON("edit-delete"),
                   tr("Delete"), this, SLOT(onDeleteAction()));

    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onItemClicked(const QModelIndex &)));
}

void FileList::contextMenuEvent(QContextMenuEvent* e)
{
    if(itemSelected().isEmpty()){
        m_copy->setEnabled(false);
        m_cut->setEnabled(false);
        m_delete->setEnabled(false);

        m_paste->setEnabled(hasValidUrls());
    }
    else{
        m_copy->setEnabled(true);
        m_cut->setEnabled(true);
        m_paste->setEnabled(false);
        m_delete->setEnabled(true);
    }

    m_menu->popup(e->globalPos());
    e->accept();
}

bool FileList::hasValidUrls()
{
    const QMimeData* mimeData = QApplication::clipboard()->mimeData();
    return hasValidUrls(mimeData);
}

bool FileList::hasValidUrls(const QMimeData* mimeData)
{
    for ( const QString &format : mimeData->formats()){
        if(format == "text/uri-list"){
            return !mimeData->data(format).isEmpty();
        }
    }

    return false;
}

bool FileList::isCutNow()
{
    const QMimeData* mimeData = QApplication::clipboard()->mimeData();
    for ( const QString &format : mimeData->formats()){

        if(format == QStringLiteral("application/x-qt-windows-mime;value=\"Preferred DropEffect\"")){
           // qDebug() << format << *((DWORD *)(mimeData->data(format).constData()));
            return *((DWORD *)(mimeData->data(format).constData())) & DROPEFFECT_MOVE;
        }
    }

    return false;
}

void FileList::onCopyAction()
{
    qDebug() << "onCopyAction";
    QStringList paths = pathsFromSelection();
    qDebug() << paths;
    copyFileToClipboard(paths);
}

QByteArray FileList::int2ByteArray(DWORD exp)
{
    QByteArray byteArray;
    for(int i = 0; i != sizeof(exp); ++i) {
        byteArray.append((char)((exp & (0xFF << (i*8))) >> (i*8)));
    }

    return byteArray;
}

void FileList::copyFileToClipboard(const QStringList &paths)
{
    QList<QUrl> urls;
    for (QString path : paths) {
        if (!path.isEmpty()){
            urls << QUrl::fromLocalFile(QFileInfo(path).canonicalFilePath());
        }
    }

    copyFileToClipboard(urls);
}

void FileList::copyFileToClipboard(const QList<QUrl> &urls)
{
    QClipboard *cb = QApplication::clipboard();

    // if needed, copy mimedata already exist on clipboard rather than clear.
    QMimeData* newMimeData = new QMimeData();

    // copy old mimedata
    const QMimeData* oldMimeData = cb->mimeData();
    newMimeData->setData(preferredDropEffectMimeType(), int2ByteArray(DROPEFFECT_COPY));
    for ( const QString &format : oldMimeData->formats()){
        if(format == preferredDropEffectMimeType()){
            DWORD old = *((DWORD *)(oldMimeData->data(format).constData()));
            old = (old | *((DWORD *)(newMimeData->data(format).constData())));
            newMimeData->setData(format,  int2ByteArray(old & ~DROPEFFECT_MOVE));
        }
        else{
            newMimeData->setData(format, oldMimeData->data(format));
        }
    }

    newMimeData->setUrls(urls);
    cb->setMimeData(newMimeData);
}

void FileList::cutFileToClipboard(const QStringList &paths)
{
    QList<QUrl> urls;
    for (QString path : paths) {
        if (!path.isEmpty()){
            urls << QUrl::fromLocalFile(QFileInfo(path).canonicalFilePath());
        }
    }

    cutFileToClipboard(urls);
}

void FileList::cutFileToClipboard(const QList<QUrl> &urls)
{
    QClipboard *cb = QApplication::clipboard();

    // if needed, copy mimedata already exist on clipboard rather than clear.
    QMimeData* newMimeData = new QMimeData();

    // copy old mimedata
    const QMimeData* oldMimeData = cb->mimeData();
    newMimeData->setData(preferredDropEffectMimeType(), int2ByteArray(DROPEFFECT_MOVE));
    for ( const QString &format : oldMimeData->formats()){
        if(format == preferredDropEffectMimeType()){
            DWORD old = *((DWORD *)(oldMimeData->data(format).constData()));
            old = (old | *((DWORD *)(newMimeData->data(format).constData())));
            newMimeData->setData(format,  int2ByteArray(old & ~DROPEFFECT_COPY));
        }
        else{
            newMimeData->setData(format, oldMimeData->data(format));
        }
    }

    newMimeData->setUrls(urls);
    cb->setMimeData(newMimeData);
}

FileList::CopyOperationMode FileList::copyMode()const
{
    return m_copyMode;
}

void FileList::setCopyMode(CopyOperationMode mode)
{
    m_copyMode = mode;
}

QString FileList::preferredDropEffectMimeType()
{
    return QStringLiteral("application/x-qt-windows-mime;value=\"Preferred DropEffect\"");
}

int FileList::miniMessageBox(QMessageBox::Icon type, QWidget *parent, const QString &title,
               const QString& text,
               QFlags<QMessageBox::StandardButton> buttons, int &state)
{
    QMessageBox w(parent);
    w.setIcon(type);
    w.setWindowTitle(title);

    QMessageBoxComponent *com = new QMessageBoxComponent();
    com->setContent(text);
    w.layout()->replaceWidget(w.layout()->itemAt(2)->widget(), com);

    w.setStandardButtons(buttons);

    int res = w.exec();
    state = UNKNOWN;
    if(com->skip()){
        state = SKIP;
    }
    else if(com->overwrite()){
        state = OVERWRITE;
    }

    return res;
}

QStringList FileList::pathListFromClipboard()
{
    QStringList paths;
    const QMimeData* mimeData = QApplication::clipboard()->mimeData();
    if(hasValidUrls(mimeData)){
        QList<QUrl> list = mimeData->urls();
        foreach(const QUrl &url, list){
            //TODO: QUrl return path '/E:/', it is not expected.
            QString path = url.path();
            paths << QDir(path.right(path.size()-1)).absolutePath();
            //qDebug() << url.path(QUrl::EncodeReserved);
        }
    }

    return paths;
}

QItemSelection FileList::itemSelected()const
{
    return selectionModel()->selection();
}


void FileList::onCutAction()
{
    //onCutAction();
    QStringList paths = pathsFromSelection();
    qDebug() << paths;
    cutFileToClipboard(paths);

}

bool FileList::targetDirIsSubDir(const QString &src, const QString &target)
{
    if(src.isEmpty() || target.isEmpty()) return false;

    QStringList srcPathNodes = src.split('/');
    QStringList targetPathNodes = target.split('/');
    if(targetPathNodes.size() >= srcPathNodes.size()){
        for(int i = 0; i < srcPathNodes.size(); ++i) {
            if(srcPathNodes[i] != targetPathNodes[i]) return false;
        }
        return true;
    }

    return false;
}

QString FileList::makeNewName(const QString &src, const QString &destPath, const HandlePairs &previousNewNames)
{
    QFileInfo info(src);
    QString name = info.fileName();
    QString path = destPath + QDir::separator() + name;
    while(QFileInfo::exists(path)){
        name = "(Copy) - " + name;
        path = destPath + QDir::separator() + name;
    }

    QStringList previousList;
    foreach (const HandlePair &pair, previousNewNames) {
        previousList << pair.second;
    }

    while(previousList.contains(path)){
        name = "(Copy) - " + name;
        path = destPath + QDir::separator() + name;
    }
    return path;
}

//For debug
void FileList::watchClipboard()
{
    QClipboard *cb = QApplication::clipboard();

    const QMimeData* mimeData = cb->mimeData();
    for ( const QString &format : mimeData->formats()){
        qDebug() << "Format:" << format << "c_str:" << mimeData->data(format).toStdString().c_str();
         qDebug() << "Format value:" << *((DWORD *)(mimeData->data(format).constData()));
    }
}

HandlePairs FileList::makeCopyPairs(const QStringList &paths, const QString &target)
{
    HandlePairs copyPairs;
    QString targetPath = target;
    foreach (const QString &path, paths) {
        QString srcPath = QDir::fromNativeSeparators(path);
        if(targetDirIsSubDir(srcPath, targetPath)){
            QString msg = "The targe directory is sub directory.";
            QMessageBox::warning(this, "Attention", msg, QMessageBox::Ok);
            return HandlePairs();
        }

        QFileInfo srcFileInfo(srcPath);
        //Operation at same directory
        if(QDir(srcFileInfo.path()) == QDir(targetPath)){
            //make copy
            HandlePair copyPair(path, makeNewName(srcPath, targetPath, copyPairs));
            copyPairs.append(copyPair);
            continue;
        }

        QString t = QDir::fromNativeSeparators(targetPath + QDir::separator() + srcFileInfo.fileName());
        if(copyMode() == UNKNOWN && QFileInfo::exists(t)){
            int state = UNKNOWN;
            QMessageBox::StandardButton b = (QMessageBox::StandardButton)miniMessageBox(QMessageBox::Warning, this, "Attention", QString("Target file %1 already exist, do you want?").arg(t), QMessageBox::Yes | QMessageBox::Close, state);
            if(b == QMessageBox::Yes){
                setCopyMode((CopyOperationMode)state);
            }
            else{
                return HandlePairs();
            }
        }

        QString toPath = targetPath + QDir::separator() + srcFileInfo.fileName();
        HandlePair copyPair(path, toPath);
        copyPairs.append(copyPair);
    }

    return copyPairs;
}

void FileList::doCopyTask(const QStringList &paths, const QString &target)
{
    if(paths.size() <= 0 || target.isEmpty()){
        return;
    }

    HandlePairs copyPairs = makeCopyPairs(paths, target);
    if(copyPairs.size() <= 0){
        return;
    }

    qint64 id = QDateTime::currentMSecsSinceEpoch();
    ProgressBar *bar = new ProgressBar(id);
    bar->progressBar()->setMaximum(0);
    bar->progressBar()->setMinimum(0);
    bar->show();
    m_idToBar[id] = bar;
    PasteThread *t = new PasteThread(id, copyPairs, copyMode() == OVERWRITE);
    m_idToThread[id] = t;
    connect(t, SIGNAL(scanFinished(qint64, qint64, QStringList)), this, SLOT(onScanFinished(qint64, qint64, QStringList)));
    connect(t, SIGNAL(processProgress(qint64, qint64, qint64)), this, SLOT(updateBar(qint64, qint64, qint64)));
    connect(t, SIGNAL(fileSizeFlush(qint64, qint64)), this, SLOT(sizeHint(qint64, qint64)));
    connect(t, SIGNAL(threadFinished(qint64)), this, SLOT(onCopyThreadFinished(qint64)));
    t->start();

    setCopyMode(UNKNOWN);
}

void FileList::doCutTask(const QStringList &paths, const QString &target)
{
    if(paths.size() <= 0 || target.isEmpty()){
        return;
    }

    //check
    QStringList newPaths;
    foreach (const QString &path, paths) {
        QFileInfo srcInfo(path);
        //Operation at same directory
        if(QDir(srcInfo.path()) != QDir(target)){
            newPaths << path;
        }
    }

    if(newPaths.size() <= 0){
        QApplication::clipboard()->clear();
        return;
    }

    HandlePairs copyPairs = makeCopyPairs(newPaths, target);
    if(copyPairs.size() <= 0){
        return;
    }

    qint64 id = QDateTime::currentMSecsSinceEpoch();
    ProgressBar *bar = new ProgressBar(id);
    bar->progressBar()->setMaximum(0);
    bar->progressBar()->setMinimum(0);
    bar->show();
    m_idToBar[id] = bar;

    QClipboard *cb = QApplication::clipboard();
    const QMimeData* mimeData = cb->mimeData();

    CutPasteThread *t = new CutPasteThread(id, copyPairs, mimeData->urls(), copyMode() == OVERWRITE);
    m_idToThread[id] = t;
    connect(t, SIGNAL(scanFinished(qint64, qint64, QStringList)), this, SLOT(onScanFinished(qint64, qint64, QStringList)));
    connect(t, SIGNAL(processProgress(qint64, qint64, qint64)), this, SLOT(updateBar(qint64, qint64, qint64)));
    connect(t, SIGNAL(fileSizeFlush(qint64, qint64)), this, SLOT(sizeHint(qint64, qint64)));
    connect(t, SIGNAL(threadFinished(qint64)), this, SLOT(onCopyThreadFinished(qint64)));
    connect(QApplication::clipboard(), SIGNAL(changed(QClipboard::Mode)), t, SLOT(onGlobalClipboardChange(QClipboard::Mode)));
    connect(t, SIGNAL(requestClearClipboard()), this, SLOT(clearClipboard()));
    t->start();

    setCopyMode(UNKNOWN);
}

void FileList::onPasteAction()
{

    QStringList paths = pathListFromClipboard();
    //qDebug() << "onPasteAction" << paths;

    if(paths.size() <= 0){
        return;
    }

    QString target = QDir::fromNativeSeparators(static_cast<QFileSystemModel*>(model())->rootPath());
    if(isCutNow()){
        doCutTask(paths, target);
    }
    else{
        doCopyTask(paths, target);
    }

}

void FileList::onScanFinished(qint64 id, qint64 totalsize, QStringList files)
{
    ProgressBar * bar = m_idToBar[id];
    if(bar){
        bar->progressBar()->setRange(0, 9999);
        bar->progressBar()->setValue(0);

        if(files.size()>0)
            qDebug() << files[0];
    }

}

void FileList::updateBar(qint64 id, qint64 bytesProcessed, qint64 bytesTotal)
{
    ProgressBar * bar = m_idToBar[id];
    if(bar){
        qreal val = 10000 * ((qreal)bytesProcessed/(qreal)bytesTotal);
        bar->progressBar()->setValue((int)val);
    }
}

void FileList::onCopyThreadFinished(qint64 id)
{
    ProgressBar * bar = m_idToBar[id];
    if(bar){
        delete bar;
        m_idToBar.remove(id);
        qDebug() << m_idToBar.size();
    }

    MarkedThread * thread = m_idToThread[id];
    if(thread){
        delete thread;
        m_idToThread.remove(id);
        qDebug() << m_idToThread.size();
    }
}

void FileList::sizeHint(qint64 id, qint64 tempFileSize)
{
    ProgressBar * bar = m_idToBar[id];
    if(bar){
        if(bar->progressBar()->maximum() == 0){
            bar->setMessage("Caculate Size...", QString("Target size: %1 bytes").arg(tempFileSize));
        }
        //qDebug() << m_idToBar.size();
    }
}

void FileList::onDeleteProgress(qint64 id, const QString &currrentFileName, qint64 bytesLeave, qint64 totalBytes)
{
    ProgressBar * bar = m_idToBar[id];
    if(bar){

        bar->setMessage("Delete files", QString("Delete file: %1 \nTotal size: %2 \nLeaved size: %3").arg(currrentFileName).arg(totalBytes).arg(bytesLeave));
        //bar->progressBar()->setValue(totalBytes - bytesLeave);
        //qDebug() << m_idToBar.size();
    }
}

void FileList::onItemClicked(const QModelIndex &index)
{
    QString path = static_cast<QFileSystemModel*>(model())->filePath(index);
    QFileInfo fileInfo(path);
    QIcon icon = static_cast<QFileSystemModel*>(model())->fileIcon(index);

    emit updateFileInfo(fileInfo, icon);
}

void FileList::onDeleteAction()
{
    qDebug() << "onDeleteAction";
    QStringList paths = pathsFromSelection();

    qint64 id = QDateTime::currentMSecsSinceEpoch();
    ProgressBar *bar = new ProgressBar(id);
    bar->progressBar()->setMaximum(0);
    bar->progressBar()->setMinimum(0);
    bar->show();
    m_idToBar[id] = bar;
    DeleteThread *t = new DeleteThread(id, paths);
    m_idToThread[id] = t;
    connect(t, SIGNAL(scanFinished(qint64, qint64, QStringList)), this, SLOT(onScanFinished(qint64, qint64, QStringList)));
    connect(t, SIGNAL(fileSizeFlush(qint64, qint64)), this, SLOT(sizeHint(qint64, qint64)));
    connect(t, SIGNAL(deleteProgress(qint64, const QString &, qint64, qint64)), this, SLOT(onDeleteProgress(qint64, const QString &, qint64, qint64)));
    connect(t, SIGNAL(threadFinished(qint64)), this, SLOT(onCopyThreadFinished(qint64)));
    t->start();
}

void FileList::dragMoveEvent(QDragMoveEvent* event)
{
    qDebug() << "drag move.";
    event->accept();
}

void FileList::dragEnterEvent(QDragEnterEvent* event)
{
    QListView::dragEnterEvent(event);
    event->acceptProposedAction();

//    event->setDropAction(Qt::CopyAction);
//    if(source == NULL){
//        event->setDropAction(Qt::CopyAction);
//        event->accept();
//    }
//    else if (source && source != this) {
//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    }
}

void FileList::dragLeaveEvent(QDragLeaveEvent* event)
{
    qDebug() << "dragLeaveEvent";
    QListView::dragLeaveEvent(event);
}

void FileList::dropEvent(QDropEvent* event)
{
    qDebug() << "dropEvent" << event->dropAction() << event->source();
    FileList *source =
            qobject_cast<FileList *>(event->source());
    if (source && source == this) {
        qDebug() << "dropEvent" << "same widget";
        event->ignore();
        return;
    }

    QStringList paths;
    QList<QUrl> list = event->mimeData()->urls();
    foreach(const QUrl &url, list){
        //TODO: QUrl return path '/E:/', it is not expected.
        QString path = url.path();
        paths << QDir(path.right(path.size()-1)).absolutePath();
        //qDebug() << url.path(QUrl::EncodeReserved);
    }

    if(paths.size() > 0){
        QString targetPath = QDir::fromNativeSeparators(static_cast<FileSystemModel*>(model())->rootPath());
        qDebug() << targetPath;
        doCopyTask(paths, targetPath);

        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

QList<QUrl> FileList::urlListFromSelection() const
{
    QList<QUrl> urls;
    for (const QModelIndex& index : itemSelected().indexes()) {
        if (index.column() == 0)
            urls << QUrl::fromLocalFile(static_cast<FileSystemModel*>(model())
                                          ->fileInfo(index)
                                          .canonicalFilePath());
    }
    return urls;
}

void FileList::clearClipboard()
{
    QApplication::clipboard()->clear();
}

QStringList FileList::pathsFromSelection() const {
    QStringList paths;
    for (const QModelIndex& index : itemSelected().indexes()) {
        if (index.column() == 0)
            paths << static_cast<FileSystemModel*>(model())->filePath(index);
    }
    return paths;
}


void FileList::mousePressEvent(QMouseEvent* event)
{
    QStringList paths = pathsFromSelection();
    if (event->button() == Qt::LeftButton)
        m_startPos = event->pos();
    QListView::mousePressEvent(event);
}

void FileList::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        qDebug() << "mouse move";
        int distance = (event->pos() - m_startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListView::mouseMoveEvent(event);
}

void FileList::performDrag()
{
    qDebug() << "performDrag";

    QApplication::clipboard()->clear();
    QMimeData *mimeData = new QMimeData;
    //mimeData->setText("item->text()");
    //mimeData->setImageData(QImage("F:/workspace/Clementine/data/icons/48x48/document-new.png"));

    QList<QUrl> urls;
    QStringList paths = pathsFromSelection();
    //qDebug() << "-----------" << paths;
    foreach (const QString &path, paths) {
         urls << QUrl(QString("file:///%1").arg(path));
    }

    //QList<QUrl> urls = urlListFromSelection();
    //urls << QUrl("file:///F:/workspace/Clementine/data/icons/48x48/document-new.png") << QUrl("file:///E:/迅雷下载/DIY Mechanical Counter from Cardboard.mp3");
    //qDebug() << urls;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap("F:/workspace/Clementine/data/icons/48x48/document-new.png"));

    //Qt::MoveAction
    if (drag->exec(Qt::CopyAction) == Qt::CopyAction){
        qWarning("execute an action does not want.");
    }
}

void FileList::showInBrowser()
{
    openInFileBrowser(urlListFromSelection());
}
