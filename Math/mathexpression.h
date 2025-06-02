#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H


#include "Math/mathchecker.h"
#include <QStringList>

class MathExpression
{
public:
    MathExpression(QString exp);
    qreal Calculate(qreal const &x, qreal const &y = qreal{INFINITY});
    int getFuncType(); // 0 - implicit, 1 - explicit by X, 2 - explicit by Y
    bool isValid(){ return isValidExp; }
    QString getString();
    // MathChecker::error_type getError{ return errorType;}
private:
    QString inital;
    QStringList postfixTok;

    int funcType = 1;
    bool isValidExp;
    MathChecker::error_type errorType;
};

#endif // MATHEXPRESSION_H
