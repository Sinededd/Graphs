#include "expressionitem.h"

ExpressionItem::ExpressionItem(MathExpression *exp, GridItem *parent,
                               QColor color)
    : QGraphicsItem{parent}, exp(exp) {
    grid = parent;
    this->color = color;
}

QRectF ExpressionItem::boundingRect() const {
    return QRectF(-grid->Size().width() / 2, -grid->Size().height() / 2,
                  grid->Size().width(), grid->Size().height());
}

void ExpressionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                           QWidget *) {
    painter->setRenderHint(QPainter::Antialiasing);
    QPen graphPen(color, 2);
    painter->setPen(graphPen);
    if(exp->isImplicit())
    {
        qInfo() << "implicit hui";
        implicitFunction(painter);
    }
    else
    {
        qInfo() << "explicit hui";
        explicitFunction(painter);
    }
}

void ExpressionItem::explicitFunction(QPainter *painter) {
    int i = -grid->Pos().x() - grid->Size().width() / 2;
    QPointF previousPoint = QPointF(
        i + grid->Pos().x(),
        -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() +
            grid->Pos().y());
    for (i = i + 1; i < grid->Size().width(); i++) {
        QPointF newPoint = QPointF(
            i + grid->Pos().x(),
            -exp->Calculate((qreal)i / (qreal)grid->GridSize()) * grid->GridSize() +
                grid->Pos().y());
        painter->drawLine(previousPoint, newPoint);
        previousPoint = newPoint;
    }
}

void ExpressionItem::implicitFunction(QPainter *painter) {
    QSizeF size = grid->Size();
    qreal gridSize = grid->GridSize();
    qreal posX = grid->Pos().x();
    qreal posY = grid->Pos().y();
    qreal step = 5;

    painter->setRenderHint(QPainter::Antialiasing);

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

    QPainterPath path;
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
                path.moveTo(points[0]);
                for (int k = 1; k < points.size(); ++k) {
                    path.lineTo(points[k]);
                }
            }
        }
    }
    painter->drawPath(path);
}
