#ifndef TRAINING_H
#define TRAINING_H

#include <QWidget>

class TrainingConfig;
class QProcess;

namespace Ui {
class Training;
}

class Training : public QWidget
{
    Q_OBJECT

public:
    explicit Training(QWidget *parent = 0);
    ~Training();
	void closeEvent(QCloseEvent *ev);

private slots:
	void onBtnConfig();
	void onBtnPrepareTrain();
	void onBtnRunCommand();
	void onProcessFinished(int);

private:
    Ui::Training *ui;
	TrainingConfig *m_trainConfig;

	QProcess *m_poc;
};

#endif // TRAINING_H
