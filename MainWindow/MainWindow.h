#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FancyTabWidget;
class LabelImage;
class RetrievalTest;
class Training;
class Preprocessing;
class FileHelper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	QTabWidget *fancyTabWidget()const;

protected:
	void closeEvent(QCloseEvent *ev);

private:
    Ui::MainWindow *ui;

    FancyTabWidget *m_tabwidget;
	RetrievalTest *m_test;
	Training *m_training;
	Preprocessing *m_process;
	FileHelper *m_files;
	LabelImage *m_labelImageWin;
};

#endif // MAINWINDOW_H
