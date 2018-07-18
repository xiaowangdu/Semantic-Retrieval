#include "EditorHighLighter.h"
#include <QDebug>

EditorHighLighter::EditorHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkCyan);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\binput\\b" << "\\binput_dim\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(Qt::darkYellow);
    keywordFormat.setFontWeight(QFont::Bold);
    keywordPatterns.clear();
    keywordPatterns << "\\bname\\b" << "\\btype\\b" << "\\bbottom\\b" << "\\btop\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::green);
    classFormat.setBackground(Qt::gray);
    rule.pattern = QRegExp("\\blayers\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    // Comment '#'
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);


    m_digitalFormat.setForeground(QColor(194,98,24));
    m_digitalFormat.setFontWeight(QFont::Bold);
    //m_digitalFormat.setFont(nFont);
    rule.pattern = QRegExp("\\b\\d+\\.?\\d*\\b");
    rule.format = m_digitalFormat;
    highlightingRules.append(rule);

    m_digitalFormat.setForeground(QColor(194,98,24));
    m_digitalFormat.setFontWeight(QFont::Bold);
    //m_digitalFormat.setFont(nFont);
    rule.pattern = QRegExp("\\d+([.])");
    rule.format = m_digitalFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkYellow);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);
    multiLineCommentFormat.setBackground(Qt::blue);
    commentStartExpression = QRegExp("\\{");
    commentEndExpression = QRegExp("\\}");
}

EditorHighLighter::~EditorHighLighter()
{

}

void EditorHighLighter::setMode(const HighlightMode mode)
{
    m_mode = mode;
}

EditorHighLighter::HighlightMode EditorHighLighter::mode()const
{
    return m_mode;
}

bool EditorHighLighter::hint()
{
    return m_mode == BLOCK_HINT;
}

void EditorHighLighter::highlightHint(QPair<HighlightPosition, HighlightPosition> &highlightmatch)
{
    m_mode = INIT;

    if(!highlightmatch.first.isNull() && !highlightmatch.second.isNull()){
        setMode(INIT);
        rehighlight();

        setMode(BLOCK_HINT);
        m_currentHintPair = highlightmatch;
        rehighlightBlock(highlightmatch.first.block);
        rehighlightBlock(highlightmatch.second.block);

//        qDebug() << highlightmatch.first.block.blockNumber() << highlightmatch.first.colomn << highlightmatch.first.matchType;
//        qDebug() << highlightmatch.second.block.blockNumber() << highlightmatch.second.colomn << highlightmatch.second.matchType;

    }
    //rehighlight();
}

void EditorHighLighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    if(hint()){
        if(m_currentHintPair.first.block.text() == text){
            setFormat(m_currentHintPair.first.colomn, 1, multiLineCommentFormat);
        }
        else if(m_currentHintPair.second.block.text() == text){
            setFormat(m_currentHintPair.second.colomn, 1, multiLineCommentFormat);
        }
    }

    //qDebug() << currentBlock().blockNumber() << text;
}
