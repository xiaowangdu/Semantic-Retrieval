#include "QMessageBoxComponent.h"
#include "ui_QMessageBoxComponent.h"
#include <QLabel>
#include <QDebug>

QMessageBoxComponent::QMessageBoxComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMessageBoxComponent)
{
    ui->setupUi(this);

    connect(ui->btnOverwrite, SIGNAL(stateChanged(int)), this, SLOT(btnOverwriteCheck(int)));
    connect(ui->btnSkip, SIGNAL(stateChanged(int)), this, SLOT(btnSkipCheck(int)));
}

QMessageBoxComponent::~QMessageBoxComponent()
{
    delete ui;
}

void QMessageBoxComponent::setContent(const QString &text)
{
    ui->qt_msgbox_label->setText(text);
}

QString QMessageBoxComponent::text()const
{
    return ui->qt_msgbox_label->text();
}

bool QMessageBoxComponent::skip()const
{
    return ui->btnSkip->isChecked();
}

bool QMessageBoxComponent::overwrite()const
{
    return ui->btnOverwrite->isChecked();
}

void QMessageBoxComponent::btnOverwriteCheck(int state)
{
    if(state == Qt::Checked){
        ui->btnSkip->setCheckState(Qt::Unchecked);
    }
}

void QMessageBoxComponent::btnSkipCheck(int state)
{
    if(state == Qt::Checked){
        ui->btnOverwrite->setCheckState(Qt::Unchecked);
    }
}
