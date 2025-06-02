#include "sceneitemcontroller.h"
#include "sceneitem.h"
#include "drawworker.h"

SceneItemController::SceneItemController(SceneItem *item, QObject *parent)
    : QObject{parent}, sceneItem(item)
{
    drawWorker = new DrawWorker(sceneItem);
    thread = new QThread(this);

    drawWorker->moveToThread(thread);
    thread->start();

    connect(this, &SceneItemController::startComputation, drawWorker, &DrawWorker::computePath);
    connect(drawWorker, &DrawWorker::pathComputed, this, &SceneItemController::onPathComputed);
}

SceneItemController::~SceneItemController()
{
    disconnect(this, &SceneItemController::startComputation, drawWorker, &DrawWorker::computePath);
    disconnect(drawWorker, &DrawWorker::pathComputed, this, &SceneItemController::onPathComputed);
    thread->quit();
    thread->wait();
    delete drawWorker;
    drawWorker = nullptr;
}

void SceneItemController::updateDraw()
{
    emit startComputation();
}

void SceneItemController::onPathComputed(const QPainterPath &newPath)
{
    sceneItem->setPath(newPath);
}
