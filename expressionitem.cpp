#include "expressionitem.h"

ExpressionItem::ExpressionItem(MathExpression *exp, GridItem *parent,
                               QColor color)
    : SceneItem{parent}, exp(exp) {
    grid = parent;
    QPen pen(color);
    pen.setWidth(2);
    setPen(pen);
    paintPath = new QPainterPath();
    // setFlag(ItemIsMovable, true);
}

void ExpressionItem::setExp(MathExpression *exp)
{
    delete this->exp;
    this->exp = exp;
}

MathExpression *ExpressionItem::getExp()
{
    return exp;
}

void ExpressionItem::draw(QPainterPath *path)
{
    if(!exp->isValid()) return;

    if(exp->getFuncType() == 0)
    {
        implicitFunction(path);
    }
    else if(exp->getFuncType() == 1)
    {
        explicitByXFunction(path);
    }
    else
    {
        explicitByYFunction(path);
    }
}

void ExpressionItem::explicitByXFunction(QPainterPath *path) {
    QRectF rect = getRect();
    int i = rect.left();
    QPointF previousPoint = QPointF(
        i,
        exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize());
    path->moveTo(previousPoint);
    for (i = i + 1; i < rect.right(); i++) {
        QPointF newPoint = QPointF(
            i,
            exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize());
        if(!rect.contains(newPoint))
        {
            path->moveTo(newPoint);
        }
        if(qAbs(previousPoint.y() - newPoint.y()) > rect.height())
        {
            path->moveTo(newPoint);
        }
        else
        {
            path->lineTo(newPoint);
        }

        previousPoint = newPoint;
    }
}

void ExpressionItem::explicitByYFunction(QPainterPath *path)
{
    QRectF rect = getRect();
    int i = rect.top();
    QPointF previousPoint = QPointF(
        exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize(),
        i);
    path->moveTo(previousPoint);
    for (i = i + 1; i < rect.bottom(); i++) {
        QPointF newPoint = QPointF(
            exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize(),
            i);
        if(!rect.contains(newPoint))
        {
            path->moveTo(newPoint);
        }
        if(qAbs(previousPoint.x() - newPoint.x()) > rect.width())
        {
            path->moveTo(newPoint);
        }
        else
        {
            path->lineTo(newPoint);
        }

        previousPoint = newPoint;
    }
}

void ExpressionItem::implicitFunction(QPainterPath *path) {
    QRectF rect = getRect();
    QSizeF size = rect.size();
    qreal gridSize = grid->GridSize();
    qreal posX = 0;
    qreal posY = 0;
    qreal step = 5;


    int gridWidth = static_cast<int>(size.width() / step) + 1;
    int gridHeight = static_cast<int>(size.height() / step) + 1;
    std::vector<std::vector<qreal>> functionValues(gridHeight,
                                                   std::vector<qreal>(gridWidth));

    for (int j = 0; j < gridHeight; ++j) {
        qreal y = (-size.height() / 2 + posY + j * step) / gridSize;
        for (int i = 0; i < gridWidth; ++i) {
            qreal x = (-size.width() / 2 - posX + i * step) / gridSize;
            functionValues[j][i] = exp->Calculate(x, -y);
        }
    }

    for (int j = 0; j < gridHeight - 1; ++j) {
        for (int i = 0; i < gridWidth - 1; ++i) {
            qreal f00 = functionValues[j][i];
            qreal f10 = functionValues[j][i + 1];
            qreal f01 = functionValues[j + 1][i];
            qreal f11 = functionValues[j + 1][i + 1];
            qreal x = -size.width() / 2 + i * step;
            qreal y = -size.height() / 2 + j * step;

            QList<QPointF> points;
            if (f00 * f10 < 0 && std::abs(f10 - f00) > 1e-6) {
                qreal t = -f00 / (f10 - f00);
                points.emplaceBack((x + t * step), -(y));
            }
            if (f10 * f11 < 0 && std::abs(f11 - f10) > 1e-6) {
                qreal t = -f10 / (f11 - f10);
                points.emplaceBack((x + step), -((y + t * step)));
            }
            if (f11 * f01 < 0 && std::abs(f01 - f11) > 1e-6) {
                qreal t = -f11 / (f01 - f11);
                points.emplaceBack((x + (1 - t) * step), -((y + step)));
            }
            if (f01 * f00 < 0 && std::abs(f00 - f01) > 1e-6) {
                qreal t = -f01 / (f00 - f01);
                points.emplaceBack(x, -((y + (1 - t) * step)));
            }

            if (points.size() >= 2) {
                path->moveTo(points[0]);
                for (int k = 1; k < points.size(); ++k) {
                    path->lineTo(points[k]);
                }
            }
        }
    }
}
