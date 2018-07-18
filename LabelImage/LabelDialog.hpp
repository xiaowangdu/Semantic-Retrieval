#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QStringListModel>
#include <QCompleter>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QMouseEvent>
#include <QDebug>

class ListWidget : public QListWidget {
	Q_OBJECT
public:
	ListWidget(QWidget * parent = Q_NULLPTR);
	~ListWidget();

protected:
	void mouseDoubleClickEvent(QMouseEvent * event){
		//qDebug() << "hello";
		emit itemDoubleClicked(currentItem());
		event->accept();
	}
};

class LabelDialog : public QDialog {
	Q_OBJECT

public:
	LabelDialog(const QStringList &listitems, QWidget * parent = Q_NULLPTR);
	~LabelDialog();

	QString popUp(const QString& text = "", bool moved = true);

private:
	QLineEdit * m_lineEdit;
	QStringListModel *m_model;
	QCompleter *m_completer;
	QVBoxLayout *m_layout;
	QDialogButtonBox *m_buttonBox;
	QListWidget *m_listWidget;

private slots:
	void postProcess();
	void validate();
	void listItemDoubleClick(QListWidgetItem *item);
};
