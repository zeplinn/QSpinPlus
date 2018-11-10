#include "qspin/models/QsPromelaSyntaxHighlighter.h"
PromelaTextHighlighter PromelaSyntaxHighlighter::colors() const{ return _colors;}

void PromelaSyntaxHighlighter::setColors(PromelaTextHighlighter value){
_colors = value;
/*    classFormat.setForeground(_colors->classes);
    keywordFormat.setForeground(_colors->keywords);
    singleLineCommentFormat.setForeground(_colors->comments);
    multiLineCommentFormat.setForeground(colors()->comments);
    typeFormat.setForeground(_colors->types);
    operatorsFormat.setForeground(_colors->operators);
    numberFormat.setForeground(_colors->numbers);
    stringFormat.setForeground(_colors->strings)*/;

    qDebug() << "highlighting rules before"<<highlightingRules.count();
    highlightingRules.clear();
    classRules(_colors.classes());
    keywordRules(_colors.keywords());
    typeRules(_colors.types());
    symbolRules(_colors.operators());
    numberRules(_colors.numbers());
    stringRules(_colors.strings());
    commentRules(_colors.comments());
    qDebug() << "highlighting rules after"<<highlightingRules.count();
    emit colorsChanged();
}

PromelaSyntaxHighlighter::PromelaSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
}

void PromelaSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, *rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = commentStartExpression.indexIn(text);

        while (startIndex >= 0) {
            int endIndex = commentEndExpression.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
}

void PromelaSyntaxHighlighter::addToHighlightingRules(const QStringList &rules, QTextCharFormat& format){
    HighlightingRule rule;
    foreach (const QString &pattern, rules) {
        rule.pattern = QRegExp(pattern);
        rule.format = &format;
        highlightingRules.append(rule);
    }

    //fun version. later
//    rule.pattern = QRegExp(format.join("|"));
//    highlightingRules.append(rule);
//    rules.join("|");
}

void PromelaSyntaxHighlighter::classRules(QColor color){
    classFormat.setForeground(color);
    classFormat.setFontWeight(QFont::Bold);
    QStringList classPatterns;
    classPatterns << "\\bactive\\b"
                  << "\\binit\\b"
                  << "\\bnever\\b"
                  << "\\btrace\\b"
                  << "\\bnotrace\\b"
                  << "\\bprovided\\b"
                  << "\\bpriority\\b";
    addToHighlightingRules(classPatterns,classFormat);
}

void PromelaSyntaxHighlighter::keywordRules(QColor color){
    keywordFormat.setForeground(color);
    classFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bif\\b"
                    << "\\bfi\\b"
                    << "\\bdo\\b"
                    << "\\bod\\b"
                    << "\\b::\\b"
                    << "ltl"
                    << "\\batomic\\b"
                    << "\\bd_step\\b"
                    << "\\belse\\b"
                    << "\\bbreak\\b"
                    << "\\bprint\\b"
                    << "\\bskip\\b"
                    << "\\bgoto\\b"
                    << "\\bassert\\b"
                    << "\\beval\\b"
                    << "\\bhidden\\b"
                    << "\\bshow\\b"
                    << "\\btrue\\b"
                    << "\\bfalse\\b"
                    << "\\blen\\b"
                    << "\\btimeout\\b"
                    << "\\bnp_\\b"
                    << "\\bxr\\b"
                    << "\\bxs\\b";
   addToHighlightingRules(keywordPatterns,keywordFormat);
}

void PromelaSyntaxHighlighter::commentRules(QColor color){
    singleLineCommentFormat.setForeground(color);
    addToHighlightingRules({"//[^\n]*"},singleLineCommentFormat);
    multiLineCommentFormat.setForeground(color);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void PromelaSyntaxHighlighter::typeRules(QColor color){
    typeFormat.setForeground(color);
    QStringList typePatterns;
    typePatterns << "\\bbit\\b"
                 << "\\bbyte\\b"
                 << "\\bbool\\b"
                 << "\\bpid\\b"
                 << "\\bshort\\b"
                 << "\\bint\\b"
                 << "\\bmtype\\b"
                 << "\\bchan\\b";
   addToHighlightingRules(typePatterns,typeFormat);
}

void PromelaSyntaxHighlighter::symbolRules(QColor color) {
    operatorsFormat.setForeground(color);
    QStringList operatorPatterns;
    operatorPatterns << "\\!"
                   << "\\?"
                   << "\\<"
                   << "\\>"
                   << "\\="
                   << "\\+"
                   << "\\-"
                   << "\\|"
                   << "\\*"
                   << "\\/"
                   << "\\%"
                   << "\\&"
                   << "\\^"
                   << "\\~"
                      ;
    addToHighlightingRules(operatorPatterns,operatorsFormat);
}

void PromelaSyntaxHighlighter::numberRules(QColor color) {
    numberFormat.setForeground(color);
    addToHighlightingRules({"\\b[0-9]+\\b"},numberFormat);
}

void PromelaSyntaxHighlighter::stringRules(QColor color) {
    stringFormat.setForeground(color);
    addToHighlightingRules({"([\"][^\n]*[\"])"},stringFormat);
}
