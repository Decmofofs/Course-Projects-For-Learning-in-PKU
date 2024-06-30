#include "mainwindow.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QMouseEvent>
#include <QLabel>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureWidget::filerootApplication = &a;


    MainWindow w;
    w.show();

    return a.exec();
}
