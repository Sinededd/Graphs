#include "sceneitem.h"
#include "sceneitemcontroller.h"
#include <QGraphicsScene>


SceneItem::SceneItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    path = new QPainterPath();
    controller = new SceneItemController(this);
}

SceneItem::~SceneItem()
{
    delete path;
}

void SceneItem::updateDraw()
{
    if(controller == nullptr)
        return;
    controller->updateDraw();
}

QRectF SceneItem::getRect()
{
    QRectF rect = boundingRect();
    rect.moveTo(-boundingRect().width() / 2, -boundingRect().height() / 2);
    return rect;
}

void SceneItem::draw(QPainterPath *path)
{}

void SceneItem::setPath(const QPainterPath &newPath)
{
    *path = newPath;
    update();
}

void SceneItem::remove()
{
    delete controller;
    controller = nullptr;
    scene()->removeItem(this);
}

QRectF SceneItem::boundingRect() const
{
    return QRectF(0, 0, scene()->sceneRect().width(), scene()->sceneRect().height());
}

void SceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(pen);
    painter->setBrush(Qt::transparent);
    painter->translate(boundingRect().center());
    painter->scale(1, -1);
    painter->drawPath(*path);
}

