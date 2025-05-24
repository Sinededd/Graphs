#ifndef GRIDITEM_H
#define GRIDITEM_H

#include "sceneitem.h"
#include <QGraphicsItem>
#include <QPainter>

class GridArrows : public SceneItem
{
public:
    GridArrows () {}
protected:
    void draw(QPainterPath *path) override;
};

class GridItem : public SceneItem
{
public:
    GridItem(int gridSize, QGraphicsItem *parent = nullptr);

    void setGridSize(int gridS);
    void addGridSize(int dgridS);
    int GridSize() { return gridSize; }
    bool isCurrentDraw() { return isCurrentDraw_; }
    void setCurrentDraw(bool is = true) { isCurrentDraw_ = is; }
    void setSize(QSizeF size);
    QSizeF Size() {return size; }
    void setPos(QPointF pos);
    QPointF Pos() {return pos; }

protected:
    void draw(QPainterPath *path) override;

private:
    int gridSize;
    bool isCurrentDraw_ = 0;
    QSizeF size;
    QPointF pos;
};

#endif // GRIDITEM_H
