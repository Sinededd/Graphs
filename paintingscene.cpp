#include "paintingscene.h"
#include "griditem.h"
#include "expressionitem.h"
#include <QRandomGenerator>
#include <QTime>
// #include <QRectF>

PaintingScene::PaintingScene(QRect rect, QObject *parent)
    : QGraphicsScene{parent}
{
    this->setSceneRect(QRect(-rect.width() / 2, -rect.height() / 2, rect.width(), rect.height()));
    gridItem = new GridItem(this->sceneRect().size(), 30);
    this->addItem(gridItem);
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
    new ExpressionItem(mathExp, gridItem, QColor(generator.bounded(180), generator.bounded(180), generator.bounded(180)));
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

void PaintingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    gridItem->setPos(lastPos + mouseEvent->scenePos() - mouseEvent->buttonDownScenePos(Qt::LeftButton));
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void PaintingScene::drawGrid()
{
    // scene->addLine(-scene->sceneRect().width() / 2, 0, 0, 0, QPen(Qt::black, 2));
    // scene->addLine(0, -200, 0, 200, QPen(Qt::black, 2));

    // // Добавляем стрелки на концах осей
    // // Стрелка для оси X (справа)
    // scene->addLine(200, 0, 190, 10, QPen(Qt::black, 2));
    // scene->addLine(200, 0, 190, -10, QPen(Qt::black, 2));
    // // Стрелка для оси Y (сверху)
    // scene->addLine(0, -200, 10, -190, QPen(Qt::black, 2));
    // scene->addLine(0, -200, -10, -190, QPen(Qt::black, 2));
}
