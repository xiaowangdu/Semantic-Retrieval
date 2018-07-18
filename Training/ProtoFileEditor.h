#ifndef PROTOFILEEDITOR_H
#define PROTOFILEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include "EditorHighLighter.h"

class LineNumberArea;
class EditorHighLighter;


class ProtoFileEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    ProtoFileEditor(QWidget *parent = 0);
    ~ProtoFileEditor();

	bool save(const QString &filename);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

signals:
    void requestHighlightHint(QPair<HighlightPosition, HighlightPosition> &);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void codeBlockHint();

private:
    bool generateIndicator();
    void writeCurrentPair(const HighlightPosition& start, const HighlightPosition& end);
    int checkSupportedBracket(const QChar &bracket);
    void clearCurrentPair();

private:
    QWidget *m_lineNumberArea;
    EditorHighLighter *m_hightlight;

    QPair<HighlightPosition, HighlightPosition> m_currentMatchPair;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ProtoFileEditor *editor) : QWidget(editor) {
        m_codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(m_codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        m_codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    ProtoFileEditor *m_codeEditor;
};

#endif // PROTOFILEEDITOR_H
