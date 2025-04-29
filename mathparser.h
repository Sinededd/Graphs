#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <QStringList>
#include <QRegularExpression>

class MathParser
{
public:
    static QStringList CreateTokenList(QString exp);

private:
    MathParser() {}
    static inline QRegularExpression re = QRegularExpression("(\\d+\\.?\\d*|[-+*\\/()]|\\s|sin|\\w)");
};

#endif // MATHPARSER_H
