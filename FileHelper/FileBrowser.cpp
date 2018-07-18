#include "FileBrowser.h"
#include "FileList.h"
#include "FileSystemModel.h"

#include <QKeyEvent>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

FileBrowser::FileBrowser(qint64 id, QWidget *parent)
    : m_id(id), QWidget(parent),
    ui(new Ui::FileBrowser)
{
    ui->setupUi(this);

    m_model = nullptr;
    m_undoStack = new QUndoStack(this);

    //set icon.
    ui->m_btnNew->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/document-new.png")));
    ui->m_btnDelete->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/application-exit.png")));
    ui->m_btnBack->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/go-previous.png")));
    ui->m_btnForward->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/go-next.png")));
    ui->m_btnUp->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/go-up.png")));
    ui->m_btnHome->setIcon(QIcon(QPixmap("F:/workspace/Clementine/data/icons/48x48/go-home.png")));


    connect(ui->m_btnNew, SIGNAL(clicked()), this, SIGNAL(newFileView()));
    connect(ui->m_btnDelete, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));

    connect(ui->m_btnBack, SIGNAL(clicked()), m_undoStack, SLOT(undo()));
    connect(ui->m_btnForward, SIGNAL(clicked()), m_undoStack, SLOT(redo()));
    connect(ui->m_btnHome, SIGNAL(clicked()), SLOT(fileHome()));
    connect(ui->m_btnUp, SIGNAL(clicked()), SLOT(fileUp()));
    connect(ui->m_edtPath, SIGNAL(textChanged(QString)),
            SLOT(changeFilePath(QString)));

//    connect(ui_->list, SIGNAL(Back()), undo_stack_, SLOT(undo()));
//    connect(ui_->list, SIGNAL(Forward()), undo_stack_, SLOT(redo()));

    connect(m_undoStack, SIGNAL(canUndoChanged(bool)), ui->m_btnBack,
            SLOT(setEnabled(bool)));
    connect(m_undoStack, SIGNAL(canRedoChanged(bool)), ui->m_btnForward,
            SLOT(setEnabled(bool)));

    connect(ui->m_list, SIGNAL(activated(QModelIndex)),
            SLOT(itemActivated(QModelIndex)));

    connect(ui->m_list, SIGNAL(updateFileInfo(const QFileInfo&, const QIcon &)), SIGNAL(updateFileInfo(const QFileInfo&, const QIcon &)));
//    connect(ui_->list, SIGNAL(EditTags(QList<QUrl>)),
//            SIGNAL(EditTags(QList<QUrl>)));


}

FileBrowser::~FileBrowser()
{
}

void FileBrowser::setPath(const QString& path)
{
  if (!m_model)
    m_lazySetPath = path;
  else
    changeFilePathWithoutUndo(path);
}

void FileBrowser::showEvent(QShowEvent* e)
{
  QWidget::showEvent(e);

  if (m_model) return;

  m_model = new FileSystemModel(this);
  m_model->setIconProvider(new IconProvider());

  m_model->setNameFilters(m_filterList);
  QDir::Filters oldFilter = m_model->filter();
  m_model->setFilter(oldFilter | QDir::Hidden);
  // if an item fails the filter, hide it
  m_model->setNameFilterDisables(false);

  ui->m_list->setModel(m_model);
  changeFilePathWithoutUndo(/*QDir::homePath()*/"E:\\");

  if(!m_lazySetPath.isEmpty()){
      changeFilePathWithoutUndo(m_lazySetPath);
  }
}

void FileBrowser::keyPressEvent(QKeyEvent* e)
{
  switch (e->key()) {
    case Qt::Key_Back:
    case Qt::Key_Backspace:
      ui->m_btnUp->click();
      break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
      itemActivated(ui->m_list->currentIndex());
      break;
  }
  QWidget::keyPressEvent(e);
}


void FileBrowser::onDeleteClicked()
{
    emit deleteFileView(m_id);
}

void FileBrowser::fileUp() {
  QDir dir(m_model->rootDirectory());
  dir.cdUp();

  // Is this the same as going back?  If so just go back, so we can keep the
  // view scroll position.
  if (m_undoStack->canUndo()) {
    const UndoCommand* last_dir = static_cast<const UndoCommand*>(
        m_undoStack->command(m_undoStack->index() - 1));
    if (last_dir->undoPath() == dir.path()) {
      m_undoStack->undo();
      return;
    }
  }

  changeFilePath(dir.path());
}

void FileBrowser::fileHome()
{
    changeFilePath(QDir::homePath());
}

void FileBrowser::changeFilePath(const QString& new_path_native)
{
  QString new_path = QDir::fromNativeSeparators(new_path_native);

  QFileInfo info(new_path);
  if (!info.exists() || !info.isDir()) return;

  QString old_path(m_model->rootPath());
  if (old_path == new_path) return;

  m_undoStack->push(new UndoCommand(this, new_path));
}

void FileBrowser::itemActivated(const QModelIndex& index) {
  if (m_model->isDir(index)) changeFilePath(m_model->filePath(index));
}


void FileBrowser::changeFilePathWithoutUndo(const QString& new_path) {
  ui->m_list->setRootIndex(m_model->setRootPath(new_path));
  ui->m_edtPath->setText(QDir::toNativeSeparators(new_path));

  QDir dir(new_path);
  ui->m_btnUp->setEnabled(dir.cdUp());

  emit pathChanged(new_path);
}

FileBrowser::UndoCommand::UndoCommand(FileBrowser* view, const QString& new_path)
    : m_view(view) {
  m_oldState.path = view->m_model->rootPath();
  m_oldState.scrollPos = m_view->ui->m_list->verticalScrollBar()->value();
  m_oldState.index = m_view->ui->m_list->currentIndex();

  m_newState.path = new_path;
}

void FileBrowser::UndoCommand::redo() {
  m_view->changeFilePathWithoutUndo(m_newState.path);
  if (m_newState.scrollPos != -1) {
    m_view->ui->m_list->setCurrentIndex(m_newState.index);
    m_view->ui->m_list->verticalScrollBar()->setValue(m_newState.scrollPos);
  }
}

void FileBrowser::UndoCommand::undo() {

  m_newState.scrollPos = m_view->ui->m_list->verticalScrollBar()->value();
  m_newState.index = m_view->ui->m_list->currentIndex();

  m_view->changeFilePathWithoutUndo(m_oldState.path);
  m_view->ui->m_list->setCurrentIndex(m_oldState.index);
  m_view->ui->m_list->verticalScrollBar()->setValue(m_oldState.scrollPos);
}

//void FileBrowser::deleteFiles(const QStringList& filenames) {
//  if (filenames.isEmpty()) return;

//  if (QMessageBox::warning(this, tr("Delete files"),
//                           tr("These files will be permanently deleted from "
//                              "disk, are you sure you want to continue?"),
//                           QMessageBox::Yes,
//                           QMessageBox::Cancel) != QMessageBox::Yes)
//    return;

//  DeleteFiles* delete_files = new DeleteFiles(task_manager_, storage_);
//  connect(delete_files, SIGNAL(Finished(SongList)),
//          SLOT(DeleteFinished(SongList)));
//  delete_files->Start(filenames);
//}

