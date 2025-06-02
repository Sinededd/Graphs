#ifndef DRAWWORKER_H
#define DRAWWORKER_H

#include "sceneitem.h"
#include <QPainterPath>
#include <QObject>

class DrawWorker : public QObject
{
    Q_OBJECT
public:
    explicit DrawWorker(SceneItem *scene, QObject *parent = nullptr);

public slots:
    void computePath();

signals:
    void pathComputed(const QPainterPath &path);

private:
    SceneItem *sceneItem;

};

#endif // DRAWWORKER_H
