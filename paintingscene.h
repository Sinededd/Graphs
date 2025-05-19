#ifndef PAINTINGSCENE_H
#define PAINTINGSCENE_H

#include "Math/mathexpression.h"
#include "expressionitem.h"
#include "griditem.h"


#include <QObject>
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>


class PaintingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintingScene(QObject *parent = nullptr);
    MathExpression *AddExpression(QString exp);
    MathExpression *AddExpression(MathExpression *exp);
    SceneItem* addItemInCenter(SceneItem *item);

    double offsetSize() { return offsetSize_; }
    void updateOffsetPos() { offsetPos_ = mouseGrabberItem()->scenePos(); }


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    double offsetSize_ = 0.5;
    QGraphicsItemGroup *group_;
    QPointF offsetPos_ = QPointF(0, 0);

    GridItem *gridItem;
};

#endif // PAINTINGSCENE_H
