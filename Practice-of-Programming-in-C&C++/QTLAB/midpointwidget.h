#ifndef MIDPOINTWIDGET_H
#define MIDPOINTWIDGET_H

#include <QWidget>
#include <QInputDialog>
#include "picturewidget.h"
#include "MidPoint.h"
#include <QThread.h>


namespace Ui {
class MidPointWidget;
}

class MidPointWidget : public PictureWidget
{
    Q_OBJECT

public:
    explicit MidPointWidget(unsigned lup = 127, unsigned ldown = 127, unsigned rup = 127, unsigned rdown = 127,
                            unsigned height = 300, unsigned width = 400, unsigned seed = 0,
                            double range = 40, unsigned height_limit=255,
                            QWidget *parent = nullptr);
    ~MidPointWidget();

    unsigned lup;
    unsigned ldown;
    unsigned rup;
    unsigned rdown;
    unsigned height;
    unsigned width;
    unsigned seed;
    double range;
    unsigned height_limit;
    QThread* m2dthread;
    MidPointCal* m2dcal;


    void Paint();

private slots:
    void on_start_clicked();
    void on_Printer_clicked();
    void on_reset_clicked();
    void on_Get3DView_clicked();

    void on_SetLU_clicked();
    void on_SetLD_clicked();
    void on_SetRU_clicked();
    void on_SetRD_clicked();

    void on_SetSeed_clicked();

    void on_SetHeight_clicked();
    void on_SetWidth_clicked();

    void on_SetRange_clicked();

private:
    Ui::MidPointWidget *ui;
};

#endif // MIDPOINTWIDGET_H
