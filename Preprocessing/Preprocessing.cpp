#include "Preprocessing.h"
#include "GeneratedFiles\ui_Preprocessing.h"
#include "../Widgets/SimpleCanvas.hpp"
#include "../utility/MacroDef.h"
#include "../Common/CommonFunctions.h"
#include <QFileInfo>
#include "ProcessLib.h"

Preprocessing::Preprocessing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preprocessing)
{
    ui->setupUi(this);

	m_originImageView = new SimpleCanvas();
	ui->m_scrollOrgView->setWidget(m_originImageView);
	ui->m_scrollOrgView->setWidgetResizable(true);

	m_processedImageView = new QLabel();
	ui->m_scrollProcessedView->setWidget(m_processedImageView);
	ui->m_scrollProcessedView->setWidgetResizable(true);

    //ui->quickWidget->setSource(QUrl("qrc:/content/qml/preprocessing_button.qml"));

	SINGLE_SLOT_CONNECT(ui->m_btnShowOrg, clicked(), this, onBtnOrgShow());
	SINGLE_SLOT_CONNECT(ui->m_edtPath, editingFinished(), this, onOriginImageChanged());
	SINGLE_SLOT_CONNECT(ui->m_btnOpen, clicked(), this, selectOriginImage());

	SINGLE_SLOT_CONNECT(ui->m_btnGray, clicked(), this, onBtnGray());
	SINGLE_SLOT_CONNECT(ui->m_btnHistogram, clicked(), this, onBtnHistogram());
}

Preprocessing::~Preprocessing()
{
    delete ui;
}

void Preprocessing::closeEvent(QCloseEvent *ev)
{

}


void Preprocessing::onBtnOrgShow()
{
	if (m_orgImage.isEmpty()) {
		return;
	}
	m_originImageView->loadPixmap(m_orgImage);

	if (m_originImageView->getPixmap()) {
		m_originImageView->setScale(1);
		m_originImageView->repaint();
	}
}

void Preprocessing::onOriginImageChanged()
{
	QString filename = ui->m_edtPath->text();
	if (filename.isEmpty()) {
		return;
	}

	QFileInfo fileinfo(filename);
	bool check = getSupportedImgExtensions().contains(fileinfo.suffix()) & fileinfo.exists();

	if (!check) {
		QString msg = QString("'%1' is not a valid image, continue anyway?").arg(filename);
		if (!askingDialog(this, msg)) {
			return;
		}
	}

	m_orgImage = filename;
}

void Preprocessing::selectOriginImage()
{
	QString filename = openImageDialog(this, "Choose Image", m_orgImage);
	if (filename.isEmpty()) {
		return;
	}

	ui->m_edtPath->setText(filename);
	onOriginImageChanged();
}
void Preprocessing::onBtnGray()
{
	if (m_orgImage.isEmpty()) {
		return;
	}

	Mat img = read2Gray(m_orgImage);
	m_processedImageView->setAlignment(Qt::AlignCenter);
	m_processedImageView->setPixmap(cvMatToQPixmap(img));

	repaint();
}

void Preprocessing::onBtnHistogram()
{
	

	if (m_orgImage.isEmpty()) {
		return;
	}

	Mat img = imread(m_orgImage.toStdString().c_str());
	img = histogramImage(img);
	m_processedImageView->setPixmap(cvMatToQPixmap(img));

	repaint();
}