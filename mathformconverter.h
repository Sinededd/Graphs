#ifndef MATHFORMCONVERTER_H
#define MATHFORMCONVERTER_H

#include <QHash>
#include <QStringList>
#include <QStack>

class MathFormConverter
{
public:
    static QStringList InfixToPostfix(QStringList tokens);
    static QString StringFromTokens(QStringList tokens);
private:
    MathFormConverter() {}
    static inline QHash<QString, int> precedence
        = QHash<QString, int>{{"(", -1}, {")", -1}, {"+", 0}, {"-", 0}, {"*", 1}, {"/", 1}};
};

#endif // MATHFORMCONVERTER_H
