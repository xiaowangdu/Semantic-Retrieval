#include "GeneralConfig.h"
#include "../utility/MacroDef.h"
#include "../Common/CommonFunctions.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

GeneralConfig::GeneralConfig(TrainWidget *parent)
	: TrainWidget(parent)
{
	ui.setupUi(this);

	SINGLE_SLOT_CONNECT(ui.m_edtToolPath, editingFinished(), this, onToolDirChanged());
	SINGLE_SLOT_CONNECT(ui.m_edtRootDir, editingFinished(), this, onRootDirChanged());
	SINGLE_SLOT_CONNECT(ui.m_edtTrainDb, editingFinished(), this, onTrainDbDirChanged());
	SINGLE_SLOT_CONNECT(ui.m_edtTestDb, editingFinished(), this, onTestDbDirChanged());

	SINGLE_SLOT_CONNECT(ui.m_btnToolDir, clicked(), this, selectToolDir());
	SINGLE_SLOT_CONNECT(ui.m_btnRootDir, clicked(), this, selectRootDir());
	SINGLE_SLOT_CONNECT(ui.m_btnTrainDbDir, clicked(), this, selectTrainDbDir());
	SINGLE_SLOT_CONNECT(ui.m_btnTestDbDir, clicked(), this, selectTestDbDir());

	SINGLE_SLOT_CONNECT(ui.m_edtSolver, editingFinished(), this, onSolverFileChanged());
	SINGLE_SLOT_CONNECT(ui.m_edtWeights, editingFinished(), this, onWeightsFileChanged());

	SINGLE_SLOT_CONNECT(ui.m_btnSolver, clicked(), this, selectSolverFile());
	SINGLE_SLOT_CONNECT(ui.m_btnWeights, clicked(), this, selectWeightsFile());

	SINGLE_SLOT_CONNECT(ui.m_edtBinPath, editingFinished(), this, onBinDirChanged());

	SINGLE_SLOT_CONNECT(ui.m_btnBinDir, clicked(), this, selectBinDir());

	m_config.load(configPath() + QDir::separator() + "TrainConfig.dat");
	if (m_config.size() > 0) {
		readFromSets();
	}
	else {
		m_config.new_element("toolDir", m_toolDir);
		m_config.new_element("rootDir", m_rootDir);
		m_config.new_element("trainDbDir", m_trainDbDir);
		m_config.new_element("testDbDir", m_testDbDir);
		m_config.new_element("solverFile", m_solverFile);
		m_config.new_element("weightsFile", m_weightsFile);
		m_config.new_element("binDir", m_binDir);
	}

	updateControls();
}

GeneralConfig::~GeneralConfig()
{
}

QString GeneralConfig::getRootDir() const
{
	return m_rootDir;
}

QString GeneralConfig::getToolDir() const
{
	return m_toolDir;
}

QString GeneralConfig::getTrainDbDir() const
{
	return m_trainDbDir;
}

QString GeneralConfig::getTestDbDir() const
{
	return m_testDbDir;
}

QString GeneralConfig::getSolverFile() const
{
	return m_solverFile;
}

QString GeneralConfig::getWeightsFile() const
{
	return m_weightsFile;
}

QString GeneralConfig::getBinDir() const
{
	return m_binDir;
}

bool GeneralConfig::useGPU() const
{
	return ui.m_checkBox->isChecked();
}

void GeneralConfig::onBtnOk()
{
	write2Sets();
	//updateControls();
	emit closeWidget();
}

void GeneralConfig::onBtnCancel()
{
	readFromSets();
	updateControls();
	emit closeWidget();
}

void GeneralConfig::onBtnApply()
{
	write2Sets();
	updateControls();
}

bool GeneralConfig::askingYesDialog(const QString &msg)
{
	return QMessageBox::Yes == QMessageBox::warning(this, "Attention", msg, QMessageBox::Yes | QMessageBox::No);
}

QString GeneralConfig::checkEdtDir(QLineEdit *edit)
{
	QString filename = edit->text();
	if (filename.isEmpty()) {
		return QString();
	}

	if (!QDir(filename).exists()) {
		QString msg = QString("'%1' is not a valid directory, continue anyway?").arg(filename);
		if (!askingYesDialog(msg)) {
			return QString();
		}
	}

	return filename;
}

bool GeneralConfig::isValidFile(const QString &filename)
{
	QFileInfo fileinfo(filename);
	if (fileinfo.suffix() != "prototxt" && fileinfo.suffix() != "caffemodel") {
		return false;
	}

	return fileinfo.exists();
}

QString GeneralConfig::checkEdtFile(QLineEdit *edit, const QString &type)
{
	QString filename = edit->text();
	if (filename.isEmpty()) {
		return QString();
	}

	if (!isValidFile(filename)) {
		QString msg = QString("'%1' is not a valid %2 file, continue anyway?").arg(filename).arg(type);
		if (!askingYesDialog(msg)) {
			return QString();
		}
	}

	return filename;
}

QString GeneralConfig::selectDir(QString &defaultDir)
{
	QString defaultOpenDirPath = defaultDir.isEmpty() ? "." : defaultDir;

	QString targetDirPath = QFileDialog::getExistingDirectory(this,
		QString("%1 - Open Directory").arg("Train General Config"), defaultOpenDirPath,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (targetDirPath.isEmpty()) {
		return QString();
	}

	return targetDirPath;
}
void GeneralConfig::onRootDirChanged()
{
	QString filename = checkEdtDir(ui.m_edtRootDir);
	if (filename.isEmpty()) {
		return;
	}

	m_rootDir = filename;
}

void GeneralConfig::onToolDirChanged()
{
	QString filename = checkEdtDir(ui.m_edtToolPath);
	if (filename.isEmpty()) {
		return;
	}

	m_toolDir = filename;
}

void GeneralConfig::onTrainDbDirChanged()
{
	QString filename = checkEdtDir(ui.m_edtTrainDb);
	if (filename.isEmpty()) {
		return;
	}

	m_trainDbDir = filename;
}

void GeneralConfig::onTestDbDirChanged()
{
	QString filename = checkEdtDir(ui.m_edtTestDb);
	if (filename.isEmpty()) {
		return;
	}

	m_testDbDir = filename;
}

void GeneralConfig::onSolverFileChanged()
{
	QString filename = checkEdtFile(ui.m_edtSolver, "prototxt");
	if (filename.isEmpty()) {
		return;
	}

	m_solverFile = filename;
}

void GeneralConfig::onWeightsFileChanged()
{
	QString filename = checkEdtFile(ui.m_edtWeights, "caffemodel");
	if (filename.isEmpty()) {
		return;
	}

	m_weightsFile = filename;
}

void GeneralConfig::onBinDirChanged()
{
	QString filename = checkEdtDir(ui.m_edtBinPath);
	if (filename.isEmpty()) {
		return;
	}

	m_binDir = filename;
}

void GeneralConfig::selectToolDir()
{
	QString dir = selectDir(m_toolDir);
	if (dir.isEmpty()) {
		return;
	}

	ui.m_edtToolPath->setText(dir);
	onToolDirChanged();
}

void GeneralConfig::selectRootDir()
{
	QString dir = selectDir(m_rootDir);
	if (dir.isEmpty()) {
		return;
	}

	ui.m_edtRootDir->setText(dir);
	onRootDirChanged();
}

void GeneralConfig::selectTrainDbDir()
{
	QString dir = selectDir(m_trainDbDir);
	if (dir.isEmpty()) {
		return;
	}

	ui.m_edtTrainDb->setText(dir);
	onTrainDbDirChanged();
}

void GeneralConfig::selectTestDbDir()
{
	QString dir = selectDir(m_testDbDir);
	if (dir.isEmpty()) {
		return;
	}

	ui.m_edtTestDb->setText(dir);
	onTestDbDirChanged();
}

QString GeneralConfig::getFileNameByDialog(const QString &path, const QString &filter)
{
	QString p = path;
	if (path.isEmpty()) {
		p = ".";
	}

	QString filters = QString("Choose files (%1)").arg(filter);
	QString filename = QFileDialog::getOpenFileName(this, QString("%1 - Choose file").arg("Train General Config"), path, filters);

	return filename;
}

void GeneralConfig::write2Sets()
{
	m_config.modify_element("toolDir", m_toolDir); 
	m_config.modify_element("rootDir", m_rootDir);
	m_config.modify_element("trainDbDir", m_trainDbDir);
	m_config.modify_element("testDbDir", m_testDbDir);
	m_config.modify_element("solverFile", m_solverFile);
	m_config.modify_element("weightsFile", m_weightsFile);
	m_config.modify_element("binDir", m_binDir);
}

void GeneralConfig::flush()
{

}

void GeneralConfig::readFromSets()
{
	m_config.decode_element(&(m_config["toolDir"]), m_toolDir);
	m_config.decode_element(&(m_config["rootDir"]), m_rootDir);
	m_config.decode_element(&(m_config["trainDbDir"]), m_trainDbDir);
	m_config.decode_element(&(m_config["testDbDir"]), m_testDbDir);
	m_config.decode_element(&(m_config["solverFile"]), m_solverFile);
	m_config.decode_element(&(m_config["weightsFile"]), m_weightsFile);
	m_config.decode_element(&(m_config["binDir"]), m_binDir);
}

void GeneralConfig::updateControls()
{
	//ui->m_groupBox->setChecked(m_resized);

	ui.m_edtToolPath->setText(m_toolDir);
	ui.m_edtRootDir->setText(m_rootDir);
	ui.m_edtTrainDb->setText(m_trainDbDir);
	ui.m_edtTestDb->setText(m_testDbDir);
	ui.m_edtSolver->setText(m_solverFile);
	ui.m_edtWeights->setText(m_weightsFile);
	ui.m_edtBinPath->setText(m_binDir);
	update();
}

void GeneralConfig::selectSolverFile()
{
	QString targetPath = getFileNameByDialog(m_solverFile, "*.prototxt");
	if (targetPath.isEmpty()) {
		return;
	}
	ui.m_edtSolver->setText(targetPath);
	onSolverFileChanged();
}

void GeneralConfig::selectWeightsFile()
{
	QString targetPath = getFileNameByDialog(m_weightsFile, "*.caffemodel");
	if (targetPath.isEmpty()) {
		return;
	}
	ui.m_edtWeights->setText(targetPath);
	onWeightsFileChanged();
}

void GeneralConfig::selectBinDir()
{
	QString dir = selectDir(m_binDir);
	if (dir.isEmpty()) {
		return;
	}

	ui.m_edtBinPath->setText(dir);
	onBinDirChanged();
}

void GeneralConfig::closeEvent(QCloseEvent *event)
{
	write2Sets();
	m_config.save(configPath() + QDir::separator() + "TrainConfig.dat");
}