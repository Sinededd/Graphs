#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QGraphicsScene>
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
    QPen pen() { return pen_; }
    void setPen(QPen pen) {pen_ = pen; }

protected:
    virtual void draw(QPainterPath *path);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    double offsetSize_ = 0.5;
    QPainterPath *path;
    int state;
    QPen pen_;
};

#endif // SCENEITEM_H
