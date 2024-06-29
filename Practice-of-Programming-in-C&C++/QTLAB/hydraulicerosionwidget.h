#ifndef HYDRAULICEROSIONWIDGET_H
#define HYDRAULICEROSIONWIDGET_H

#include <QWidget>
#include <QInputDialog>
#include "picturewidget.h"
#include "HydraulicErosion.h"
#include <QThread.h>


namespace Ui {
class HydraulicErosionWidget;
}

class HydraulicErosionWidget : public PictureWidget
{
    Q_OBJECT

public:
    explicit HydraulicErosionWidget(unsigned seed = 0, unsigned T = 1000,
                                    QWidget *parent = nullptr);
    ~HydraulicErosionWidget();

    unsigned seed;
    unsigned T;
    QThread* e2dthread;
    HydraulicErosionCal* e2dcal;


    void Paint();

private slots:
    void on_start_clicked();
    void on_Printer_clicked();
    void on_reset_clicked();
    void on_Get3DView_clicked();

    void on_SetSeed_clicked();
    void on_SetT_clicked();

private:
    Ui::HydraulicErosionWidget *ui;
};

#endif // HYDRAULICEROSIONWIDGET_H
