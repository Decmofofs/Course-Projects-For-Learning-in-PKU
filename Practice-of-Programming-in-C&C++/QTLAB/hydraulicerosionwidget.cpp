#include "hydraulicerosionwidget.h"
#include "ui_hydraulicerosionwidget.h"
#include "view3dwidget.h"


HydraulicErosionWidget::HydraulicErosionWidget(unsigned seed, unsigned T,
                                   QWidget *parent) :
    PictureWidget(parent),
    seed(seed), T(T),
    ui(new Ui::HydraulicErosionWidget)
{
    ui->setupUi(this);

    e2dcal = new HydraulicErosionCal(this->seed, this->T);
    e2dthread = new QThread;

    e2dcal->moveToThread(e2dthread);

    // QObject::connect(v2dcal, &ValueNoiseCal::ToDo, v2dcal, &ValueNoiseCal::work);

    e2dthread->start();
}

void HydraulicErosionWidget::on_Get3DView_clicked()
{

    if (view3dwidget::View3DPlayer) delete view3dwidget::View3DPlayer;
    view3dwidget::View3DPlayer = new view3dwidget("hydraulicerosionmesh");

    emit view3dwidget::View3DPlayer->ToDo();

}

HydraulicErosionWidget::~HydraulicErosionWidget()
{
    delete ui;
    if(e2dcal) delete e2dcal;
    if(e2dthread) {
        e2dthread->exit();
        delete e2dthread;
    }
}

void HydraulicErosionWidget::Paint() {
    // v2dcal->work();
    emit e2dcal->ToDo();
}

void HydraulicErosionWidget::on_start_clicked()
{
    this->Paint();
}
void HydraulicErosionWidget::on_Printer_clicked()
{
    this->Print("./HydraulicErosionGraph.bmp");
}
void HydraulicErosionWidget::on_reset_clicked()
{
    this->seed = 0;
    this->T = 1000;

    this->ui->SetSeed->setText("种子：0");
    this->ui->SetT->setText("模拟次数：1000");
}

void HydraulicErosionWidget::on_SetSeed_clicked()
{
    unsigned rseed = (unsigned)time(0);
    rseed = unsigned((rseed % 65536) * (rseed % 65536) * (rseed % 1024) + 1127 * rseed + 1898) / 2;
    int seedrec = QInputDialog::getInt(this, QString("Set seed"), QString("new seed :"), this->seed, -1, 2147483647, 1);
    if (seedrec == -1) this->seed = rseed;
    else this->seed = seedrec;
    this->ui->SetSeed->setText(QString("种子：" + QString::number(this->seed)));
}


void HydraulicErosionWidget::on_SetT_clicked()
{
    this->T = QInputDialog::getInt(this, QString("模拟次数"), QString("请输入一个1-100000的整数"), this->T, 1, 100000, 1);
    this->ui->SetT->setText(QString("模拟次数：") + QString::number(this->T));
}

