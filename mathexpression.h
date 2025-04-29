#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

#include <QStringList>

class MathExpression
{
public:
    MathExpression(QString exp);
    qreal Calculate(qreal x);
private:
    QString inital;
    QStringList postfixTok;
};

#endif // MATHEXPRESSION_H
