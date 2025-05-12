#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include "mathexpression.h"
#include "griditem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QWidget>
#include <QGraphicsScene>

class ExpressionItem : public QGraphicsItem
{
public:
    ExpressionItem(MathExpression *exp, GridItem *parent, QColor color = QColor("red"));
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget) override;

private:
    MathExpression *exp;
    GridItem *grid;
    QColor color;

    qreal renderK = 2;
    QPointF renderPos;

    QPainterPath *paintPath;

    void explicitFunction(QPainterPath *path);
    void implicitFunction(QPainterPath *path);
};

#endif // EXPRESSIONITEM_H
