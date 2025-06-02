#include "paintingarea.h"
#include "qtimer.h"


PaintingArea::PaintingArea(QRect rect, QWidget *parent, Qt::WindowFlags f)
    : QWidget{parent, f}
{
    setFocusPolicy(Qt::StrongFocus);
    this->setGeometry(0, 0, rect.width(), rect.height());
    view = new QGraphicsView(this);
    view->setGeometry(rect);
    scene = new PaintingScene();
    scene->setSceneRect(view->geometry());
    view->setScene(scene);
    view->viewport()->resize(this->size() - QSize(2, 25));
    QTimer::singleShot(0, this, [this]() {
        QResizeEvent resizeEvent(this->size(), this->size());
        this->resizeEvent(&resizeEvent);
});
}

void PaintingArea::resizeEvent(QResizeEvent *event)
{
    view->setGeometry(0, 0, event->size().width(), event->size().height());
    scene->setSceneRect(view->viewport()->geometry());
    scene->updateItemsDraw();
    QWidget::resizeEvent(event);
}

void PaintingArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        scene->getGrid()->addGridSize(5);
        scene->updateItemsDraw();
        scene->update();
    }
    if(event->key() == Qt::Key_W)
    {
        scene->getGrid()->addGridSize(-5);
        scene->updateItemsDraw();
        scene->update();
    }
}

void PaintingArea::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();
    if(delta > 0)
    {
        scene->getGrid()->addGridSize(5);
        scene->updateItemsDraw();
        scene->update();
    }
    else if(delta < 0)
    {
        scene->getGrid()->addGridSize(-5);
        scene->updateItemsDraw();
        scene->update();
    }
    event->accept();
}
