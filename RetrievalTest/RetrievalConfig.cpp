#include "RetrievalConfig.h"
#include "GeneratedFiles/ui_RetrievalConfig.h"
#include "../utility/MacroDef.h"
#include "../utility/Constants.hpp"
#include "../Common/iconloader.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

RetrievalConfig::RetrievalConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RetrievalConfig)
{
    ui->setupUi(this);

	setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));

	m_config.load(retrievalConfigPath() + QDir::separator() + "RetrievalConfig.dat");
	if (m_config.size() > 0) {
		readFromSets();
	}
	else {
		m_config.new_element("top_k", m_topK);
		m_config.new_element("img_lib", m_imageLibPath);
		m_config.new_element("bin_path", m_binaryFeaturePath);
		m_config.new_element("raw_path", m_rawFeaturePath);
	}

	updateControls();

	SINGLE_SLOT_CONNECT(ui->m_spinBox, valueChanged(int), this, onSpinboxValueChanged(int));
	SINGLE_SLOT_CONNECT(ui->m_edtLibPath, editingFinished(), this, onLibPathChanged());
	SINGLE_SLOT_CONNECT(ui->m_edtBinPath, editingFinished(), this, onBinPathChanged());
	SINGLE_SLOT_CONNECT(ui->m_edtRawPath, editingFinished(), this, onRawPathChanged());

	SINGLE_SLOT_CONNECT(ui->m_btnDirLib, clicked(), this, selectLibDir());
	SINGLE_SLOT_CONNECT(ui->m_btnDirBin, clicked(), this, selectBinFile());
	SINGLE_SLOT_CONNECT(ui->m_btnRaw, clicked(), this, selectRawFeatureFile());

	SINGLE_SLOT_CONNECT(ui->m_btnOk, clicked(), this, onBtnOk());
	SINGLE_SLOT_CONNECT(ui->m_btnCancel, clicked(), this, onBtnCancel());
	SINGLE_SLOT_CONNECT(ui->m_btnReset, clicked(), this, onBtnReset());
}

RetrievalConfig::~RetrievalConfig()
{
    delete ui;
}

unsigned int RetrievalConfig::getTopK()const
{
	return m_topK;
}

void RetrievalConfig::setDefaultTopK(unsigned int k)
{
	m_topK = k;
	ui->m_spinBox->setValue(m_topK);
	m_config.modify_element("top_k", m_topK);
}

QString RetrievalConfig::getImageLib()const
{
	return m_imageLibPath;
}

void RetrievalConfig::setDefaultImageLibPath(const QString &path)
{
	m_imageLibPath = path;
	ui->m_edtLibPath->setText(m_imageLibPath);
	m_config.modify_element("img_lib", m_imageLibPath);
}

QString RetrievalConfig::getBinFeaturePath()const
{
	return m_binaryFeaturePath;
}

void RetrievalConfig::setDefaultBinFeaturePath(const QString &path)
{
	m_binaryFeaturePath = path;
	ui->m_edtBinPath->setText(m_binaryFeaturePath);
	m_config.modify_element("bin_path", m_binaryFeaturePath);
}
QString RetrievalConfig::getRawFeaturePath()const
{
	return m_rawFeaturePath;
}

bool RetrievalConfig::isValidFile(const QString &filename)
{
	QFileInfo fileinfo(filename);
	if (fileinfo.suffix() != "mat") {
		return false;
	}

	return fileinfo.exists();
}

void RetrievalConfig::closeEvent(QCloseEvent *event)
{
	qDebug() << "lllll";
	m_config.save(retrievalConfigPath() + QDir::separator() + "RetrievalConfig.dat");
}

void RetrievalConfig::setDefaultRawFeaturePath(const QString &path)
{
	m_rawFeaturePath = path;
	ui->m_edtRawPath->setText(m_rawFeaturePath);
	m_config.modify_element("raw_path", m_rawFeaturePath);
}

bool RetrievalConfig::askingYesDialog(const QString &msg)
{
	return QMessageBox::Yes == QMessageBox::warning(this, "Attention", msg, QMessageBox::Yes | QMessageBox::No);
}

QString RetrievalConfig::getFileNameByDialog(const QString &path)
{
	QString p = path;
	if (path.isEmpty()) {
		p = ".";
	}

	QString filters = QString("Mat files (%1)").arg("*.mat");
	QString filename = QFileDialog::getOpenFileName(this, QString("%1 - Choose Mat file").arg("Retrieval Config"), path, filters);

	return filename;
}

void RetrievalConfig::onSpinboxValueChanged(int val)
{
	m_topK = val;
}

void RetrievalConfig::onLibPathChanged()
{
	qDebug() << "onLibPathChanged()";
	QString filename = ui->m_edtLibPath->text();
	if (filename.isEmpty()) {
		return;
	}

	if (!QDir(filename).exists()) {
		QString msg = QString("'%1' is not a valid lib directory, continue anyway?").arg(filename);
		if (!askingYesDialog(msg)) {
			return;
		}
	}

	m_imageLibPath = filename;
}

void RetrievalConfig::onBinPathChanged()
{
	QString filename = ui->m_edtBinPath->text();
	if (filename.isEmpty()) {
		return;
	}

	if (!isValidFile(filename)) {
		QString msg = QString("'%1' is not a valid binary feature path, continue anyway?").arg(filename);
		if (!askingYesDialog(msg)) {
			return;
		}
	}

	m_binaryFeaturePath = filename;
}

void RetrievalConfig::onRawPathChanged()
{
	QString filename = ui->m_edtRawPath->text();
	if (filename.isEmpty()) {
		return;
	}

	if (!isValidFile(filename)) {
		QString msg = QString("'%1' is not a valid raw feature path, continue anyway?").arg(filename);
		if (!askingYesDialog(msg)) {
			return;
		}
	}
	m_rawFeaturePath = filename;
}

void RetrievalConfig::selectLibDir()
{
	QString defaultOpenDirPath = m_imageLibPath.isEmpty() ? "." : m_imageLibPath;

	QString targetDirPath = QFileDialog::getExistingDirectory(this,
		QString("%1 - Open Directory").arg("Retrieval Config"), defaultOpenDirPath,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (targetDirPath.isEmpty()) {
		return;
	}
	ui->m_edtLibPath->setText(targetDirPath);
	onLibPathChanged();
}

void RetrievalConfig::selectBinFile()
{
	QString targetPath = getFileNameByDialog(m_binaryFeaturePath);
	if (targetPath.isEmpty()) {
		return;
	}
	ui->m_edtBinPath->setText(targetPath);
	onBinPathChanged();
}

void RetrievalConfig::selectRawFeatureFile()
{
	QString targetPath = getFileNameByDialog(m_rawFeaturePath);
	if (targetPath.isEmpty()) {
		return;
	}
	ui->m_edtRawPath->setText(targetPath);
	onRawPathChanged();
}

void RetrievalConfig::write2Sets()
{
	qDebug() << m_topK << m_imageLibPath << m_binaryFeaturePath << m_rawFeaturePath;
	m_config.modify_element("top_k", m_topK);
	m_config.modify_element("img_lib", m_imageLibPath);
	m_config.modify_element("bin_path", m_binaryFeaturePath);
	m_config.modify_element("raw_path", m_rawFeaturePath);
}

void RetrievalConfig::clearSets()
{
	m_topK = 10;
	m_imageLibPath = m_binaryFeaturePath = m_rawFeaturePath = "";
	write2Sets();
}

void RetrievalConfig::readFromSets()
{
	m_config.decode_element(&(m_config["top_k"]), m_topK);
	m_config.decode_element(&(m_config["img_lib"]), m_imageLibPath);
	m_config.decode_element(&(m_config["bin_path"]), m_binaryFeaturePath);
	m_config.decode_element(&(m_config["raw_path"]), m_rawFeaturePath);
}

void RetrievalConfig::updateControls()
{
	ui->m_spinBox->setValue(m_topK);
	ui->m_edtLibPath->setText(m_imageLibPath);
	ui->m_edtBinPath->setText(m_binaryFeaturePath);
	ui->m_edtRawPath->setText(m_rawFeaturePath);
	update();
}

QString RetrievalConfig::retrievalConfigPath()
{
	QString path = QCoreApplication::applicationDirPath();
	path = QDir::toNativeSeparators(path + QDir::separator() + "config");
	return path;
}

void RetrievalConfig::onBtnOk()
{
	write2Sets();
	//updateControls();
	close();
}

void RetrievalConfig::onBtnCancel()
{
	readFromSets();
	updateControls();
	close();
}

void RetrievalConfig::onBtnReset()
{
	clearSets();
	updateControls();
}