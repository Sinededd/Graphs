#include "paintingscene.h"
#include "griditem.h"
#include "expressionitem.h"
#include <QRandomGenerator>
#include <QTime>
#include <QGraphicsView>
// #include <QRectF>

PaintingScene::PaintingScene(QRect rect, QObject *parent)
    : QGraphicsScene{parent}
{
    this->setSceneRect(QRect(-rect.width() / 2, -rect.height() / 2, rect.width(), rect.height()));
    gridItem = new GridItem(this->sceneRect().size(), 30);
    this->addItem(gridItem);
    groupExpressions = this->createItemGroup(this->selectedItems());
    groupExpressions->setFlag(QGraphicsItem::ItemIsMovable);
}

MathExpression *PaintingScene::AddExpression(QString exp)
{
    MathExpression *mathExp = new MathExpression(exp);
    if(!mathExp->isValid())
    {
        delete mathExp;
        return nullptr;
    }
    expressionList.push_back(mathExp);
    QRandomGenerator generator(QTime::currentTime().msec());
    ExpressionItem *newExp = new ExpressionItem(mathExp, gridItem, QColor(generator.bounded(180), generator.bounded(180), generator.bounded(180)));
    groupExpressions->addToGroup(newExp);
    expressionItems.push_back(newExp);
    return mathExp;
}

MathExpression *PaintingScene::AddExpression(MathExpression *exp)
{
    expressionList.push_back(exp);
    new ExpressionItem(exp, gridItem);
    return exp;
}

void PaintingScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    lastPos = gridItem->Pos();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

//////////////////////////////////
/// Нужно соединить renderK из PaingScene с ExpressionItem;
int renderK = 3;
QPointF poi = QPointF(0, 0);
void PaintingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    gridItem->setPos(lastPos + mouseEvent->scenePos() - mouseEvent->buttonDownScenePos(Qt::LeftButton));
    if(qAbs(groupExpressions->pos().x()) > gridItem->Size().width() / 2 * renderK || qAbs(groupExpressions->pos().y()) > gridItem->Size().height() / 4 * renderK)
    {
        if(qAbs(groupExpressions->pos().x() - poi.x()) > gridItem->Size().width() / 2 * renderK || qAbs(groupExpressions->pos().y() + poi.y()) > gridItem->Size().height() / 4 * renderK)
        {
            poi = QPointF(0, 0);
            gridItem->setCurrentDraw(false);
        }

        // qInfo() << groupExpressions->pos() - poi;
        if(poi == QPointF(0, 0))
        {
            poi = groupExpressions->pos();

        }
        groupExpressions->setPos(groupExpressions->pos() - poi);
        update();
    }
}
