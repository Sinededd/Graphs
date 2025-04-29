#include "paintingarea.h"


PaintingArea::PaintingArea(QRect rect, QWidget *parent, Qt::WindowFlags f)
    : QWidget{parent, f}
{
    view = new QGraphicsView(this);
    view->setGeometry(rect);
    scene = new PaintingScene(rect);
    view->setScene(scene);
    // view->setRenderHint(QPainter::Antialiasing);
    // view->setAlignment(Qt::AlignCenter);
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void PaintingArea::resizeEvent(QResizeEvent *event)
{

    view->setGeometry(0, 0, event->size().width(), event->size().height());
    scene->setSceneRect(-event->size().width() / 2 + 5, -event->size().height() / 2 + 5, event->size().width() - 5, event->size().height() - 5);
    scene->Grid()->setSize(event->size());

    // static_cast<QGraphicsRectItem *>(scene->Scene()->items().at(0))->setRect(0, 0, event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
}

void PaintingArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        scene->Grid()->addGridSize(-5);
    }
    if(event->key() == Qt::Key_W)
    {
        scene->Grid()->addGridSize(5);
    }
    if(event->key() == Qt::Key_S)
    {
        scene->Grid()->setPos(scene->Grid()->Pos() + QPointF(5, 5));
    }
    if(event->key() == Qt::Key_A)
    {
        scene->Grid()->setPos(scene->Grid()->Pos() + QPointF(-5, -5));
    }
}
