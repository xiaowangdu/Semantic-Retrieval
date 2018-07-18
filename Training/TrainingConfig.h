#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QStyledItemDelegate>

class QTreeWidgetItem;
class TrainWidget;
class GeneralConfig;

namespace Ui {
class TrainingConfig;
}

class ConfigsItemDelegate : public QStyledItemDelegate {
public:
    ConfigsItemDelegate(QObject* parent);

    QSize sizeHint(const QStyleOptionViewItem& option,
             const QModelIndex& index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
         const QModelIndex& index) const;

    static void drawHeader(QPainter* painter, const QRect& rect,
                               const QFont& font, const QPalette& palette,
                               const QString& text);

private:
    static const int kBarThickness;
    static const int kBarMarginTop;
};

class TrainingConfig : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingConfig(QWidget *parent = 0);
    ~TrainingConfig();
	void closeEvent(QCloseEvent *ev);

	GeneralConfig * generalConfig();

    QTreeWidgetItem* addCategory(const QString& name);
    void addPage(TrainWidget* page, QTreeWidgetItem* parent);

public slots:
    void changePageByItem(QTreeWidgetItem*, QTreeWidgetItem*);

private:
    Ui::TrainingConfig *ui;
    QMap<QTreeWidgetItem *, TrainWidget*> m_pages;

	const int CONFIG_WINS = 2;
};

#endif // TREEWIDGET_H
