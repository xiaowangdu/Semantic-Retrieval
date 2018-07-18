#include "../utility/Constants.hpp"
#include "ProtoFileEditor.h"
#include <QPaintEvent>
#include <QTextBlock>
#include <QTextFragment>
#include <QPainter>
#include <QDebug>
#include <QStack>
#include <QPalette>

#define NOT_SUPPORTED -1

const QChar match_table[] = {
    '{', '}'
};
//define match with match_table
enum SupportedState{
    FORWARD_SYMBOL, BACK_SYMBOL
};

ProtoFileEditor::ProtoFileEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(10);
    setFont(font);

    QPalette pal = palette();
    pal.setColor(QPalette::Active, QPalette::Base, Qt::lightGray);
    pal.setColor(QPalette::Inactive, QPalette::Base, Qt::lightGray);
    setPalette(pal);


    m_lineNumberArea = new LineNumberArea(this);
    m_hightlight = new EditorHighLighter(document());

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    //connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(codeBlockHint()));
    connect(this, SIGNAL(requestHighlightHint(QPair<HighlightPosition, HighlightPosition> &)), m_hightlight, SLOT(highlightHint(QPair<HighlightPosition, HighlightPosition> &)));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

}

ProtoFileEditor::~ProtoFileEditor()
{
    delete m_lineNumberArea;
}

bool ProtoFileEditor::save(const QString &filename)
{
	QFile file(filename);
	if (!file.exists()) {
		return false;
	}

	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);  
		stream << toPlainText();
		file.flush();
		file.close();
	}
	else {
		return false;
	}
}

int ProtoFileEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    int factor = max >= 100 ? 10 : 28;

    while (max >= 10) {
        max /= 10;
        ++digits;
    }



    int space = factor + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void ProtoFileEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void ProtoFileEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        m_lineNumberArea->scroll(0, dy);
    else
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ProtoFileEditor::codeBlockHint()
{
    //qDebug() << "ProtoFileEditor::codeBlockHint";
    highlightCurrentLine();
    bool res = generateIndicator();

    if(res){
        emit requestHighlightHint(m_currentMatchPair);
    }
    else{
        if(m_hightlight->mode() != EditorHighLighter::INIT){
            m_hightlight->setMode(EditorHighLighter::INIT);
            m_hightlight->rehighlight();
        }
    }
}

bool ProtoFileEditor::generateIndicator()
{
    HighlightPosition start;
    HighlightPosition end;

    QTextCursor cursor = textCursor();

    //int cur_row = cursor.blockNumber();
    int cur_col = cursor.columnNumber();
    QString content = cursor.block().text();

    if(!content.isEmpty()){
        //check forward
        if(cur_col - 1 >= 0){
            int state = checkSupportedBracket(content[cur_col - 1]);
            //"}|" type
            if(state != NOT_SUPPORTED && state == BACK_SYMBOL){
                end.block = cursor.block();
                end.colomn = cur_col - 1;
                end.matchType = match_table[BACK_SYMBOL];


                //search start "{"
                QStack<QString> stack;
                stack.push(end.matchType);
                int from = end.colomn - 1;

                int i = from;
                while(i >= 0){
                    if(content[i] == match_table[BACK_SYMBOL]){
                        stack.push(match_table[BACK_SYMBOL]);
                    }
                    else if(content[i] == match_table[FORWARD_SYMBOL]){
                        stack.pop();
                        if(stack.isEmpty()){
                            start.block = cursor.block();
                            start.colomn = i;
                            start.matchType = match_table[FORWARD_SYMBOL];

                            writeCurrentPair(start, end);
                            return true;
                        }
                    }
                    i--;
                }


                QTextBlock block = cursor.block().previous();
                while (block.isValid()){
                    content = block.text();
                    int i = content.size() - 1;
                    while(i >= 0){
                        if(content[i] == match_table[BACK_SYMBOL]){
                            stack.push(match_table[BACK_SYMBOL]);
                        }
                        else if(content[i] == match_table[FORWARD_SYMBOL]){
                            stack.pop();
                            if(stack.isEmpty()){
                                start.block = block;
                                start.colomn = i;
                                start.matchType = match_table[FORWARD_SYMBOL];

                                writeCurrentPair(start, end);
                                return true;
                            }
                        }
                        i--;
                    }

                    block = block.previous();
                }

                return false;
            }
        }

        //check back
        int state = checkSupportedBracket(content[cur_col]);
        if(state != NOT_SUPPORTED && state == FORWARD_SYMBOL){
            start.block = cursor.block();
            start.colomn = cur_col;
            start.matchType = match_table[FORWARD_SYMBOL];

            //search end "}"
            QStack<QString> stack;
            stack.push(start.matchType);
            int from = start.colomn + 1;

            int i = from;
            while(i < content.size()){
                if(content[i] == match_table[FORWARD_SYMBOL]){
                    stack.push(match_table[FORWARD_SYMBOL]);
                }
                else if(content[i] == match_table[BACK_SYMBOL]){
                    stack.pop();
                    if(stack.isEmpty()){
                        end.block = cursor.block();
                        end.colomn = i;
                        end.matchType = match_table[BACK_SYMBOL];

                        writeCurrentPair(start, end);
                        return true;
                    }
                }
                i++;
            }


            QTextBlock block = cursor.block().next();
            while (block.isValid()){
                content = block.text();
                int i = 0;
                while(i < content.size()){
                    if(content[i] == match_table[FORWARD_SYMBOL]){
                        stack.push(match_table[FORWARD_SYMBOL]);
                    }
                    else if(content[i] == match_table[BACK_SYMBOL]){
                        stack.pop();
                        if(stack.isEmpty()){
                            end.block = block;
                            end.colomn = i;
                            end.matchType = match_table[BACK_SYMBOL];

                            writeCurrentPair(start, end);
                            return true;
                        }
                    }
                    i++;
                }

                block = block.next();
            }

            return false;
        }

    }

    return false;
}

void ProtoFileEditor::writeCurrentPair(const HighlightPosition& start, const HighlightPosition& end)
{
    m_currentMatchPair.first = start;
    m_currentMatchPair.second = end;
}

int ProtoFileEditor::checkSupportedBracket(const QChar &bracket)
{
    int size = sizeof(match_table)/sizeof(QChar);
    if(size <= 0 || bracket.isNull()){
        return NOT_SUPPORTED;
    }

    for(int i = 0; i < size; ++i){
        if(match_table[i] == bracket) return i;
    }

    return NOT_SUPPORTED;
}

void ProtoFileEditor::clearCurrentPair()
{
    HighlightPosition start;
    HighlightPosition end;

    m_currentMatchPair.first = start;
    m_currentMatchPair.second = end;
}

void ProtoFileEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void ProtoFileEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = DEFAULT_HIGHLIGHT_SELECTED.lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void ProtoFileEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::gray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
