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
    ~ExpressionItem() override {delete exp; }
    void setExp(MathExpression *exp);
    MathExpression* getExp();

protected:
    void draw(QPainterPath *path) override;

private:
    MathExpression *exp;
    GridItem *grid;
    QPainterPath *paintPath;

    void explicitByXFunction(QPainterPath *path);
    void explicitByYFunction(QPainterPath *path);
    void implicitFunction(QPainterPath *path);
};

#endif // EXPRESSIONITEM_H
