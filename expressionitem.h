#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include "mathexpression.h"
#include "griditem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>

class ExpressionItem : public QGraphicsItem
{
public:
    ExpressionItem(MathExpression *exp, GridItem *parent, QColor color = QColor("red"));
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    MathExpression *exp;
    GridItem *grid;
    QColor color;

    void explicitFunction(QPainter *painter);
    void implicitFunction(QPainter *painter);
};

#endif // EXPRESSIONITEM_H
