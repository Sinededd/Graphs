#include "mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QInputDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // setMinimumSize(700, 480);
    setMinimumSize(250, 250);
    paintArea = new PaintingArea(QRect(0, 0, this->minimumWidth(), this->minimumHeight()), this);
    setCentralWidget(paintArea);

    QAction *addExpAction = new QAction("Добавить");
    connect(addExpAction, &QAction::triggered, this, &MainWindow::addGraph);
    this->menuBar()->addAction(addExpAction);
}

MainWindow::~MainWindow() {}

void MainWindow::addGraph()
{
    bool ok{};
    QString text = QInputDialog::getText(this, tr("Функция"),
                                         tr("Введите функцию:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
        paintArea->AddExpression(text);
}
