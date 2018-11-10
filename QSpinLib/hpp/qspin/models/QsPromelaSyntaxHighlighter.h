#ifndef QSPROMELASYNTAXHIGHLIGHTER_H
#define QSPROMELASYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
// copied from https://github.com/flamingoen/qspin
// the above link is based on the qt example
// http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
#include "qspin/viewModels/ColorScheme.h"
#include "qspin/Qs.h"
class PromelaSyntaxHighlighter : public QSyntaxHighlighter {

    Q_OBJECT
    Q_PROPERTY(PromelaTextHighlighter colors READ colors WRITE setColors NOTIFY colorsChanged)
    QColor _classes = Qt::magenta, _keywords=Qt::red
            , _operators=Qt::yellow, _comments= Qt::green, _number=Qt::cyan, _types= Qt::blue,_strings = Qt::darkYellow;
    PromelaTextHighlighter _colors;
public:
    PromelaTextHighlighter colors()const;
    void setColors(PromelaTextHighlighter value);
signals:
    void colorsChanged();
public:
    PromelaSyntaxHighlighter(QTextDocument *parent = nullptr);


protected:
    virtual void highlightBlock(const QString &text) override;

private:
    void addToHighlightingRules(const QStringList &rules, QTextCharFormat &format);


    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat* format;
        //HighlightingRule(QTextCharFormat & format):format(format){}
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat classFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat typeFormat;
    QTextCharFormat operatorsFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat stringFormat;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    void classRules(QColor color);
    void keywordRules(QColor color);
    void commentRules(QColor color);
    void typeRules(QColor color);
    void symbolRules(QColor color);
    void numberRules(QColor color);
    void stringRules(QColor color);
};
#endif // QSPROMELASYNTAXHIGHLIGHTER_H
