#pragma once

#include "TrainWidget.hpp"
#include "../utility/Settings.hpp"
#include "GeneratedFiles/ui_GeneralConfig.h"

class GeneralConfig : public TrainWidget
{
	Q_OBJECT

public:
	GeneralConfig(TrainWidget *parent = Q_NULLPTR);
	~GeneralConfig();
	void closeEvent(QCloseEvent *event);

	QString getRootDir() const;
	QString getToolDir() const;
	QString getTrainDbDir() const;
	QString getTestDbDir() const;
	QString getSolverFile() const;
	QString getWeightsFile() const;
	QString getBinDir() const;
	bool useGPU() const;

public slots:
	void onBtnOk();
	void onBtnCancel();
	void onBtnApply();

private slots:
	void onRootDirChanged();
	void onToolDirChanged();
	void onTrainDbDirChanged();
	void onTestDbDirChanged();
	void onSolverFileChanged();
	void onWeightsFileChanged();
	void onBinDirChanged();

	void selectToolDir();
	void selectRootDir();
	void selectTrainDbDir();
	void selectTestDbDir();
	void selectSolverFile();
	void selectWeightsFile();
	void selectBinDir();

private:
	bool askingYesDialog(const QString &msg);
	QString checkEdtDir(QLineEdit *edit);
	bool isValidFile(const QString &filename);
	QString checkEdtFile(QLineEdit *edit, const QString &type);
	QString selectDir(QString &defaultDir);
	QString getFileNameByDialog(const QString &path, const QString &filter = "*.*");
	void write2Sets();
	void flush();
	void readFromSets();
	void updateControls();

private:
	Ui::GeneralConfig ui;

	QString m_toolDir = "";
	QString m_trainDbDir = "";
	QString m_testDbDir = "";
	QString m_rootDir = "";
	QString m_solverFile = "";
	QString m_weightsFile = "";
	QString m_binDir = "";

	Settings m_config;
};
