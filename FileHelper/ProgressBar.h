#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>

namespace Ui {
class ProgressBar;
}

class ProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBar(qint64 id, QWidget *parent = 0);
    ~ProgressBar();

    void setTitle(const QString &title);
    void setContent(const QString &content);
    void setMessage(const QString &title, const QString &content);
    QProgressBar * progressBar()const;

signals:
    void cancelEvent(qint64);

private slots:
    void sendCancelEvent();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ProgressBar *ui;
    qint64 m_id;
};

#endif // PROGRESSBAR_H
