#ifndef VALUENOISEWIDGET_H
#define VALUENOISEWIDGET_H

#include <QWidget>
#include <QInputDialog>
#include "picturewidget.h"
#include "valuenoise.h"
#include <QThread.h>


namespace Ui {
class ValueNoiseWidget;
}

class ValueNoiseWidget : public PictureWidget
{
    Q_OBJECT

public:
    explicit ValueNoiseWidget(unsigned height = 3, unsigned width = 4, unsigned precision = 100, unsigned seed = 0,
                              unsigned height_limit = 255, smoothFunc useFunction = C1Polynomial,
                              QWidget *parent = nullptr);
    ~ValueNoiseWidget();

    unsigned height;
    unsigned width;
    unsigned precision;
    unsigned seed;
    unsigned height_limit;
    smoothFunc useFunction;
    QThread* v2dthread;
    ValueNoiseCal* v2dcal;


    void Paint();

private slots:
    void on_start_clicked();
    void on_Printer_clicked();

    void on_SetInterval_valueChanged(int value);


    void on_SetWidth_valueChanged(int value);

    void on_SetHeight_valueChanged(int value);

    void on_SetSeed_clicked();

    void on_reset_clicked();

    void on_Get3DView_clicked();

private:
    Ui::ValueNoiseWidget *ui;
};

#endif // VALUENOISEWIDGET_H
