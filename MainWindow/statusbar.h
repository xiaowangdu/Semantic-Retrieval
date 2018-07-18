#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QStatusBar>

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    StatusBar(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // STATUSBAR_H
