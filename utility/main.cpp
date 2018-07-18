//#define DEBUG

#include <QtCore/QCoreApplication>
#include "Serializable.h"
#include "MacroDef.h"
#include "Settings.hpp"
#include "../Common/Exception.hpp"
#include "Constants.hpp"
#include "UMath.h"
#include "TypeAdapter.h"
#include <QRect>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QUrl>
#include <QVector>
#include "../LabelImage/Lib.h"
#include "Downloader.hpp"
#include "TyperLimits.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	/*
	QVector<QAction *> q;
	QVector<QMenu *> q2;
	QAction * p;

	IS_ALLOWED_TYPE_CHECK(q2);
	IS_ALLOWED_TYPE_CHECK(q);
	QString text = "lkj";
	QByteArray hashcode = QCryptographicHash::hash(text.toLocal8Bit(), QCryptographicHash::Sha256);
	qDebug() << sizeof(double);
	hashcode = hashcode.left(4);
	qDebug() << uchar(hashcode[0]);
	int r = uchar(hashcode[0]);
	int g = uchar(hashcode[1]);
	int b = uchar(hashcode[2]);
	qDebug() << "R:" << r << "G:" << g << "B:" << b;
	*/
	//IS_ALLOWED_TYPE_CHECK(p);

//	printlimit(p);
	/*
	for (int i = 0; i < sizeof(actions) / sizeof(Action); i++) {
		actions[i].tip = "oop";
		qDebug() << actions[i].text << " " << actions[i].tip;
	}
	qDebug() << sizeof(actions);
	qDebug() << sizeof(Action);
*/

	Downloader downloader;
	downloader.downloadFileFromURL(QUrl("https://pic4.zhimg.com/2ef44eb8d73583885f5ec74c70289bfd_r.jpg"));

	downloader.downloadFileFromURL(QUrl("https://pic4.zhimg.com/2ef44eb8d73583885f5ec74c70289bfd_r.jpg"));

	/*
	// serializable test
	QRect rc(100, 200, 11, 16);
	QVector<QRect> mrc;
	mrc.append(rc);
	mrc.append(rc);
	mrc.append(rc);
	mrc.append(rc);
	mrc.append(rc);
	mrc.append(rc);
	mrc.append(rc);
	rc.setHeight(981);

	Settings sets;
	sets.new_element("Hello0", QString("C++11 is a version of the standard for the programming language C++"), 77, 9, 12.34);
	sets.new_element("Hello1", QString("It was approved by International Organization for Standardization (ISO)"), mrc, rc);
	sets.new_element("Hello2", QString("C++11 was published as ISO/IEC 14882:2011"));
	//sets.deleteElement("Hello2");

	sets.modify_element("Hello2", 67, QString("78"));
	qDebug() << sets["Hello2"].toInt();

	Settings sets_c;
	sets_c = sets;

	sets_c.save("F:/workspace/spyder_prj_test/data/hello&.dat");
	//sets.save();

	//sets.saveAsText("F:/workspace/spyder_prj_test/data/hello&.txt");
	Settings sets_b;
	sets_b.load("F:/workspace/spyder_prj_test/data/hello&.dat");
	//sets_b.load();

	QRect vv;
	QVector<QRect> bb;
	QString ss;
	QByteArray by = sets_b["Hello1"];
	sets_b.decode_element(&by, ss, bb, vv);
	qDebug() << ss;

	for (int i = 0; i < bb.size(); i++) {
		qDebug() << bb[i].x() << bb[i].y() << bb[i].width() << bb[i].height();
	}

	qDebug() << vv.x() << vv.y() << vv.width() << vv.height();

	int modify;
	QString yfidom;
	QByteArray by2 = sets_b["Hello2"];
	sets_b.decode_element(&by2, modify, yfidom);
	qDebug() << modify << yfidom;
	*/
	
	/*
	QString s("888888fdg888");
	QByteArray *bd = serializable(s);
	serializable(s, "F:/workspace/spyder_prj_test/data/hello.dat");

	QRect r1;
	QString t;
	QVector<QRect> dmrc;
	if (deserializable(t, bd) && deserializable(t, "F:/workspace/spyder_prj_test/data/hello.dat")) {
		for (int i = 0; i < dmrc.size(); i++) {
			qDebug() << dmrc[i].x() << dmrc[i].y() << dmrc[i].width() << dmrc[i].height();
		}
		
		qDebug() << t;
	}
	delete bd;
	*/
	/*
#ifdef DEBUG
	Widget w1;
	w1.create();
	w1.print();
	//Widget w2(w1);
	//w2.print(); //crash
	QPointF *p = w1.makePoint();
	qDebug() << p->y();
	delete p;

#endif*/
	/*
	TypeAt<0, typelist>::type s = 9;
	testType(s);
	*/

	//testpp(8);
	/*
	Settings dict;
	dict["key"] = "klkl";
	dict["keey"] = "klfl";
	dict["key2"] = "klkl";

	QString gg = dict["key2"];

	dict.save("F:/workspace/spyder_prj_test/data/hello.srd");

	Settings t;
	t.load("F:/workspace/spyder_prj_test/data/hello.srd");
	//t.dprint();
	*/
	/*
	Settings s;
	s["key"] = "klkl";
	s["key"] = "klfl";
	s["key2"] = "klkl";

	qDebug() << (s["key2"].value());
	qDebug() << (s["key"].value());
	s.saveAsText("F:/workspace/spyder_prj_test/data/hello.txt");
	*/
	/*
	qDebug() << INT32MAX;
	qDebug() << FLOATMAX;
	qDebug() << FLOATMIN;
	
	QFileInfo fileinfo("F:/workspace/spyder_prj_test/ui.txt");
	//const QString imgfolderpath = os.path.dirname(imagePath);
	qDebug() << fileinfo.fileName();
	qDebug() << fileinfo.absoluteDir().absolutePath();
	qDebug() << fileinfo.absoluteDir().dirName();

	QVector<qreal> p;
	p.push_back(1); p.push_back(12);
	QVector<qreal> q;
	q.push_back(1); q.push_back(2);
	QVector<qreal> m;
	m.push_back(13); m.push_back(2);

	QVector<QVector<qreal > > t;
	t.append(p); t.append(m); t.append(p); t.append(q);



	QVector<qreal> ar = MinArray(t);
	for (int i = 0; i < ar.size(); i++) {
		qDebug() << ar[i];
	}
	*/

	/*
	try {
		throw new LabelFileError();
	}
	catch (LabelFileError &e) {
		e.raise();
	}
	*/

	return a.exec();
}
