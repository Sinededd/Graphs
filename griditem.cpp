#include "griditem.h"
#include "qgraphicsitem.h"
#include <QTime>
#include <QGraphicsScene>


GridItem::GridItem(int gridSize, QGraphicsItem *parent) :
    QGraphicsItem{parent}, gridSize(gridSize)
{
    setZValue(-100);
}

void GridItem::addGridSize(int dgridS)
{
    if(gridSize <= 30)
    {
        gridSize *= 2;
        division *= 2;
    }
    if(gridSize >= 80)
    {
        gridSize /= 2;
        division /= 2;
    }
    gridSize += dgridS;
    update();
}

QRectF GridItem::boundingRect() const
{
    return QRectF(0, 0, scene()->sceneRect().width(), scene()->sceneRect().height());
}

void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // painter->setBrush(QBrush("red"));
    QRectF rect = boundingRect();
    painter->drawRect(rect);
    // painter->translate(rect.center());
    // rect.moveTo(pos);
        // Рисуем сетку
    QPen gridPen(QColor(200, 200, 200), 1, Qt::DashLine);
    QPen defPen(Qt::black, 2);
    for (int y = rect.center().y() + gridSize; y <= rect.bottom(); y += gridSize) { // сетка горизонт -
        painter->setPen(gridPen);
        painter->drawLine(rect.left(), y, rect.right(), y);
        painter->setPen(defPen);
        painter->drawText(rect.center().x() + 2, y + 7, QString::number(qFloor((-(y - rect.center().y())) / gridSize) * division));

    }
    for (int y = rect.center().y() - gridSize; y >= rect.top(); y -= gridSize) { // сетка горизонт +
        painter->setPen(gridPen);
        painter->drawLine(rect.left(), y, rect.right(), y);
        painter->setPen(defPen);
        painter->drawText(rect.center().x() + 2, y + 7, QString::number(qFloor(-(y - rect.center().y())) / gridSize * division));
    }
    ////
    for (int x = rect.center().x() + gridSize; x <= rect.right(); x += gridSize) {
        painter->setPen(gridPen);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        painter->setPen(defPen);
        painter->drawText(x - 5, rect.center().y() - 3, QString::number(qCeil(x - rect.center().x()) / gridSize * division));

    }
    for (int x = rect.center().x() - gridSize; x >= rect.left(); x -= gridSize) {
        painter->setPen(gridPen);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        painter->setPen(defPen);
        painter->drawText(x - 5, rect.center().y() - 3, QString::number(qFloor(x - rect.center().x()) / gridSize * division));
    }
    QPen axisPen(Qt::black, 2);
    painter->setPen(axisPen);

    painter->drawLine(rect.left(), rect.center().y(), rect.right(), rect.center().y());
    painter->drawLine(rect.center().x(), rect.top(), rect.center().x(), rect.bottom());
}
