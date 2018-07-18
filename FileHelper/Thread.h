#ifndef THREAD_H
#define THREAD_H

#include "MarkedThread.h"
#include <QClipboard>
#include <QUrl>

class PasteThread : public MarkedThread
{
    Q_OBJECT
public:
    PasteThread(qint64 id, HandlePairs &handlePairs, bool overwrite);

signals:
    void processProgress(qint64 id, qint64 bytesProcessed, qint64 bytesTotal);

public slots:
    void sendProcessProgressChangeMsg(qint64 bytesProcessed, qint64 bytesTotal);


protected:
    void main();


private:
    bool m_overwriteState;
    qint64 m_fileSizeAlreadyDone;

    HandlePairs m_handlePairs;
};


class CutPasteThread : public PasteThread
{
    Q_OBJECT
public:
    CutPasteThread(qint64 id, HandlePairs &handlePairs, const QList<QUrl>& clipboardUrls, bool overwrite);

signals:
    void requestClearClipboard();

public slots:
    void onGlobalClipboardChange(QClipboard::Mode mode);

protected:
    void main();


private:
    void deleteDir(const HandlePairs &pairs);

private:
    bool m_globalClipboardChanged;
    QList<QUrl> m_currentClipboardUrls;

    bool m_overwriteState;
    qint64 m_fileSizeAlreadyDone;

    HandlePairs m_handlePairs;
};

class DeleteThread : public MarkedThread
{
    Q_OBJECT
public:
    DeleteThread(qint64 id, const QStringList &files);

signals:
    void deleteProgress(qint64 id, const QString &currrentFileName, qint64 bytesLeave, qint64 totalBytes);

//public slots:
//    void sendProcessProgressChangeMsg(qint64 bytesProcessed, qint64 bytesTotal);


protected:
    void main();

private:
    void deleteDir(const QStringList &dirs);

private:
    qint64 m_fileSizeAlreadyDone;

    QStringList m_filesDel;

};



#endif // THREAD_H
