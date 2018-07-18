
#ifndef FANCYTABWIDGET_H
#define FANCYTABWIDGET_H

#include <memory>

#include <QTabWidget>
#include <QWidget>

class QActionGroup;
class QMenu;
class QSignalMapper;


class FancyTabWidget : public QTabWidget {
  Q_OBJECT

    public:
        FancyTabWidget(QWidget* parent = 0);
        int addTab(QWidget * page, const QIcon & icon, const QString & label);
        int insertTab(int index, QWidget * page, const QIcon & icon, const QString & label);
        void addBottomWidget(QWidget* widget);

        void setBackgroundPixmap(const QPixmap& pixmap);
        void addSpacer();

        void loadSettings(const char *);
        void saveSettings(const char *);
        // Values are persisted - only add to the end
        enum Mode {
            Mode_None = 0,
            Mode_LargeSidebar,
            Mode_SmallSidebar,
            Mode_Tabs,
            Mode_IconOnlyTabs,
            Mode_PlainSidebar,
        };
    
        static const QSize TabSize_LargeSidebar;

        static const QSize IconSize_LargeSidebar;
        static const QSize IconSize_SmallSidebar;
        
        Mode mode() { return mode_; }

    signals:
        void ModeChanged(FancyTabWidget::Mode mode);

    public slots:
        void setCurrentIndex(int index);
        void SetMode(Mode mode);
        // Mapper mapped signal needs this convenience function 
        void SetMode(int mode) { SetMode(Mode(mode)); }

    private slots:
        void tabBarUpdateGeometry();
        void currentTabChanged(int);

    protected:
        void paintEvent(QPaintEvent *);
        //void contextMenuEvent(QContextMenuEvent* e);
    private:
        void addMenuItem(QSignalMapper* mapper, QActionGroup* group,
                                 const QString& text, Mode mode);

        QPixmap background_pixmap_;
        QMenu* menu_;
        Mode mode_;
        QWidget *bottom_widget_;

};

#endif  // FANCYTABWIDGET_H
