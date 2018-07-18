#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QWidget>

namespace Ui {
class Preprocessing;
}

class SimpleCanvas;
class QLabel;

class Preprocessing : public QWidget
{
    Q_OBJECT

public:
    explicit Preprocessing(QWidget *parent = 0);
    ~Preprocessing();

	void closeEvent(QCloseEvent *ev);

private slots:
	void onBtnOrgShow();
	void onOriginImageChanged();
	void selectOriginImage();
	void onBtnGray();
	void onBtnHistogram();

private:
    Ui::Preprocessing *ui;

	SimpleCanvas *m_originImageView;
	QLabel *m_processedImageView;
	QString m_orgImage = "";
};

#endif // PREPROCESSING_H
