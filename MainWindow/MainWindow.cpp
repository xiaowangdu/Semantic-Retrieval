#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Widgets/fancytabwidget.h"
#include "../utility/Logging.hpp"
#include "../Common/iconloader.h"
#include "../utility/utilities.h"
#include "statusbar.h"

#include "../FileHelper/FileHelper.h"
#include "../LabelImage/LabelImage.h"
#include "../Preprocessing/Preprocessing.h"
#include "../RetrievalTest/RetrievalTest.h"
#include "../Training/Training.h"

#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	setMinimumSize(1400, 900);

	QStatusBar *statusbar = new StatusBar(this);
	setStatusBar(statusbar);

    setWindowTitle(QApplication::translate("MainWindow", "Semantic Retrieval", Q_NULLPTR));
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));

	m_test = new RetrievalTest(this);
	ui->tabwidget->addTab(m_test,
		IconLoader::load("test", IconLoader::Base),
		tr("Test", "Global search settings dialog title."));

	m_training = new Training(this);
	ui->tabwidget->addTab(m_training,
		IconLoader::load("train", IconLoader::Base),
		tr("Train", "Global search settings dialog title."));

	ui->tabwidget->addSpacer();

	m_process = new Preprocessing(this);
	ui->tabwidget->addTab(m_process,
		IconLoader::load("preprocess", IconLoader::Base),
		tr("Process", "Global search settings dialog title."));

	m_files = new FileHelper(this);
    ui->tabwidget->addTab(m_files,
                      IconLoader::load("folder_48x48", IconLoader::Base),
                      tr("Files", "Global search settings dialog title."));

	m_labelImageWin = new LabelImage(this);
	m_labelImageWin->setFancyTabWidget(ui->tabwidget);
	m_labelImageWin->setTabPageIndex(ui->tabwidget->count());

    ui->tabwidget->addTab(m_labelImageWin,
                      IconLoader::load("label", IconLoader::Base),
                      tr("Label", "The tool for label image."));


//    ui->tabwidget->setCurrentWidget(m_labelImageWin);

//    ui->tabwidget->addTab(global_search_view_,
//                      IconLoader::Load("search", IconLoader::Base),
//                      tr("Search", "Global search settings dialog title."));
//    ui->tabwidget->addTab(global_search_view_,
//                      IconLoader::Load("search", IconLoader::Base),
//                      tr("Search", "Global search settings dialog title."));

    ui->tabwidget->setBackgroundPixmap(QPixmap(GetConfigPath(Path_Background) + QDir::separator() + "sidebar_background.png"));
    //m_tabwidget = new FancyTabWidget(this);

    ui->tabwidget->loadSettings("MainWindow");

    //ui->toolBar->setGeometry(parentSize.width() - 25, 0, 25, parentSize.height());

    //qLog(Debug) << ui->tabwidget->pos();
    //qLog(Debug) << ui->tabwidget->size();

}

MainWindow::~MainWindow()
{
    delete ui;

    //delete m_tabwidget;
}

QTabWidget *MainWindow::fancyTabWidget()const
{
	return ui->tabwidget;
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
	m_test->closeEvent(ev);
	m_training->closeEvent(ev);
	m_process->closeEvent(ev);
	m_files->closeEvent(ev);
	m_labelImageWin->closeEvent(ev);
}