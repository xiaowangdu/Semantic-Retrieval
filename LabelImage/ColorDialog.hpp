#pragma once
#include <QColorDialog>
class QPushButton;
class QAbstractButton;

//please reference:https://github.com/Willib/color-picker

class ColorDialog : public QColorDialog {
	Q_OBJECT

public:
	ColorDialog(QWidget *parent = 0);
	~ColorDialog();

	QColor getColor(const QColor &color, const QString &title, const QColor &defaultcolor = QColor(""));

private:
	QPushButton *m_pushBt;

	QColor m_defaultColor = QColor(125, 0, 0);

private slots:
	void checkRestore();
	
};
