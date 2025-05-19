#include "paintingarea.h"


PaintingArea::PaintingArea(QRect rect, QWidget *parent, Qt::WindowFlags f)
    : QWidget{parent, f}
{
    this->setGeometry(0, 0, rect.width(), rect.height());
    view = new QGraphicsView(this);
    view->setGeometry(rect);
    scene = new PaintingScene();
    scene->setSceneRect(view->geometry());
    view->setScene(scene);
    view->viewport()->resize(this->size() - QSize(2, 25));
}

void PaintingArea::resizeEvent(QResizeEvent *event)
{
    view->setGeometry(0, 0, event->size().width(), event->size().height());
    scene->setSceneRect(view->viewport()->geometry());
    QWidget::resizeEvent(event);
}

void PaintingArea::keyPressEvent(QKeyEvent *event)
{
    // if(event->key() == Qt::Key_Q)
    // {
    //     scene->Grid()->addGridSize(-5);
    // }
    // if(event->key() == Qt::Key_W)
    // {
    //     scene->Grid()->addGridSize(5);
    // }
    // if(event->key() == Qt::Key_S)
    // {
    //     scene->Grid()->setPos(scene->Grid()->Pos() + QPointF(5, 5));
    // }
    // if(event->key() == Qt::Key_A)
    // {
    //     scene->Grid()->setPos(scene->Grid()->Pos() + QPointF(-5, -5));
    // }
    if(event->key() == Qt::Key_Z)
    {
        dynamic_cast<SceneItem*>(scene->items().at(0))->updateDraw();
    }
}
