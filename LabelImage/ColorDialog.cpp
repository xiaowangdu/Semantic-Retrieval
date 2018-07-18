#include "ColorDialog.hpp"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QAbstractButton>
#include <QDebug>

ColorDialog::ColorDialog(QWidget *parent) : QColorDialog(parent) 
{

	setOption(QColorDialog::ShowAlphaChannel);
	setOption(QColorDialog::DontUseNativeDialog);

	//problem solve: https://www.zhihu.com/question/34250349
	QDialogButtonBox *btBox = this->findChild<QDialogButtonBox *>();
	btBox->addButton(QDialogButtonBox::RestoreDefaults);

	m_pushBt = btBox->button(QDialogButtonBox::RestoreDefaults);

	m_defaultColor = QColor(125, 0, 0);
	setCurrentColor(m_defaultColor);
	QObject::connect(m_pushBt, SIGNAL(clicked()), this, SLOT(checkRestore()));
}

ColorDialog::~ColorDialog() 
{
	
}
QColor ColorDialog::getColor(const QColor &color, const QString &title, const QColor &defaultcolor)
{
	if (!title.isEmpty()) {
		setWindowTitle(title);
	}

	if (color.isValid()) {
		setCurrentColor(color);
	}

	return exec() ? currentColor() : QColor();
}

void ColorDialog::checkRestore()
{
	if (m_defaultColor.isValid()) {
		setCurrentColor(m_defaultColor);
	}
}