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

    //Expression
    MathExpression *addExp(QString exp);
    void deleteExp(int i);

    //Grid
    GridItem* getGrid() {return gridItem; }
    QList<ExpressionItem*> getExps() {return exps; }

    // service
    void updateItemsDraw();

private slots:
    void initGrid();

private:
    SceneItem* addItemInCenter(SceneItem *item);

    QGraphicsItemGroup *group_;
    QList<ExpressionItem*> exps;
    static QPointF offsetPos_;
    constexpr static double offsetSize_ = 0.5;

    GridItem *gridItem;
};

#endif // PAINTINGSCENE_H
