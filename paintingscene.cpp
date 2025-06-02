#include "paintingscene.h"
#include "sceneitem.h"
#include "expressionitem.h"
#include "Math/mathexpression.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QTime>
#include <QGraphicsView>


PaintingScene::PaintingScene(QObject *parent)
    : QGraphicsScene(parent)
{
    connect(this, &QGraphicsScene::sceneRectChanged, this, &PaintingScene::initGrid);
}

MathExpression *PaintingScene::addExp(QString exp)
{
    MathExpression *mathExp = new MathExpression(exp);
    QRandomGenerator generator(QTime::currentTime().msec());
    ExpressionItem *newExp = new ExpressionItem(mathExp, gridItem, QColor(generator.bounded(180), generator.bounded(180), generator.bounded(180)));
    addItemInCenter(newExp);
    return mathExp;
}

void PaintingScene::deleteExp(int i)
{
    ExpressionItem* item = exps[i];
    exps.removeAt(i);
    item->remove();
}

SceneItem* PaintingScene::addItemInCenter(SceneItem *item)
{
    ExpressionItem* exp = dynamic_cast<ExpressionItem*>(item);
    if(exp != nullptr)
        exps.push_back(exp);
    group_->setPos(0, 0);
    QList<QGraphicsItem*> items = group_->childItems();
    for(QGraphicsItem* item : std::as_const(items))
    {
        dynamic_cast<SceneItem*>(item)->updateDraw();
    }
    item->updateDraw();
    group_->addToGroup(item);
    return item;
}

void PaintingScene::updateItemsDraw()
{
    QList<QGraphicsItem*> items = group_->childItems();
    for(QGraphicsItem* item : std::as_const(items))
    {
        dynamic_cast<SceneItem*>(item)->updateDraw();
    }
    update();
}

void PaintingScene::initGrid()
{
    group_ = this->createItemGroup(selectedItems());
    gridItem = new GridItem(50);
    addItem(gridItem);
    disconnect(this, &QGraphicsScene::sceneRectChanged, this, &PaintingScene::initGrid);
}
