#include "sceneitem.h"
#include <QGraphicsScene>
#include "paintingscene.h"

SceneItem::SceneItem(QGraphicsItem *parent) : QGraphicsItem(parent), state(0)
{
    path = new QPainterPath();
    this->setFlag(ItemIsMovable);
}

SceneItem::~SceneItem()
{
    delete path;
}

void SceneItem::updateDraw()
{
    qInfo() << "updateDraw";
    state = (state + 1) % 2;
    path->clear();
    draw(path);
    update();
}

double SceneItem::offsetSize()
{
    return dynamic_cast<PaintingScene*>(scene())->offsetSize();
}

QRectF SceneItem::offsetRect()
{
    double k = dynamic_cast<PaintingScene*>(scene())->offsetSize();
    return QRectF(-scene()->sceneRect().width() * (k + 0.5), -scene()->sceneRect().height() * (k + 0.5), scene()->sceneRect().width() * (k * 2 + 1), scene()->sceneRect().height() * (k * 2 + 1));
}

void SceneItem::draw(QPainterPath *path)
{
    if (state == 0) {
        path->addRect(-4, -4, 8, 8);
    } else {
        path->addEllipse(-4, -4, 8, 8);
    }
}

QRectF SceneItem::boundingRect() const
{
    double k = dynamic_cast<PaintingScene*>(scene())->offsetSize();
    return QRectF(-scene()->sceneRect().width() * k, -scene()->sceneRect().height() * k, scene()->sceneRect().width() * (k * 2 + 1), scene()->sceneRect().height() * (k * 2 + 1));
}

void SceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    painter->setPen(Qt::black);
    painter->setBrush(Qt::transparent);
    painter->translate(boundingRect().center());
    painter->scale(1, -1);
    painter->drawPath(*path);
}

