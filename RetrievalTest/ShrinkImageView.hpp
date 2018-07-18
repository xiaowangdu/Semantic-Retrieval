#pragma once
#include <QTableWidget>

class ShrinkImageView : public QTableWidget {
	Q_OBJECT

public:
	ShrinkImageView(QWidget * parent = Q_NULLPTR);
	~ShrinkImageView();

protected:
	void resizeEvent(QResizeEvent *event);

private:
	
};
