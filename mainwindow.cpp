#include "mainwindow.h"
#include "explineedit.h"
#include <QMenuBar>
#include <QAction>
#include <QInputDialog>
#include <QDockWidget>
#include <QLayout>
#include <QPushButton>
#include <QListWidgetItem>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 500);
    paintArea = new PaintingArea(QRect(0, 0, minimumWidth(), minimumHeight()), this);
    setCentralWidget(paintArea);

    QDockWidget *dock = new QDockWidget(tr("Функции"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    QWidget *dockContent = new QWidget(dock);
    QVBoxLayout *layout = new QVBoxLayout(dockContent);

    functionList = new QListWidget(dockContent);
    functionList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    functionList->setIconSize(QSize(20, 20));
    functionList->addItem("");
    layout->addWidget(functionList);

    layout->addStretch();
    dockContent->setLayout(layout);
    dock->setWidget(dockContent);

    connect(functionList, &QListWidget::itemDoubleClicked, this, &MainWindow::changeGraph);
    connect(functionList, &QListWidget::itemSelectionChanged, this, &MainWindow::setSelectionExp);
}

MainWindow::~MainWindow() {}


void MainWindow::changeGraph(QListWidgetItem *item)
{
    ExpLineEdit *editExp = new ExpLineEdit(item->text());
    QListWidgetItem *currentItem;
    if(item->text().trimmed() == "")
    {
        functionList->removeItemWidget(item);
        delete item;
        QListWidgetItem *newItem = new QListWidgetItem("");
        currentItem = newItem;
        functionList->addItem(newItem);
        functionList->setItemWidget(newItem, editExp);
        editExp->setFocus();
        functionList->addItem("");
        paintArea->getScene()->addExp(".");
    }
    else
    {
        currentItem = item;
        functionList->setItemWidget(item, editExp);
    }
    connect(editExp, &QLineEdit::editingFinished, this, [this, currentItem, editExp]() {
        changeGraphFinish(currentItem, editExp);
    });
    connect(editExp, &QLineEdit::inputRejected, this, [this, currentItem, editExp]() {
        changeGraphFinish(currentItem, editExp);
    });
}

void MainWindow::changeGraphFinish(QListWidgetItem *item, QLineEdit *editExp)
{
    if(editExp->text().trimmed() == "")
    {
        paintArea->getScene()->deleteExp(functionList->row(item));
        functionList->removeItemWidget(item);
        functionList->takeItem(functionList->row(item));
        return;
    }
    MathExpression *newMathExp = new MathExpression(editExp->text());
    if(!newMathExp->isValid())
    {
        QIcon icon = functionList->style()->standardIcon(QStyle::SP_MessageBoxWarning);
        item->setIcon(icon);
    }
    else
    {
        item->setIcon(QIcon());
    }
    paintArea->getScene()->getExps().at(functionList->row(item))->setExp(newMathExp);
    item->setText(editExp->text());
    paintArea->getScene()->updateItemsDraw();
    functionList->removeItemWidget(item);
    delete editExp;
    setSelectionExp();
}

void MainWindow::setSelectionExp()
{
    QPen curPen;
    QList<ExpressionItem*> expItems = paintArea->getScene()->getExps();
    for(int i = 0; i < expItems.size(); i++)
    {
        curPen = expItems[i]->getPen();
        curPen.setWidth(2);
        expItems[i]->setPen(curPen);
    }
    QList<QListWidgetItem*> selectedItems = functionList->selectedItems();
    for(int i = 0; i < selectedItems.size(); i++)
    {
        if(selectedItems[i]->text().trimmed() == "")
            continue;
        curPen = expItems[functionList->row(selectedItems[i])]->getPen();
        curPen.setWidth(4);
        expItems[functionList->row(selectedItems[i])]->setPen(curPen);
    }
    paintArea->getScene()->updateItemsDraw();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        QList<QListWidgetItem*> selectedItems = functionList->selectedItems();
        for(int i = selectedItems.size() - 1; i >= 0; i--)
        {
            if(selectedItems[i]->text().trimmed() == "")
                continue;
            int row = functionList->row(selectedItems[i]);
            paintArea->getScene()->deleteExp(row);
            functionList->takeItem(row);

        }
    }
}


