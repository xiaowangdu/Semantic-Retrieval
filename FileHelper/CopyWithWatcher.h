#ifndef COPYWITHWATCHER_H
#define COPYWITHWATCHER_H

#include <QObject>

class CopyWithWatcher : public QObject
{
    Q_OBJECT
public:
    CopyWithWatcher(QObject *parent = 0);

    bool copy(const QString &sourceFile, const QString &destFile, bool overwrite = false);

signals:
    void copyProgress(qint64 bytesCopied, qint64 bytesTotal);

};

#endif // COPYWITHWATCHER_H
