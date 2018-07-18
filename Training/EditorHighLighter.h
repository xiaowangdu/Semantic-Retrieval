#ifndef EDITORHIGHLIGHTER
#define EDITORHIGHLIGHTER

#include <QSyntaxHighlighter>

struct HighlightPosition{
    QTextBlock block;
    int colomn = -1;
    QString matchType;

    HighlightPosition &operator=(const HighlightPosition &other){
        block = other.block; colomn = other.colomn; matchType = other.matchType;
        return *this;
    }


    bool isNull(){return !block.isValid() && (colomn == -1) && matchType.isEmpty();}
};

class EditorHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum HighlightMode{
        INIT, BLOCK_HINT
    };

    EditorHighLighter(QTextDocument *parent = 0);
    ~EditorHighLighter();

    void setMode(const HighlightMode mode);
    HighlightMode mode()const;
    bool hint();

public slots:
    void highlightHint(QPair<HighlightPosition, HighlightPosition> &highlightmatch);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;


private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat m_digitalFormat;
    QTextCharFormat singleLineKey;
    QTextCharFormat singleLineValue;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

    HighlightMode m_mode;
    QPair<HighlightPosition, HighlightPosition> m_currentHintPair;
};

#endif // EDITORHIGHLIGHTER
