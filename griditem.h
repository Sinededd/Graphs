#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>


class GridItem : public QGraphicsItem
{
public:
    GridItem(int gridSize, QGraphicsItem *parent = nullptr);

    void addGridSize(int dgridS);
    qreal GridSize() { return gridSize / division; }


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    int gridSize;
    double division = 1;
    QPointF pos = QPointF(100, 0);
};

#endif // GRIDITEM_H
