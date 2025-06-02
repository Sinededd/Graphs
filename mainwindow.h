#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include "paintingarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeGraph(QListWidgetItem *item);
    void changeGraphFinish(QListWidgetItem *item, QLineEdit *editExp);
    void setSelectionExp();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    PaintingArea *paintArea;
    QListWidget *functionList;
};
#endif // MAINWINDOW_H
