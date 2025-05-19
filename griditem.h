#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>

class GridItem : public QGraphicsItem
{
public:
    GridItem(int gridSize, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    void setGridSize(int gridS);
    void addGridSize(int dgridS);
    int GridSize() { return gridSize; }
    bool isCurrentDraw() { return isCurrentDraw_; }
    void setCurrentDraw(bool is = true) { isCurrentDraw_ = is; }


    void setSize(QSizeF size);
    QSizeF Size() {return size; }
    void setPos(QPointF pos);
    QPointF Pos() {return pos; }
private:
    int gridSize;
    bool isCurrentDraw_ = 0;
    QSizeF size;
    QPointF pos;
};

#endif // GRIDITEM_H
