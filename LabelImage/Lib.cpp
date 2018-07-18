#include "Lib.h"
#include <QDebug>

QRegExpValidator & labelValidator() {
	return QRegExpValidator(QRegExp("^[^ \t].+"));
}

double distance(const QPointF &p) {
	return sqrt(p.x() * p.x() + p.y() * p.y());
}

QIcon newIcon(const QString &iconname) {
	return QIcon(":/" + iconname);
}

//the return object need be delete.
QAction *newAction(const ActionDetail & act, QWidget *whose) {
	QAction *a = new QAction(act.text, whose);
	if (!act.icon.isEmpty()) {
		a->setIcon(newIcon(act.icon));
	}

	if (!act.shortcut.isEmpty()) {
		a->setShortcut(act.shortcut);
	}

	a->setToolTip(act.tip);
	a->setStatusTip(act.tip);

	if (act.checkable) {
		a->setCheckable(true);
	}

	a->setEnabled(act.enabled);
	return a;
}


void listDir(QString path, QStringList &list) {
	QDir dir(path);
	foreach(QFileInfo fileinfo, dir.entryInfoList()){
		if (fileinfo.isFile()){
			list << fileinfo.fileName();
		}
		else{
#if 0
			if (fileinfo.fileName() == "." || fileinfo.fileName() == "..")continue;
			listDir(fileinfo.absoluteFilePath(), list);
#endif
		}
	}
}

QColor generateColorByText(const QString &text) {
	QByteArray hashcode = QCryptographicHash::hash(text.toLocal8Bit(), QCryptographicHash::Sha256);
	hashcode = hashcode.left(4);
	int r = uchar(hashcode[0]);
	int g = uchar(hashcode[1]);
	int b = uchar(hashcode[2]);

	return QColor(r, g, b, 100);
}

QStringList stringArray2List(const QString * array, unsigned int size){
	QStringList slist;

	if (size == 0) {
		return slist;
	}

	for (int i = 0; i < size; i++) {
		slist << array[i];
	}

	return slist;
}

QString formatShortcut(const QString & shortcut) {
	if (shortcut.isEmpty()) {
		return "";
	}
	int index = shortcut.indexOf('+');
	if (index < 0) {
		return "";
	}
	QString m = shortcut.left(index);
	QString k = shortcut.right(shortcut.length() - (index + 1));

	return QString("<b>%1</b>+<b>%2</b>").arg(m).arg(k);
}

QStringList readFileFromTxt(const QString &filename)
{
	QStringList res;

	if (filename.isEmpty()) {
		return res;
	}

	QFileInfo fileinfo(filename);
	if (!fileinfo.exists()) {
		qDebug() << QString("File: %s not exist.").arg(filename);
		return res;
	}

	QFile file(fileinfo.absoluteFilePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return res;
	}

	QTextStream in(&file);
	in.seek(0);
	while (!in.atEnd()) {
		res << in.readLine();
	}

	file.close();
	return res;
}