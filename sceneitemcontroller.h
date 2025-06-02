#ifndef SCENEITEMCONTROLLER_H
#define SCENEITEMCONTROLLER_H

#include <QObject>
#include <QPainterPath>

class SceneItem;
class DrawWorker;

class SceneItemController : public QObject
{
    Q_OBJECT
public:
    explicit SceneItemController(SceneItem *item, QObject *parent = nullptr);
    ~SceneItemController();

    void updateDraw();

signals:
    void startComputation();

private slots:
    void onPathComputed(const QPainterPath &newPath);

private:
    SceneItem *sceneItem;
    DrawWorker *drawWorker;
    QThread *thread;
};

#endif // SCENEITEMCONTROLLER_H
