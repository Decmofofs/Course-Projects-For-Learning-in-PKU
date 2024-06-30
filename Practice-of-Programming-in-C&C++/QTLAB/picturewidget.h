#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "setcolor.h"

namespace Ui {
class PictureWidget;
}

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    static QApplication* filerootApplication;
    static QQmlApplicationEngine* engine;
    static SetColor* setcolorWidget;
    static int MeshStyle;
    static int PrinterStyle;

    explicit PictureWidget(QWidget *parent = nullptr);
    virtual ~PictureWidget();

    QImage* image;

    void Print(const char* file);

private slots:
    void on_pushButton_clicked();

private:
    Ui::PictureWidget *ui;
};

#endif // PICTUREWIDGET_H
