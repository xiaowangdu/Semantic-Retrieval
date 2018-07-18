#include "TrainingConfig.h"
#include "GeneratedFiles/ui_TrainingConfig.h"
#include "../utility/MacroDef.h"
#include "../Common/iconloader.h"
#include <QFont>
#include <QMap>
#include <QPainter>
#include <QDialogButtonBox>

#include "GeneralConfig.h"
#include "EditorWidget.h"


const int ConfigsItemDelegate::kBarThickness = 2;
const int ConfigsItemDelegate::kBarMarginTop = 3;

ConfigsItemDelegate::ConfigsItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

QSize ConfigsItemDelegate::sizeHint(const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
  const bool is_separator =
      index.data(Qt::UserRole).toBool();
  QSize ret = QStyledItemDelegate::sizeHint(option, index);

  if (is_separator) {
    ret.setHeight(ret.height() * 2);
  }

  return ret;
}

void ConfigsItemDelegate::paint(QPainter* painter,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
  const bool is_separator =
      index.data(Qt::UserRole).toBool();

  if (is_separator) {
    drawHeader(painter, option.rect, option.font,
                                option.palette, index.data().toString());
  } else {
    QStyledItemDelegate::paint(painter, option, index);
  }
}

void ConfigsItemDelegate::drawHeader(QPainter* painter, const QRect& rect,
                                 const QFont& font, const QPalette& palette,
                                 const QString& text)
{
  painter->save();

  // Bold font
  QFont bold_font(font);
  bold_font.setBold(true);
  QFontMetrics metrics(bold_font);

  QRect text_rect(rect);
  text_rect.setHeight(metrics.height());
  text_rect.moveTop(
      rect.top() +
      (rect.height() - text_rect.height() - kBarThickness - kBarMarginTop) / 2);
  text_rect.setLeft(text_rect.left() + 3);

  // Draw text
  painter->setFont(bold_font);
  painter->drawText(text_rect, text);

  // Draw a line underneath
  QColor line_color = palette.color(QPalette::Text);
  QLinearGradient grad_color(text_rect.bottomLeft(), text_rect.bottomRight());
  const double fade_start_end = (text_rect.width()/3.0)/text_rect.width();
  line_color.setAlphaF(0.0);
  grad_color.setColorAt(0, line_color);
  line_color.setAlphaF(0.5);
  grad_color.setColorAt(fade_start_end, line_color);
  grad_color.setColorAt(1.0 - fade_start_end, line_color);
  line_color.setAlphaF(0.0);
  grad_color.setColorAt(1, line_color);
  painter->setPen(QPen(grad_color, 1));
  painter->drawLine(text_rect.left(), text_rect.bottom() + kBarMarginTop,
                    text_rect.right(), text_rect.bottom() + kBarMarginTop);

  painter->restore();
}



TrainingConfig::TrainingConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingConfig)
{
    ui->setupUi(this);
	setWindowIcon(IconLoader::load("semantic_retrieval", IconLoader::Base));

    ui->list->setItemDelegate(new ConfigsItemDelegate(this));

    QTreeWidgetItem* general = addCategory(tr("Train Config"));
	GeneralConfig *firstwidget = new GeneralConfig();
	SINGLE_SLOT_CONNECT(ui->m_btnOk, clicked(), firstwidget, onBtnOk());
	SINGLE_SLOT_CONNECT(ui->m_btnCancel, clicked(), firstwidget, onBtnCancel());
	SINGLE_SLOT_CONNECT(ui->m_btnApply, clicked(), firstwidget, onBtnApply());
	SINGLE_SLOT_CONNECT(firstwidget, closeWidget(), this, close());
    addPage(firstwidget, general);

	QTreeWidgetItem* modifyproto = addCategory(tr("Modify Proto File"));
    addPage(new EditorWidget(), modifyproto);

    connect(ui->list, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(changePageByItem(QTreeWidgetItem*, QTreeWidgetItem*)));
	ui->stackedWidget->setCurrentWidget(firstwidget);

	ui->m_title->setText("<b>" + firstwidget->windowTitle() + "</b>");
	

}

TrainingConfig::~TrainingConfig()
{
    delete ui;
}

void TrainingConfig::closeEvent(QCloseEvent *ev)
{
	QMap<QTreeWidgetItem *, TrainWidget*>::iterator iter = m_pages.begin();
	while (iter != m_pages.end()) {
		iter.value()->closeEvent(ev);
		++iter;
	}
}

GeneralConfig *TrainingConfig::generalConfig()
{
	QMap<QTreeWidgetItem *, TrainWidget*>::iterator iter = m_pages.begin();
	while (iter != m_pages.end()) {
		GeneralConfig * p = qobject_cast<GeneralConfig *>(iter.value());
		if (p) {
			return p;
		}

		++iter;
	}

	return NULL;
}

QTreeWidgetItem* TrainingConfig::addCategory(const QString& name)
{
  QTreeWidgetItem* item = new QTreeWidgetItem;
  item->setText(0, name);
  item->setData(0, Qt::UserRole, true);
  item->setFlags(Qt::ItemIsEnabled);

  ui->list->invisibleRootItem()->addChild(item);
  item->setExpanded(true);

  return item;
}

void TrainingConfig::addPage(TrainWidget* page, QTreeWidgetItem* parent)
{
  if (!parent) parent = ui->list->invisibleRootItem();

  QTreeWidgetItem* item = new QTreeWidgetItem;
  item->setText(0, page->windowTitle());
  item->setIcon(0, page->windowIcon());
  item->setData(0, Qt::UserRole, false);
  parent->addChild(item);

  // Add the page to the stack
  ui->stackedWidget->addWidget(page);

  m_pages[item] = page;
}

void TrainingConfig::changePageByItem(QTreeWidgetItem *current, QTreeWidgetItem * /*previous*/) {
  if (!(current->flags() & Qt::ItemIsSelectable)) {
    return;
  }

  // Set the title
  ui->m_title->setText("<b>" + current->text(0) + "</b>");


  QMap<QTreeWidgetItem *, TrainWidget*>::iterator iter = m_pages.begin();
  while (iter != m_pages.end()){
      if(iter.key() == current){
          ui->stackedWidget->setCurrentWidget(iter.value());
          break;
      }
      ++iter;
  }
}
