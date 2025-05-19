#include "paintingscene.h"
#include "sceneitem.h"
#include "expressionitem.h"
#include "Math/mathexpression.h"
#include <QRandomGenerator>
#include <QTime>
#include <QGraphicsView>
// #include <QRectF>

PaintingScene::PaintingScene(QObject *parent)
    : QGraphicsScene(parent)
{
    // SceneItem *item = new SceneItem();
    // item->updateDraw();
    group_ = this->createItemGroup(this->selectedItems());
    gridItem = new GridItem(10);
    addItem(gridItem);
    // group_->setFlag(QGraphicsItem::ItemIsMovable);
}

MathExpression *PaintingScene::AddExpression(QString exp)
{
    // addItemInCenter(new SceneItem());

    MathExpression *mathExp = new MathExpression(exp);
    if(!mathExp->isValid())
    {
        delete mathExp;
        return nullptr;
    }
    // expressionList.push_back(mathExp);
    QRandomGenerator generator(QTime::currentTime().msec());
    ExpressionItem *newExp = new ExpressionItem(mathExp, gridItem, QColor(generator.bounded(180), generator.bounded(180), generator.bounded(180)));
    addItemInCenter(newExp);
    // groupExpressions->addToGroup(newExp);
    // expressionItems.push_back(newExp);
    // return mathExp;
    return mathExp;
}

MathExpression *PaintingScene::AddExpression(MathExpression *exp)
{
    // expressionList.push_back(exp);
    // new ExpressionItem(exp, gridItem);
    // return exp;
    return new MathExpression("x");
}

SceneItem* PaintingScene::addItemInCenter(SceneItem *item)
{
    group_->setPos(0, 0);
    QList<QGraphicsItem*> items = group_->childItems();
    for(QGraphicsItem* item : std::as_const(items))
    {
        dynamic_cast<SceneItem*>(item)->updateDraw();
    }
    dynamic_cast<SceneItem*>(item)->updateDraw();
    // this->addItem(item);
    group_->addToGroup(item);
    return item;
}

void PaintingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    group_->moveBy(mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x(), mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y());
    if(qAbs(group_->pos().x()) > sceneRect().width() * offsetSize_ || qAbs(group_->pos().y()) > sceneRect().height() * offsetSize_)
    {
        // qInfo() << group_->pos();
        group_->setPos(0, 0);
        QList<QGraphicsItem*> items = group_->childItems();
        for(QGraphicsItem* item : std::as_const(items))
        {
            dynamic_cast<SceneItem*>(item)->updateDraw();
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
