#include "commonfunctions.h"


void showFileInExplorer(QString const& path)
{

  QProcess::execute("explorer.exe", QStringList()
                                        << "/select,"
                                        << QDir::toNativeSeparators(path));
}

void openInFileBrowser(const QList<QUrl>& urls) {
  QSet<QString> dirs;

  for (const QUrl& url : urls) {
    if (url.scheme() != "file") {
      continue;
    }
    QString path = url.toLocalFile();

    if (!QFile::exists(path)) continue;

    const QString directory = QFileInfo(path).dir().path();
    if (dirs.contains(directory)) continue;
    dirs.insert(directory);
    qDebug() << path;

    showFileInExplorer(path);

  }
}
