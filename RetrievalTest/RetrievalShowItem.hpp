#pragma once
#include "../Widgets/SimpleCanvas.hpp"

class QPainter;
	
namespace RetrievalCanvas {
	class RetrievalShowItem : public SimpleCanvas {
		Q_OBJECT

	public:
		RetrievalShowItem(QWidget * parent = Q_NULLPTR);
		~RetrievalShowItem();

		bool selected() const;
		void setSelected(bool state);

	protected:
		void paintEvent(QPaintEvent *event);
		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);
		//void resizeEvent(QResizeEvent *event);

	private:
		qreal caculateScale(const QSize cansize);

	private:
		QPainter *m_painter;
		bool hovered = false;
		bool m_selected = false;
	};
}