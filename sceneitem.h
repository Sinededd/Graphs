#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>

class SceneItem : public QGraphicsItem
{
public:
    SceneItem(QGraphicsItem *parent = nullptr);
    ~SceneItem();
    void updateDraw();
    double offsetSize();
    QRectF offsetRect();

protected:
    virtual void draw(QPainterPath *path);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    QPainterPath *path;
    int state;
};

#endif // SCENEITEM_H
