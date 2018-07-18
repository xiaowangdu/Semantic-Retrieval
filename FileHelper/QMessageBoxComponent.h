#ifndef QMESSAGEBOXCOMPONENT_H
#define QMESSAGEBOXCOMPONENT_H

#include <QWidget>

class QLabel;

namespace Ui {
class QMessageBoxComponent;
}

class QMessageBoxComponent : public QWidget
{
    Q_OBJECT

public:
    explicit QMessageBoxComponent(QWidget *parent = 0);
    ~QMessageBoxComponent();

    void setContent(const QString &text);
    QString text()const;

    bool skip()const;
    bool overwrite()const;

private slots:
    void btnOverwriteCheck(int state);
    void btnSkipCheck(int state);

private:
    Ui::QMessageBoxComponent *ui;
};

#endif // QMESSAGEBOXCOMPONENT_H
