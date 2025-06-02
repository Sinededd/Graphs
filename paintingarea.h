#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H
#include "paintingscene.h"

#include <QWidget>
#include <QGraphicsView>
#include <QResizeEvent>


class PaintingArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintingArea(QRect rect, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    PaintingScene* getScene() {return scene; }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsView *view;
    PaintingScene *scene;

};

#endif // PAINTINGAREA_H
