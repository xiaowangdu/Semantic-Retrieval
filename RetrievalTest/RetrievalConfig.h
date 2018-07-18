#ifndef RETRIEVALCONFIG_H
#define RETRIEVALCONFIG_H

#include <QWidget>
#include "../utility/Settings.hpp"

namespace Ui {
class RetrievalConfig;
}

class RetrievalConfig : public QWidget
{
    Q_OBJECT

public:
    explicit RetrievalConfig(QWidget *parent = 0);
    ~RetrievalConfig();
	
	unsigned int getTopK()const;
	void setDefaultTopK(unsigned int k);
	QString getImageLib()const;
	void setDefaultImageLibPath(const QString &path);
	QString getBinFeaturePath()const;
	void setDefaultBinFeaturePath(const QString &path);
	QString getRawFeaturePath()const;
	void setDefaultRawFeaturePath(const QString &path);
	static bool isValidFile(const QString &filename);
	static QString retrievalConfigPath();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void onSpinboxValueChanged(int);
	void onLibPathChanged();
	void onBinPathChanged();
	void onRawPathChanged();
	void selectLibDir();
	void selectBinFile();
	void selectRawFeatureFile();
	void onBtnOk();
	void onBtnCancel();
	void onBtnReset();
	
private:
	bool askingYesDialog(const QString &msg);
	QString getFileNameByDialog(const QString &path);
	void write2Sets();
	void clearSets();
	void readFromSets();
	void updateControls();
	

private:
    Ui::RetrievalConfig *ui;

	unsigned int m_topK = 10;
	QString m_imageLibPath = "";
	QString m_binaryFeaturePath = "";
	QString m_rawFeaturePath = "";

	Settings m_config;
};

#endif // RETRIEVALCONFIG_H
