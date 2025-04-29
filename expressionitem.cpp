#include "expressionitem.h"

ExpressionItem::ExpressionItem(MathExpression *exp, GridItem *parent, QColor color)
    : QGraphicsItem{parent}, exp(exp)
{
    grid = parent;
    this->color = color;
}

QRectF ExpressionItem::boundingRect() const
{
    return QRectF(-grid->Size().width() / 2, -grid->Size().height() / 2, grid->Size().width(), grid->Size().height());
}

void ExpressionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen graphPen(color, 2);
    painter->setPen(graphPen);
    // double k = (double)grid->Size().width() / grid->GridSize();
    int i = -grid->Pos().x() - grid->Size().width() / 2;
    QPointF previousPoint = QPointF(i + grid->Pos().x(), -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() + grid->Pos().y());
    for(i = i + 1; i < grid->Size().width(); i++)
    {
        QPointF newPoint = QPointF(i + grid->Pos().x(), -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() + grid->Pos().y());
        painter->drawLine(previousPoint, newPoint);
        previousPoint = newPoint;

    }
}
