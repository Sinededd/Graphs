#ifndef PAINTINGSCENE_H
#define PAINTINGSCENE_H

#include "Math/mathexpression.h"
#include "expressionitem.h"
#include "griditem.h"

#include <QGraphicsItem>
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

    void updateOffsetPos() { PaintingScene::offsetPos_ = mouseGrabberItem()->scenePos();}

    void updateItemsDraw();


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private slots:
    void initGrid();

private:
    QGraphicsItemGroup *group_;
    QList<QGraphicsItem*> sceneItems;
    static QPointF offsetPos_;
    constexpr static double offsetSize_ = 0.5;

    GridItem *gridItem;
};

#endif // PAINTINGSCENE_H
