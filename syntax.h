#pragma once

class Syntax : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Syntax(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct SyntaxRule
    {
        QRegExp RegExPattern;
        QTextCharFormat CharFormat;
    };
    QVector<SyntaxRule> Rules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat KeyWordFormat;
	QTextCharFormat QuoteFormat;
    QTextCharFormat SingleLineCommentFormat;
    QTextCharFormat MultiLineCommentFormat;
	QTextCharFormat IncludeFormat;
	QTextCharFormat PreProcessor;
};