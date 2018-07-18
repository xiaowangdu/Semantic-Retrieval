#pragma once
#include <QWidget>

class SimpleCanvas : public QWidget {
	Q_OBJECT

public:
	SimpleCanvas(QWidget * parent = Q_NULLPTR);
	~SimpleCanvas();
	void loadPixmap(const QString &fileName);
	QPixmap *getPixmap() const;

	QSize sizeHint()const;
	QSize minimumSizeHint() const;

	void setScale(qreal scale);
	qreal getScale()const;

protected:
	void paintEvent(QPaintEvent *event);
	//void enterEvent(QEvent *event);
	//void leaveEvent(QEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

signals:
	void zoomRequest(int);
	void mouseDoubleClicked(const QString &);

private:
	QPointF offsetToCenter();

private:
	QString m_currentImagePath = "";
	QPixmap *m_pixmap;

	qreal m_scale = 1.0;

	QPainter *m_painter;
};
