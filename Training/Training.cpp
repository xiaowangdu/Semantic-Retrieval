#include "Training.h"
#include "GeneratedFiles/ui_Training.h"
#include "TrainingConfig.h"
#include "GeneralConfig.h"
#include "../utility/MacroDef.h"
#include "../Common/ProcessLogger.h"
#include "../Common/LoggerInterface.h"
#include <QDebug>
#include <QProcess>
#include <QDir>

Training::Training(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Training),
	m_poc(new QProcess)
{
    ui->setupUi(this);

	QPalette pal;
	pal = ui->m_txtMiniConsole->palette();
	pal.setColor(QPalette::Text, QColor(255, 255, 255));
	pal.setColor(QPalette::Base, QColor(0, 0, 0));
	ui->m_txtMiniConsole->setPalette(pal);

	m_trainConfig = new TrainingConfig();

	m_poc->setProcessChannelMode(QProcess::MergedChannels);
	LoggerInterface *logger = new ProcessLogger();
	logger->setProcess(m_poc);
	//logger->initConsoleLogger();
	//logger->initFileLogger("F:/workspace/proc_log.txt");
	logger->initControlLogger(ui->m_txtMiniConsole);

	SINGLE_SLOT_CONNECT(ui->m_btnConfig, clicked(), this, onBtnConfig());
	SINGLE_SLOT_CONNECT(ui->m_btnStartTrain, clicked(), this, onBtnPrepareTrain());
	SINGLE_SLOT_CONNECT(ui->m_btnRunCmd, clicked(), this, onBtnRunCommand());
	SINGLE_SLOT_CONNECT(m_poc, finished(int), this, onProcessFinished(int));
}

Training::~Training()
{
    delete ui;
	delete m_trainConfig;
}

void Training::closeEvent(QCloseEvent *ev)
{
	m_trainConfig->closeEvent(ev);
}

void Training::onBtnConfig()
{
	qDebug() << "Hello .";
	m_trainConfig->show();
}

void Training::onBtnPrepareTrain()
{
	GeneralConfig *config = m_trainConfig->generalConfig();
	if (config == NULL) {
		return;
	}

	QDir wordir(config->getRootDir());
	if (!wordir.exists()) {
		return;
	}

	QString whereEXE = config->getToolDir() + QDir::separator() + "caffe train";

	QString useGPU = "";
	if (config->useGPU()) {
		useGPU = "-gpu all";
	}

	QString command = "%1 -solver  %2 -weights %3 %4";
	command = command.arg(whereEXE).arg(config->getSolverFile()).arg(config->getWeightsFile()).arg(useGPU);

	ui->m_edtCommand->setText(command);
}

void Training::onBtnRunCommand()
{
	QString cmd = ui->m_edtCommand->text();
	if (cmd.isEmpty()) {
		return;
	}
	qDebug() << "start do cmd" << cmd;

	m_poc->setWorkingDirectory(m_trainConfig->generalConfig()->getRootDir());
	//m_poc->start("D:/Tools/Caffe/bin/convert_imageset --resize_height=256 --resize_width=256 --shuffle --backend=leveldb D:/Tools/Caffe/matlab/demo/examples/Caltech256/256_ObjectCategories D:/Tools/Caffe/matlab/demo/examples/Caltech256/train_file_list.txt F:/workspace/project/SemanticRetrieval/LMDBGenerator/x64/train_leveldb -logbufsecs=1");
	m_poc->start(cmd);
	
	ui->m_btnRunCmd->setText("Waiting...");
	ui->m_btnRunCmd->setEnabled(false);
}

void Training::onProcessFinished(int)
{
	ui->m_btnRunCmd->setText("Start Train");
	ui->m_btnRunCmd->setEnabled(true);
}