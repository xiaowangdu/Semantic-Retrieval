#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H
#include <QProcess>
#include <QDir>
#include <QUrl>
#include <QDebug>

extern void showFileInExplorer(QString const& path);

extern void openInFileBrowser(const QList<QUrl>& urls);


#endif // COMMONFUNCTIONS_H
