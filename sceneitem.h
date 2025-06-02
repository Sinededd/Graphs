#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#include <QThread>

class SceneItemController;

class SceneItem : public QGraphicsItem
{
public:
    SceneItem(QGraphicsItem *parent = nullptr);
    virtual ~SceneItem();
    void updateDraw();
    QPen getPen() { return pen; }
    void setPen(QPen pen) {this->pen = pen; }
    QRectF getRect();

    virtual void draw(QPainterPath *path);
    void setPath(const QPainterPath &newPath);
    void remove();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    SceneItemController *controller;
    QPainterPath *path;
    QPen pen;
};

#endif // SCENEITEM_H
