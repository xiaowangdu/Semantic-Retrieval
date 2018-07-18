#pragma once

#include <QWidget>
#include "ui_FileBrowser.h"
#include <QWidget>
#include <QUndoCommand>
#include <QUrl>
#include <QModelIndex>

class FileSystemModel;

class FileBrowser : public QWidget
{
	Q_OBJECT

public:
    FileBrowser(qint64 id, QWidget *parent = Q_NULLPTR);
    ~FileBrowser();

    void setPath(const QString& path);

    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent* e);

signals:
    void newFileView();
    void pathChanged(const QString &path);
    void deleteFileView(qint64);
    void updateFileInfo(const QFileInfo& fileInfo, const QIcon &icon);

private slots:
    void onDeleteClicked();

    void fileUp();
    void fileHome();
    void changeFilePath(const QString& new_path);
    void itemActivated(const QModelIndex& index);

//    void deleteFiles(const QStringList& filenames);
//    void deleteFinished(const SongList& songs_with_errors);

private:
    void changeFilePathWithoutUndo(const QString& new_path);


private:
    class UndoCommand : public QUndoCommand {
     public:
      UndoCommand(FileBrowser* view, const QString& new_path);

      QString undoPath() const { return m_oldState.path; }

      void undo();
      void redo();

     private:
      struct State {
        State() : scrollPos(-1) {}

        QString path;
        QModelIndex index;
        int scrollPos;
      };

      FileBrowser* m_view;
      State m_oldState;
      State m_newState;
    };

private:
    Ui::FileBrowser *ui;
    qint64 m_id;


    FileSystemModel* m_model;
    QUndoStack* m_undoStack;

    QString m_lazySetPath;

    QStringList m_filterList;
};
