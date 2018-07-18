#include "ProgressBar.h"
#include "ui_ProgressBar.h"
#include "../Common/iconloader.h"
#include "Thread.h"

ProgressBar::ProgressBar(qint64 id, QWidget *parent) :
    QWidget(parent),
    m_id(id),
    ui(new Ui::ProgressBar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));
    connect(ui->m_btnCancel, SIGNAL(clicked()), this, SLOT(sendCancelEvent()));
}

ProgressBar::~ProgressBar()
{
    delete ui;
}
void ProgressBar::sendCancelEvent()
{
    emit cancelEvent(m_id);
}



void ProgressBar::setTitle(const QString &title)
{
     setWindowTitle(title);
}

void ProgressBar::setContent(const QString &content)
{
    ui->m_content->setText(content);
}

void ProgressBar::setMessage(const QString &title, const QString &content)
{
    setWindowTitle(title);
    ui->m_content->setText(content);
}

QProgressBar * ProgressBar::progressBar()const
{
    return ui->m_progressBar;
}

void ProgressBar::closeEvent(QCloseEvent *event)
{
    emit cancelEvent(m_id);
    QWidget::closeEvent(event);
}
