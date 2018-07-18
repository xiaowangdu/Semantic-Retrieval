#pragma once
#include <QWidget>
#include <QMenu>
#include <QPair>
#include <QException>
#include "Shape.hpp"
#include "../utility/Constants.hpp"
#include "../utility/MacroDef.h"

class Canvas : public QWidget {
	Q_OBJECT

		DEFINE_CLASS_PROPERTY_DEFAULT(bool, Verified, false);
public:
	enum WinMode{
		CREATE, EDIT
	};

	Canvas(QWidget * parent);
	~Canvas();

	void loadPixmap(QPixmap &pixmap);
	void loadPixmap(const QString &fileName);
	void loadShapes(const QVector<Shape *> shapes);
	QPixmap *getPixmap()const;
	QPair<QMenu *, QMenu *> getMenu() { return m_menus; }

	QSize sizeHint()const;
	QSize minimumSizeHint() const;

	void setDrawingColor(const QColor &color);
	bool isVisible(Shape * const shape);
	bool drawing()const;
	bool editing()const;
	void setEditing(const bool value = true);
	void unHighlight();
	void deSelectShape();
	void setHiding(const bool value = true);
	Shape * deleteSelected();
	Shape * copySelectedShape();
	void boundedShiftShape(Shape * shape);
	void selectShape(Shape * const shape);
	Shape *getSelectedShape()const;
	void selectShapePoint(const QPointF &point);
	void calculateOffsets(Shape & shape, const QPointF & point);
	bool outOfPixmap(const QPointF &p);
	bool boundedMoveShape(Shape & shape, const QPointF & pos);
	void boundedMoveVertex(const QPointF & pos);
	Shape * setLastLabel(const QString &text, const QColor &linecolor = QColor(), const QColor & fillcolor = QColor());
	bool closeEnough(const QPointF &p1, const QPointF &p2);
	QPointF & intersectionPoint(const QPointF & p1, const QPointF & p2);
	QVector<qreal> intersectingEdges(const QPointF &x1y1, const QPointF &x2y2, QVector<QPointF> &points);
	void resetState();
	void setShapeVisible(Shape *shape, bool value);
	QVector<Shape *> getShapes() const;
	void clearAllShapes();
	void clearShape(Shape * const shape);
	void setScale(qreal);
	qreal getScale()const;
	void restoreCursor();
	void resetAllLines();

signals:
	void zoomRequest(int);
	void scrollRequest(int, Qt::Orientation);
	void newShape();
	void selectionChanged(bool);
	void shapeMoved();
	void drawingPolygon(bool);
	void mousePositionChanged(int, int);

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void focusOutEvent(QFocusEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	QCursor *currentCursor();
	void overrideCursor(const QCursor &cursor);
	void moveOnePixel(const QString &direction);
	bool moveOutOfBound(const QPointF &step);
	bool selectedVertex();
	QPointF transformPos(const QPointF &point);
	QPointF offsetToCenter();
	void finalise();
	bool canCloseShape();
	void endMove(const bool copy = false);
	void hideBackroundShapes(const bool value);
	void handleDrawing(const QPointF &pos);
	void assertNoRepeatShapeWith(Shape *shape);

private:
	QWidget *m_loader;

	QPixmap *m_pixmap;
	QVector<Shape *> m_boxShapes;

	Shape *m_currentBoxShape;
	Shape *m_selectedBoxShape;
	Shape *m_selectedBoxShapeCopy;
	Shape *m_hoveredShape;
	//Line shape can't be deleted during the life time.
	Shape *m_lineShape;

	QPainter *m_painter;
	QCursor m_cursor;

	QColor m_drawingLineColor;
	QColor m_drawingRectColor;

	QPointF m_prevPoint;
	QPair<QPointF, QPointF> m_offsets;
	QPair<QMenu *, QMenu *> m_menus;

	int m_hVertexIndex = -1;
	bool m_hideBackround = false;

	QMap<Shape *, bool> m_visible;

	qreal m_epsilon = 11.0;
	qreal m_scale = 1.0;
	WinMode m_mode = EDIT;
};
