#include "mathparser.h"
#include "mathchecker.h"


QStringList MathParser::CreateTokenList(QString exp)
{
    QStringList tokens;
    QString cleaned = exp.simplified().replace(" ", "");
    QString tokenStr;

    QRegularExpressionMatchIterator it = re.globalMatch(cleaned);

    while (it.hasNext()) {
        QString token = it.next().captured(1);
        if (!token.isEmpty())
        {
            tokens << token;
            tokenStr += token;
        }
    }

    if(tokenStr != cleaned)
    {
        MathChecker::ThrowError(MathChecker::Invalid_Syntax);
    }
    qInfo() << tokens;
    return tokens;
}
