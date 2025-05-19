#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include "Math/mathexpression.h"
#include "griditem.h"
#include "sceneitem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QWidget>
#include <QGraphicsScene>

class ExpressionItem : public SceneItem
{
public:
    ExpressionItem(MathExpression *exp, GridItem *parent, QColor color = QColor("red"));

protected:
    void draw(QPainterPath *path) override;

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
