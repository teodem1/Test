#include "stdafx.h"


Syntax::Syntax(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
	SyntaxRule CurrentRule;

	KeyWordFormat.setForeground(QColor("#63a058"));
	QStringList Patterns;
	Patterns << "scriptparsetree" << "rawfile" << "scriptbundle" << "xmodel" << "actor"; //I Can't Find Docs On All, Would Be Nice To Get The Rest :).

	foreach (const QString &Pattern, Patterns) {
		CurrentRule.RegExPattern = QRegExp(Pattern);
		CurrentRule.CharFormat = KeyWordFormat;
		Rules.append(CurrentRule);
	}

	IncludeFormat.setForeground(QColor("#fc8eac"));
	CurrentRule.RegExPattern = QRegExp("#[^\n]*"); //Start With #, Continue To New Line.
	CurrentRule.CharFormat = IncludeFormat;
	Rules.append(CurrentRule);

	QuoteFormat.setForeground(QColor("#6c6999"));
	CurrentRule.RegExPattern = QRegExp("\".*\""); //Start With ", Continue To Next ".
	CurrentRule.CharFormat = QuoteFormat;
	Rules.append(CurrentRule);

	SingleLineCommentFormat.setForeground(QColor("#c0e4ff"));
	CurrentRule.RegExPattern = QRegExp("//[^\n]*"); //Start With //, Continue To New Line.
	CurrentRule.CharFormat = SingleLineCommentFormat;
	Rules.append(CurrentRule);

	PreProcessor.setForeground(QColor("#a09c85"));
	CurrentRule.RegExPattern = QRegExp(">[^\n]*");
	CurrentRule.CharFormat = PreProcessor;
	Rules.append(CurrentRule);

	MultiLineCommentFormat.setForeground(QColor("#c0e4ff"));
	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void Syntax::highlightBlock(const QString &text)
{
	foreach (const SyntaxRule &rule, Rules) {
		QRegExp expression(rule.RegExPattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();	
			setFormat(index, length, rule.CharFormat);
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
		setFormat(startIndex, commentLength, MultiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}