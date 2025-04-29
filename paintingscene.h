#ifndef PAINTINGSCENE_H
#define PAINTINGSCENE_H

#include "griditem.h"
#include "mathexpression.h"

#include <QObject>
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>


class PaintingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintingScene(QRect rect, QObject *parent = nullptr);
    GridItem *Grid() {return gridItem; }
    MathExpression *AddExpression(QString exp);
    MathExpression *AddExpression(MathExpression *exp);
    // void updateExp

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    GridItem *gridItem = nullptr;
    QList<MathExpression *> expressionList;

    QPointF lastPos;

    void drawGrid();
};

#endif // PAINTINGSCENE_H
