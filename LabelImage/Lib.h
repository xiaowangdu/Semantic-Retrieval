#ifndef __LIB_H__
#define __LIB_H__

#include <QPointF>
#include <QRegExpValidator>
#include <QIcon>
#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QDir>
#include <QCryptographicHash>
#include "../Common/BaseShape.hpp"
#include "Shape.hpp"
#include "../utility/TyperLimits.h"

class LabelImage;

struct ActionDetail {
	QWidget *parent = NULL;
	QString text;
	QString shortcut;
	QString icon;
	QString tip;
	QString actionKey;
	bool enabled = true;
	bool checkable = false;

	ActionDetail(const QString &text_, const QString &shortcut_, const QString &icon_, const QString &tip_, const QString &key, bool enabled_ = true, bool checkable_ = false)
	{
		text = text_; shortcut = shortcut_; icon = icon_; tip = tip_; actionKey = key; enabled = enabled_; checkable = checkable_;
	}
};

extern QRegExpValidator & labelValidator();

extern double distance(const QPointF &p);

extern QIcon newIcon(const QString &iconname);

extern QAction *newAction(const ActionDetail & act, QWidget *whose);

extern QString formatShortcut(const QString & shortcut);

extern QStringList readFileFromTxt(const QString &filename);

template<typename T1, typename T2>
extern void addActionsIn(T1 powner, T2 &actions) {
	IS_ALLOWED_TYPE_CHECK(actions);
	Q_ASSERT(powner != NULL);
	for (int i = 0; i < actions.size(); i++) {

		if (actions[i] == NULL) {
			qDebug() << actions[i];
			powner->addSeparator();
		}
		else if (bool(qobject_cast<QWidgetAction *>(actions[i]))) {
			powner->addAction(qobject_cast<QWidgetAction *>(actions[i]));
		}
		else if(bool(qobject_cast<QAction *>(actions[i]))){
			powner->addAction(qobject_cast<QAction *>(actions[i]));
		}
		else {
			qDebug() << actions[i] << " Type is not allowed.";
			//qDebug() << QString("(%1) Type is not allowed.").arg(actions[i]);
			Q_ASSERT(0);
		}
	}
}

template<typename T>
extern void addActionsIn(QMenu * powner, T &actions) {
	IS_ALLOWED_TYPE_CHECK(actions);
	Q_ASSERT(powner != NULL);
	for (int i = 0; i < actions.size(); i++) {

		if (actions[i] == NULL) {
			qDebug() << actions[i];
			powner->addSeparator();
		}
		else if (bool(qobject_cast<QWidgetAction *>(actions[i]))) {
			powner->addAction(qobject_cast<QWidgetAction *>(actions[i]));
		}
		else if (bool(qobject_cast<QAction *>(actions[i]))) {
			powner->addAction(qobject_cast<QAction *>(actions[i]));
		}
		else if (bool(qobject_cast<QMenu *>(actions[i]))) {
			powner->addMenu(qobject_cast<QMenu *>(actions[i]));
		}
		else {
			qDebug() << "Type is not allowed.";
			Q_ASSERT(0);
		}
	}
}

extern void listDir(QString path, QStringList &list);

extern QColor generateColorByText(const QString &text);

extern QStringList stringArray2List(const QString * array, unsigned int size);

template<typename T>
extern QMenu *addWinMenu(QMainWindow *parent, const QString &title, T & actions) {
	IS_ALLOWED_TYPE_CHECK(actions);
	Q_ASSERT(parent != NULL);
	QMenu * m = parent->menuBar()->addMenu(title);
	if (actions.size() > 0) {
		addActionsIn(m, actions);
	}

	return m;
}

/*
template<typename T>
extern QMenu *assembleMenu(QMenu *parent, const QString &title, T & actions) {
	IS_ALLOWED_TYPE_CHECK(actions);
	Q_ASSERT(parent != NULL);
	QMenu * m = parent;
	if (actions.size() > 0) {
		addActions(m, actions);
	}

	return m;
}
*/


#endif