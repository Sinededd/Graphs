#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

#include "mathchecker.h"
#include <mathparser.h>
#include <QStringList>

class MathExpression
{
public:
    MathExpression(QString exp);
    qreal Calculate(qreal const &x, qreal const &y = qreal{INFINITY});
    bool isImplicit();
    bool isValid(){ return isValidExp; }
private:
    QString inital;
    QStringList postfixTok;

    bool isValidExp;
    MathChecker::error_type errorType;
};

#endif // MATHEXPRESSION_H
