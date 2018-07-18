#include "LMDBGenerator.h"
#include "GeneratedFiles/ui_LMDBGenerator.h"
#include "../utility/MacroDef.h"
#include "../utility/Constants.hpp"
#include "../Common/iconloader.h"
#include "../Common/CommonFunctions.h"
#include "../Common/ProcessLogger.h"
#include "../Common/LoggerInterface.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QProcess>

const QString LMDBGenerator::BAXKEND = "leveldb";

LMDBGenerator::LMDBGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMDBGenerator),
	m_poc(new QProcess)
{
    ui->setupUi(this);
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));

	ui->m_edtWidth->setValidator(new QIntValidator(0, INT32MAX, this));
	ui->m_edtHeight->setValidator(new QIntValidator(0, INT32MAX, this));

	m_poc->setProcessChannelMode(QProcess::MergedChannels);
	LoggerInterface *logger = new ProcessLogger();
	logger->setProcess(m_poc);
	logger->initConsoleLogger();
	logger->initFileLogger("F:/workspace/proc_log.txt");
	logger->initControlLogger(ui->m_textBrowser);

	m_config.load(configPath() + QDir::separator() + "LMDBGeneratorConfig.dat");
	if (m_config.size() > 0) {
		readFromSets();
	}
	else {
		m_config.new_element("resized", (int)m_resized);
		m_config.new_element("width", m_resizeWidth);
		m_config.new_element("height", m_resizeHeight);
		m_config.new_element("root_path", m_rootPath);
		m_config.new_element("input_path", m_inputFilePath);
		m_config.new_element("output_path", m_outputDBPath);
		m_config.new_element("db_name", m_outputDBName);
	}

	updateControls();

	SINGLE_SLOT_CONNECT(m_poc, finished(int), this, onProcessFinished(int));
	SINGLE_SLOT_CONNECT(ui->m_btnTool, clicked(), this, selectToolDir());
	SINGLE_SLOT_CONNECT(ui->m_btnRoot, clicked(), this, selectRootDir());
	SINGLE_SLOT_CONNECT(ui->m_btnInput, clicked(), this, selectListFilePath());
	SINGLE_SLOT_CONNECT(ui->m_btnOutput, clicked(), this, selectOutputDBPath());
	SINGLE_SLOT_CONNECT(ui->m_btnMake, clicked(), this, startMakeDB());
	SINGLE_SLOT_CONNECT(ui->m_edtOutputFileName, editingFinished(), this, setDbName());
	SINGLE_SLOT_CONNECT(ui->m_edtWidth, editingFinished(), this, flush());
	SINGLE_SLOT_CONNECT(ui->m_edtHeight, editingFinished(), this, flush());

}

LMDBGenerator::~LMDBGenerator()
{
    delete ui;
	delete m_poc;
}

void LMDBGenerator::onListFileChanged()
{
	QString filename = ui->m_edtInputFile->text();
	if (filename.isEmpty()) {
		return;
	}

	//if (!isValidFile(filename)) {
	//	QString msg = QString("'%1' is not a valid binary feature path, continue anyway?").arg(filename);
	//	if (!askingYesDialog(msg)) {
	//		return;
	//	}
	//}

	m_inputFilePath = filename;
}

void LMDBGenerator::onOutputDBPathChanged()
{
	QString filename = ui->m_edtOutputFile->text();
	if (filename.isEmpty()) {
		return;
	}

	//if (!isValidFile(filename)) {
	//	QString msg = QString("'%1' is not a valid binary feature path, continue anyway?").arg(filename);
	//	if (!askingYesDialog(msg)) {
	//		return;
	//	}
	//}

	m_outputDBPath = filename;
}


void LMDBGenerator::startMakeDB()
{

	QString cmd = makeCommandString();
	qDebug() << "start do cmd" << cmd;
	//m_poc->start("D:/Tools/Caffe/bin/convert_imageset --resize_height=256 --resize_width=256 --shuffle --backend=leveldb D:/Tools/Caffe/matlab/demo/examples/Caltech256/256_ObjectCategories D:/Tools/Caffe/matlab/demo/examples/Caltech256/train_file_list.txt F:/workspace/project/SemanticRetrieval/LMDBGenerator/x64/train_leveldb -logbufsecs=1");
	m_poc->start(cmd);
	ui->m_btnMake->setText("Waiting...");
	ui->m_btnMake->setEnabled(false);
}

void LMDBGenerator::setDbName()
{
	m_outputDBName = ui->m_edtOutputFileName->text();
}

void LMDBGenerator::onProcessFinished(int)
{
	ui->m_btnMake->setText("Start Make");
	ui->m_btnMake->setEnabled(true);
}

void LMDBGenerator::closeEvent(QCloseEvent *event)
{
	//qDebug() << configPath() + QDir::separator() + "LMDBGeneratorConfig.dat";
	flush();// read again.
	write2Sets();
	m_config.save(configPath() + QDir::separator() + "LMDBGeneratorConfig.dat");
}

void LMDBGenerator::onRootPathChanged()
{
	QString filename = ui->m_edtRootPath->text();
	if (filename.isEmpty()) {
		return;
	}

	//if (!isValidFile(filename)) {
	//	QString msg = QString("'%1' is not a valid raw feature path, continue anyway?").arg(filename);
	//	if (!askingYesDialog(msg)) {
	//		return;
	//	}
	//}
	m_rootPath = filename;
}

void LMDBGenerator::onToolPathChanged()
{
	QString filename = ui->m_edtToolPath->text();
	if (filename.isEmpty()) {
		return;
	}

	//if (!isValidFile(filename)) {
	//	QString msg = QString("'%1' is not a valid raw feature path, continue anyway?").arg(filename);
	//	if (!askingYesDialog(msg)) {
	//		return;
	//	}
	//}
	m_toolPath = filename;
}

void LMDBGenerator::selectToolDir()
{
	QString defaultOpenDirPath = m_toolPath.isEmpty() ? "." : m_toolPath;
	QString targetpath = openDirDialog(defaultOpenDirPath);
	if (targetpath.isEmpty()) {
		return;
	}

	ui->m_edtToolPath->setText(targetpath);
	onToolPathChanged();
}

QString LMDBGenerator::openDirDialog(const QString &defaultOpenDirPath)
{
	QString targetDirPath = QFileDialog::getExistingDirectory(this,
		QString("%1 - Open Directory").arg("LMDB Generator"), defaultOpenDirPath,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (targetDirPath.isEmpty()) {
		return QString();
	}

	return targetDirPath;
}

void LMDBGenerator::selectRootDir()
{
	QString defaultOpenDirPath = m_rootPath.isEmpty() ? "." : m_rootPath;
	QString targetpath = openDirDialog(defaultOpenDirPath);
	if (targetpath.isEmpty()) {
		return;
	}

	ui->m_edtRootPath->setText(targetpath);
	onRootPathChanged();
}

void LMDBGenerator::selectListFilePath()
{
	QString targetPath = getFileNameByDialog(m_inputFilePath);
	if (targetPath.isEmpty()) {
		return;
	}
	ui->m_edtInputFile->setText(targetPath);
	onListFileChanged();
}

void LMDBGenerator::selectOutputDBPath()
{
	QString defaultOpenDirPath = m_outputDBPath.isEmpty() ? "." : m_outputDBPath;

	QString targetpath = openDirDialog(defaultOpenDirPath);
	if (targetpath.isEmpty()) {
		return;
	}

	ui->m_edtOutputFile->setText(targetpath);
	onOutputDBPathChanged();
}

QString LMDBGenerator::getFileNameByDialog(const QString &path)
{
	QString p = path;
	if (path.isEmpty()) {
		p = ".";
	}

	QString filters = QString("Txt files (%1)").arg("*.txt");
	QString filename = QFileDialog::getOpenFileName(this, QString("%1 - Choose Txt file").arg("LMDBGenerator Config"), path, filters);

	return filename;
}

void LMDBGenerator::write2Sets()
{
	m_config.modify_element("resized", (int)m_resized);
	m_config.modify_element("width", m_resizeWidth);
	m_config.modify_element("height", m_resizeHeight);
	m_config.modify_element("tool_path", m_toolPath);
	m_config.modify_element("root_path", m_rootPath);
	m_config.modify_element("input_path", m_inputFilePath);
	m_config.modify_element("output_path", m_outputDBPath);
	m_config.modify_element("db_name", m_outputDBName);
}

void LMDBGenerator::flush()
{
	setDbName();
	m_resized = ui->m_groupBox->isChecked();
	m_resizeWidth = ui->m_edtWidth->text().toInt();
	m_resizeHeight = ui->m_edtHeight->text().toInt();
}

void LMDBGenerator::readFromSets()
{
	int resized = 0;
	m_config.decode_element(&(m_config["resized"]), resized);
	m_resized = resized;
	m_config.decode_element(&(m_config["width"]), m_resizeWidth);
	m_config.decode_element(&(m_config["height"]), m_resizeHeight);
	m_config.decode_element(&(m_config["tool_path"]), m_toolPath);
	m_config.decode_element(&(m_config["root_path"]), m_rootPath);
	m_config.decode_element(&(m_config["input_path"]), m_inputFilePath);
	m_config.decode_element(&(m_config["output_path"]), m_outputDBPath);
	m_config.decode_element(&(m_config["db_name"]), m_outputDBName);
}

QString LMDBGenerator::makeCommandString()
{
	int width = 256, height = 256;
	if (m_resized) {
		width = ui->m_edtWidth->text().toInt();
		height = ui->m_edtHeight->text().toInt();
	}

	if (m_toolPath.isEmpty() || m_rootPath.isEmpty() || m_inputFilePath.isEmpty() || m_outputDBPath.isDetached() || m_outputDBName.isEmpty()) {
		QString msg = "The tool path and list file should be geiven.";
		QMessageBox::warning(this, "Attention", msg, QMessageBox::Ok);
		return QString();
	}

	return QString("%1/convert_imageset --resize_height=%2 --resize_width=%3 --shuffle --backend=%4 %5 %6 %7")
		.arg(m_toolPath)
		.arg(m_resizeHeight)
		.arg(m_resizeWidth)
		.arg(BAXKEND)
		.arg(m_rootPath+"/")
		.arg(m_inputFilePath)
		.arg(m_outputDBPath + "/" + m_outputDBName);
}

void LMDBGenerator::updateControls()
{
	ui->m_groupBox->setChecked(m_resized);
	ui->m_edtWidth->setText(QString::number(m_resizeWidth));
	ui->m_edtHeight->setText(QString::number(m_resizeHeight));

	ui->m_edtToolPath->setText(m_toolPath);
	ui->m_edtRootPath->setText(m_rootPath);
	ui->m_edtInputFile->setText(m_inputFilePath);
	ui->m_edtOutputFile->setText(m_outputDBPath);
	ui->m_edtOutputFileName->setText(m_outputDBName);
	update();
}