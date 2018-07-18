#ifndef LMDBGENERATOR_H
#define LMDBGENERATOR_H

#include <QWidget>
#include "../utility/Settings.hpp"

namespace Ui {
class LMDBGenerator;
}
class QProcess;

class LMDBGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit LMDBGenerator(QWidget *parent = 0);
    ~LMDBGenerator();

private slots:
	void selectToolDir();
	void selectRootDir();
	void selectListFilePath();
	void selectOutputDBPath();
	void onToolPathChanged();
	void onRootPathChanged();
	void onListFileChanged();
	void onOutputDBPathChanged();
	void startMakeDB();
	void setDbName();
	void onProcessFinished(int);

protected:
	void closeEvent(QCloseEvent *event);

private:
	QString getFileNameByDialog(const QString &path);
	void write2Sets();
	void flush();
	void readFromSets();
	void updateControls();
	QString makeCommandString();
	QString openDirDialog(const QString &defaultOpenDirPath);

private:
    Ui::LMDBGenerator *ui;

	int m_resizeWidth = 256;
	int m_resizeHeight = 256;
	bool m_resized = false;

	QString m_toolPath = "";
	QString m_rootPath = "";
	QString m_inputFilePath = "";
	QString m_outputDBPath = "";
	QString m_outputDBName = "";

	Settings m_config;
	QProcess *m_poc;

	static const QString BAXKEND;
};

#endif // LMDBGENERATOR_H
