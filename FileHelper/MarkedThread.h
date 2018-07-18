#ifndef MARKED_THREAD_H
#define MARKED_THREAD_H

#include <QObject>
#include <functional>
#include <QThread>
#include <QFileInfo>
#include <QDir>
#include <QTimer>

// pair detail should be:
//      [src-file]   ------>   [des-file]
//      [src-dir]    ------>   [des-dir]
//      [paths you choose] ------> [null] ==> for delete/scan operation

typedef QPair<QString, QString> HandlePair;
typedef QList<QPair<QString, QString>> HandlePairs;

class MarkedThread : public QThread
{
    Q_OBJECT
public:
    qint64 m_id;
    qint64 m_totalSize;

public:
    MarkedThread(qint64 id, const QStringList &dirs);
    ~MarkedThread();

    QStringList listFiles(const QString &sourceFolder, const QString& copyToFolder);

    QStringList scanFiles(const HandlePairs &handlePairs);

protected:
    MarkedThread(qint64 id);

signals:
    void fileSizeFlush(qint64 id, qint64 tempFileSize);
    void scanFinished(qint64 id, qint64 totleSize, QStringList files);
    void threadFinished(qint64);

private slots:
    void onThreadFinished();

protected:
    virtual void main();
    void run();

private:
    void scanFiles();

private:
    qint64 m_fileSizeTemp;
    const qint64 SIZEHINTSTEP = 1024*1024;

    QStringList m_directorys;
};

#endif // MARKED_THREAD_H
