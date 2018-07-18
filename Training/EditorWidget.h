#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include "TrainWidget.hpp"

namespace Ui {
class EditorWidget;
}

class EditorHighLighter;

class EditorWidget : public TrainWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(TrainWidget *parent = 0);
    ~EditorWidget();

	bool loadFile(const QString &name);
	void stateHint(const QString &tip, bool clear = true);
	void closeEvent(QCloseEvent *ev);

public slots:
	void onBtnOk();
	void onBtnCancel();
	void onBtnApply();

private slots:
    void onSave();
	void onOpenFile();
	void tipClear();
	void onTextChanged(bool);

private:
	bool dirty()const;
	void setDirty(bool);

private:
	bool m_dirty = false;

    Ui::EditorWidget *ui;
    EditorHighLighter *m_highlighter;

	QString m_currentFilename;
};

#endif // EDITORWIDGET_H
