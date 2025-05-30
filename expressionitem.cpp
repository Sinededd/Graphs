#include "expressionitem.h"

ExpressionItem::ExpressionItem(MathExpression *exp, GridItem *parent,
                               QColor color)
    : QGraphicsItem{parent}, exp(exp) {
    grid = parent;
    this->color = color;
    paintPath = new QPainterPath();
    renderPos = QPointF(INFINITY, INFINITY);
    setFlag(ItemIsMovable, true);
}

QRectF ExpressionItem::boundingRect() const {
    return QRectF(-grid->Size().width() * renderK / 2, -grid->Size().height() * renderK / 2,
                  grid->Size().width() * renderK, grid->Size().height() * renderK);
}

void ExpressionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                           QWidget *) {
    painter->setRenderHint(QPainter::Antialiasing);
    QPen graphPen(color, 2);
    painter->setPen(graphPen);
    // painter->drawRect(boundingRect());
    if(grid->isCurrentDraw() == 0)
    {
        // qInfo() << this->pos();
        // paintPath->addRect(boundingRect());
        paintPath->clear();
        if(exp->isImplicit())
        {
            // qInfo() << "implicit hui";
            implicitFunction(paintPath);
        }
        else
        {
            // qInfo() << "explicit hui";
            explicitFunction(paintPath);

        }
        grid->setCurrentDraw();
        QPainterPath curPath(paintPath->toReversed());
        painter->drawPath(curPath);
        return;
    }
    QPainterPath curPath(paintPath->toReversed());

    painter->drawPath(curPath);
}

void ExpressionItem::explicitFunction(QPainterPath *path) {
    if(grid->isCurrentDraw() == 0)
    {
        qInfo() << "penis";
        int i = -grid->Pos().x() - grid->Size().width() * renderK / 2;
        QPointF previousPoint = QPointF(
            i + grid->Pos().x(),
            -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() +
                grid->Pos().y());
        path->moveTo(previousPoint);
        for (i = i + 1; i < grid->Size().width() * renderK; i++) {
            QPointF newPoint = QPointF(
                i + grid->Pos().x(),
                -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() +
                    grid->Pos().y());
            if(qAbs(previousPoint.y() - newPoint.y()) > 1000)
            {
                path->moveTo(newPoint);
                // painter->drawLine(previousPoint, newPoint);
            }
            else
            {
                path->lineTo(newPoint);
            }

            previousPoint = newPoint;
        }
    }
    else
    {
        int i = - grid->Size().width() / 2;
        QPointF previousPoint = QPointF(
            i,
            -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize());
        path->moveTo(previousPoint);
        for (i = i + 1; i < grid->Size().width() * renderK; i++) {
            QPointF newPoint = QPointF(
                i,
                -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize());
            if(qAbs(previousPoint.y() - newPoint.y()) > 1000)
            {
                path->moveTo(newPoint);
                // painter->drawLine(previousPoint, newPoint);
            }
            else
            {
                path->lineTo(newPoint);
            }

            previousPoint = newPoint;
        }
    }

}

void ExpressionItem::implicitFunction(QPainterPath *path) {
    QSizeF size = grid->Size() * renderK;
    qreal gridSize = grid->GridSize();
    qreal posX = grid->Pos().x();
    qreal posY = grid->Pos().y();
    qreal step = 5;


    int gridWidth = static_cast<int>(size.width() / step) + 1;
    int gridHeight = static_cast<int>(size.height() / step) + 1;
    std::vector<std::vector<qreal>> functionValues(gridHeight,
                                                   std::vector<qreal>(gridWidth));

    for (int j = 0; j < gridHeight; ++j) {
        qreal y = (-size.height() / 2 + posY + j * step) / gridSize;
        for (int i = 0; i < gridWidth; ++i) {
            qreal x = (-size.width() / 2 - posX + i * step) / gridSize;
            functionValues[j][i] = exp->Calculate(x, y);
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
                    // painter->drawLine(points[k - 1], points[k]);
                }
            }
        }
    }
}
