#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QWidget>
#include <QPixmap>

class ImageLabel : public QWidget
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);

    void drawImage(const QPixmap& pixmap);
    void drawIcon(const QIcon& icon);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QSize minDistance(const QSize &centre, const QList<QSize> &sizeList);

private:
    QPixmap m_pixmap;
};

#endif // IMAGELABEL_H
