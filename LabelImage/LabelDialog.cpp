#include "LabelDialog.hpp"
#include "Lib.h"
#include "../Common/iconloader.h"
#include <QPushButton>
#include <QDebug>

ListWidget::ListWidget(QWidget * parent)
	: QListWidget(parent)
{
	
}

ListWidget::~ListWidget()
{

}

LabelDialog::LabelDialog(const QStringList &listitems, QWidget * parent) 
	: QDialog(parent) 
{
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));

	m_lineEdit = new QLineEdit();
	m_lineEdit->setText("Enter object label");
	//m_lineEdit->setValidator(&labelValidator());

	m_model = new QStringListModel();
	m_model->setStringList(listitems);
	m_completer = new QCompleter();
	m_completer->setModel(m_model);
	m_lineEdit->setCompleter(m_completer);

	m_layout = new QVBoxLayout();
	m_layout->addWidget(m_lineEdit);
	m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	//m_buttonBox->button(QDialogButtonBox::Ok)->setIcon(newIcon("done"));
	//m_buttonBox->button(QDialogButtonBox::Cancel)->setIcon(newIcon("undo"));
	m_layout->addWidget(m_buttonBox);

	m_listWidget = new QListWidget(this);

	if (!listitems.isEmpty()) {
		for (int i = 0; i < listitems.size(); ++i) {
			m_listWidget->addItem(listitems.at(i));
		}
		
	}
	m_layout->addWidget(m_listWidget);
	QObject::connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(listItemDoubleClick(QListWidgetItem *)));
	//QObject::connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listItemClick(QListWidgetItem *)));
	

	QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(validate()));
	QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	
	QObject::connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(postProcess()));

	setLayout(m_layout);
}

LabelDialog::~LabelDialog() 
{
	delete m_lineEdit;
	delete m_model;
	delete m_completer;
}

QString LabelDialog::popUp(const QString& text, bool moved)
{
	m_lineEdit->setText(text);
	m_lineEdit->setSelection(0, text.length());
	m_lineEdit->setFocus(Qt::PopupFocusReason);

	if (moved) {
		move(QCursor::pos());
	}

	return exec() ? m_lineEdit->text() : "";
}

void LabelDialog::postProcess()
{
	qDebug() << "hello postProcess";
	m_lineEdit->setText(m_lineEdit->text());
}

void LabelDialog::validate()
{
	qDebug() << "hello validate";
	if (!m_lineEdit->text().isEmpty() && (m_lineEdit->text() != "Enter object label")) {
		accept();
	}
}

void LabelDialog::listItemDoubleClick(QListWidgetItem *item)
{
	qDebug() << "hello listItemDoubleClick";
	const QString text = item->text();
	m_lineEdit->setText(text);

	validate();
}