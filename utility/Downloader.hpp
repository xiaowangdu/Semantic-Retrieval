#pragma once
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class Downloader : public QObject {
	Q_OBJECT

public:
	Downloader(QObject * parent = Q_NULLPTR);
	~Downloader();

	void downloadFileFromURL(const QUrl &url, const QString &filePath = "");
	bool busy();

signals:
	void downloadComplete(bool);
	void currentProgressChanged(qint64 bytes, qint64 totalbytes);

private slots:
	void onDownloadFinished(QNetworkReply *reply);
	void downloadProgress(qint64 bytes, qint64 totalbytes);

private:
	void setBusy(bool b);
	


private:
	QFile * m_file;
	bool m_busy = false;

	QNetworkAccessManager *m_netManager;
	QNetworkReply * m_reply;
};
