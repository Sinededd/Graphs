#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("/home/denis/study/Course_work/Graphs/Geoo/Geoo.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
