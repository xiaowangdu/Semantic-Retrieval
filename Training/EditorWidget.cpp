#include "EditorWidget.h"
#include "ui_EditorWidget.h"
#include "EditorHighLighter.h"
#include "../utility/MacroDef.h"
#include "../Common/CommonFunctions.h"
#include <QDebug>
#include <QTextCursor>
#include <QMessageBox>
#include <QTimer>

EditorWidget::EditorWidget(TrainWidget *parent) :
	TrainWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);

	SINGLE_SLOT_CONNECT(ui->m_save, clicked(), this, onSave());
	SINGLE_SLOT_CONNECT(ui->m_openFile, clicked(), this, onOpenFile());
	SINGLE_SLOT_CONNECT(ui->m_plainTextEdit, modificationChanged(bool), this, onTextChanged(bool));

	// test
	loadFile("D:/Tools/Caffe/matlab/demo/examples/Caltech256/train_CALTECH256_48.prototxt");
}

EditorWidget::~EditorWidget()
{
    delete ui;
}

bool EditorWidget::loadFile(const QString &name)
{
	QFile file(name);
	if (!file.exists()) {
		return false;
	}

	if(!file.open(QFile::ReadOnly)){
		return false;
	}
	QString content = QString::fromUtf8(file.readAll());
	ui->m_plainTextEdit->setPlainText(content);
	file.close();

	stateHint("open success.");
	m_currentFilename = name;
	if (ui->m_lineEdit->text().isEmpty()) {
		ui->m_lineEdit->setText(m_currentFilename);
	}
	return true;
}

void EditorWidget::stateHint(const QString &tip, bool clear)
{
	ui->m_fileState->setText(tip);
	if(clear) QTimer::singleShot(3000, this, SLOT(tipClear()));
}

void EditorWidget::closeEvent(QCloseEvent *ev)
{
	TrainWidget::closeEvent(ev);
}

void EditorWidget::onBtnOk()
{
	close();
}

void EditorWidget::onBtnCancel()
{
	close();
}

void EditorWidget::onBtnApply()
{

}

void EditorWidget::tipClear()
{
	ui->m_fileState->setText("");
}

void EditorWidget::onSave()
{
	qDebug() << "onSave";
	Q_ASSERT(!m_currentFilename.isEmpty());
	if (!ui->m_plainTextEdit->save(m_currentFilename)) {
		QString msg = QString("Save file: %1 failed.").arg(m_currentFilename);
		QMessageBox::warning(this, "Attention", msg, QMessageBox::Ok);
	}
	else {
		stateHint("save success.");
	}
}

void EditorWidget::onOpenFile()
{
    qDebug() << "onOpenFile";
	QString filename = openFileDialog(".", "*.prototxt", "Proto");
	if (filename.isEmpty()) {
		return;
	}

	ui->m_lineEdit->setText(filename);
	loadFile(filename);
}

void EditorWidget::onTextChanged(bool changed)
{
	qDebug() << "onTextChanged" << changed;
	setDirty(changed);
	if (dirty()) {
		stateHint("have changed.", false);
	}
	else {
		tipClear();
	}
}

bool EditorWidget::dirty()const
{
	return m_dirty == true;
}
void EditorWidget::setDirty(bool state)
{
	m_dirty = state;
}
