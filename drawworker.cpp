#include "drawworker.h"

DrawWorker::DrawWorker(SceneItem *sceneItem, QObject *parent)
    : QObject{parent}, sceneItem{sceneItem}
{}

void DrawWorker::computePath()
{
    QPainterPath newPath;
    sceneItem->draw(&newPath);
    emit pathComputed(newPath);
}
