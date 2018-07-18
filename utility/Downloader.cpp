#include "Downloader.hpp"
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QNetworkReply>

Downloader::Downloader(QObject * parent) 
	: QObject(parent) 
{
	m_file = new QFile();
	m_netManager = new QNetworkAccessManager();
	connect(m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadFinished(QNetworkReply *)));
}

Downloader::~Downloader() 
{
	delete m_netManager;
	delete m_file;
}

void Downloader::downloadFileFromURL(const QUrl &url, const QString &filePath)
{
	if (busy()) {
		return;
	}

	QString path = filePath;
	if (path.isEmpty()) {
		path = QCoreApplication::applicationDirPath();
		path = QDir::toNativeSeparators(path + QDir::separator() + "tmp" + QDir::separator() + "test.jpg");
	}

	m_file->setFileName(path);
	m_file->open(QIODevice::WriteOnly);
	m_reply = m_netManager->get(QNetworkRequest(url));
	connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64)));

	setBusy(true);
}

bool Downloader::busy()
{
	return m_busy == true;
}

void Downloader::onDownloadFinished(QNetworkReply *reply)
{
	bool status = true;
	if (m_reply->error()) {
		QMessageBox::critical(NULL, "Request erorr", m_reply->errorString(), QMessageBox::Yes, QMessageBox::Yes);
		status = false;
	}

	m_file->flush();
	m_file->close();
	reply->deleteLater();

	emit downloadComplete(status);
	setBusy(false);
}

void Downloader::setBusy(bool b)
{
	m_busy = b;
}

void Downloader::downloadProgress(qint64 bytes, qint64 totalbytes)
{
	if (m_reply->error()){
		qDebug() << "ERROR!";
		qDebug() << m_reply->errorString();
	}
	else{
		qDebug() << m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
		qDebug() << m_reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
		qDebug() << m_reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
		qDebug() << m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		qDebug() << m_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
		qDebug() << m_reply->isFinished();

		m_file->write(m_reply->readAll());
		emit currentProgressChanged(bytes, totalbytes);
	}
}