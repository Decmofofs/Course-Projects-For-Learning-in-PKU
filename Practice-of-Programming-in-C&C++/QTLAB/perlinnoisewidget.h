#ifndef PERLINNOISEWIDGET_H
#define PERLINNOISEWIDGET_H

#include <QWidget>
#include <QInputDialog>
#include "picturewidget.h"
#include "PerlinNoise.h"
#include <QThread.h>


namespace Ui {
class PerlinNoiseWidget;
}

class PerlinNoiseWidget : public PictureWidget
{
    Q_OBJECT

public:
    explicit PerlinNoiseWidget(unsigned height = 3, unsigned width = 4, unsigned precision = 100, unsigned seed = 0,
                              unsigned height_limit = 255, interpolateFunc useFunction = CosineInterpolate,
                              QWidget *parent = nullptr);
    ~PerlinNoiseWidget();

    unsigned height;
    unsigned width;
    unsigned precision;
    unsigned seed;
    unsigned height_limit;
    interpolateFunc useFunction;
    QThread* p2dthread;
    PerLinNoiseCal* p2dcal;


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
    Ui::PerlinNoiseWidget *ui;
};

#endif // PERLINNOISEWIDGET_H
