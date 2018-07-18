#pragma once
#include <QToolButton>
#include <QToolBar>

class ToolBar : public QToolBar {
	

public:
	ToolBar(const QString &title, QWidget * parent = Q_NULLPTR);
	~ToolBar();

private:
	
};

class ToolButton : public QToolButton {


public:
	ToolButton(QWidget * parent = Q_NULLPTR) {
		m_minSize = QSize(60, 60);
	}
	~ToolButton();

	virtual QSize minimumSizeHint() {
		QSize ms = minimumSizeHint();
		int w1 = ms.width();
		int h1 = ms.height();
		int w2 = m_minSize.width();
		int h2 = m_minSize.height();

		m_minSize.setWidth(qMax(w1, w2));
		m_minSize.setWidth(qMax(h1, h2));
		return m_minSize;
	}

private:
	QSize m_minSize;
};