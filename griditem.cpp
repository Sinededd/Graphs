#include "griditem.h"
#include "qgraphicsitem.h"
#include <QTime>
#include <QGraphicsScene>


GridItem::GridItem(int gridSize, QGraphicsItem *parent) :
    QGraphicsItem{parent}, gridSize(gridSize)
{}


QRectF GridItem::boundingRect() const
{
    return QRectF(50, 50, scene()->sceneRect().width() - 100, scene()->sceneRect().height() - 100);
}

void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    // painter->setRenderHint(QPainter::Antialiasing);
    // // Рисуем сетку
    // QPen gridPen(QColor(200, 200, 200), 1, Qt::DashLine);
    // QPen defPen(Qt::black, 2);
    // for (int y = gridSize + pos.y(); y <= size.height() / 2; y += gridSize) { // сетка горизонт -
    //     painter->setPen(gridPen);
    //     painter->drawLine(-size.width() / 2, y, size.width() / 2, y);
    //     painter->setPen(defPen);
    //     painter->drawText(5 + pos.x(), y + 5, "-" + QString::number((y - pos.y()) / gridSize));

    // }
    // for (int y = -gridSize + pos.y(); y >= -size.height() / 2; y -= gridSize) { // сетка горизонт +
    //     painter->setPen(gridPen);
    //     painter->drawLine(-size.width() / 2, y, size.width() / 2, y);
    //     painter->setPen(defPen);
    //     painter->drawText(5 + pos.x(), y + 5, QString::number((y - pos.y()) / gridSize));
    // }
    // for (int x = gridSize + pos.x(); x <= size.width() / 2; x += gridSize) {
    //     painter->setPen(gridPen);
    //     painter->drawLine(x, -size.height() / 2, x, size.height() / 2);
    //     painter->setPen(defPen);
    //     painter->drawText(x - 5, -3 + pos.y(), QString::number((x - pos.x()) / gridSize));

    // }
    // for (int x = -gridSize + pos.x(); x >= -size.width() / 2; x -= gridSize) {
    //     painter->setPen(gridPen);
    //     painter->drawLine(x, -size.height() / 2, x, size.height() / 2);
    //     painter->setPen(defPen);
    //     painter->drawText(x - 5, -3 + pos.y(), "-" + QString::number((x - pos.x()) / gridSize));
    // }
    // // Рисуем оси
    // QPen axisPen(Qt::black, 2);
    // painter->setPen(axisPen);
    // painter->drawLine(-size.width() / 2, pos.y(), size.width() / 2, pos.y()); // оcь x
    // painter->drawLine(pos.x(), -size.height() / 2, pos.x(), size.height() / 2); // ось y
}

void GridItem::setGridSize(int gridS)
{
    gridSize = gridS;
    update();
}

void GridItem::addGridSize(int dgridS)
{
    gridSize += dgridS;
    update();
}

void GridItem::setSize(QSizeF size)
{
    this->size = size;
    update();
}

void GridItem::setPos(QPointF pos)
{
    this->pos = pos;
    update();
}
