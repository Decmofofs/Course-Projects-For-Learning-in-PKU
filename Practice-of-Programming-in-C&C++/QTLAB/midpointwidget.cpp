#include "midpointwidget.h"
#include "ui_midpointwidget.h"
#include "view3dwidget.h"


MidPointWidget::MidPointWidget(unsigned lup, unsigned ldown, unsigned rup, unsigned rdown,
                               unsigned height, unsigned width, unsigned seed,
                               double range, unsigned height_limit,
                               QWidget *parent) :
    PictureWidget(parent),
    lup(lup), ldown(ldown), rup(rup), rdown(rdown),
    height(height), width(width), seed(seed),
    range(range), height_limit(height_limit),
    ui(new Ui::MidPointWidget)
{
    ui->setupUi(this);

    m2dcal = new MidPointCal(this->lup, this->ldown, this->rup, this->rdown, this->height, this->width, this->seed, this->range, this->height_limit);
    m2dthread = new QThread;

    m2dcal->moveToThread(m2dthread);

    m2dthread->start();
}

MidPointWidget::~MidPointWidget()
{
    delete ui;
    if(m2dcal) delete m2dcal;
    if(m2dthread) {
        m2dthread->exit();
        delete m2dthread;
    }
}

void MidPointWidget::Paint() {
    // m2dcal->work();
    emit m2dcal->ToDo();
}


void MidPointWidget::on_Get3DView_clicked()
{

    if (view3dwidget::View3DPlayer) delete view3dwidget::View3DPlayer;
    view3dwidget::View3DPlayer = new view3dwidget("midpointmesh");

    emit view3dwidget::View3DPlayer->ToDo();

}

void MidPointWidget::on_start_clicked()
{
    this->Paint();
}
void MidPointWidget::on_Printer_clicked()
{
    this->Print("./MidPointGraph.bmp");
}
void MidPointWidget::on_reset_clicked()
{
    this->height = 300;
    this->width = 400;
    this->seed = 0;
    this->height_limit = 255;
    this->ldown = this->rdown = this->lup = this->rup = 0;
    this->range = 40;

    this->ui->SetLU->setText("左上：127");
    this->ui->SetLD->setText("左下：127");
    this->ui->SetRU->setText("右上：127");
    this->ui->SetRD->setText("右下：127");

    this->ui->SetSeed->setText("种子：0");
    this->ui->SetHeight->setText("高度：300");
    this->ui->SetWidth->setText("宽度：400");

    this->ui->SetRange->setText("扰动范围：±40");
}

void MidPointWidget::on_SetLU_clicked() {
    this->lup = QInputDialog::getInt(this, QString("左上"), QString("请输入0-255的整数："), this->lup, 0, 255, 1);
    this->ui->SetLU->setText(QString("左上：") + QString::number(this->lup));
}
void MidPointWidget::on_SetLD_clicked() {
    this->ldown = QInputDialog::getInt(this, QString("左下"), QString("请输入0-255的整数："), this->ldown, 0, 255, 1);
    this->ui->SetLD->setText(QString("左下：") + QString::number(this->ldown));
}
void MidPointWidget::on_SetRU_clicked() {
    this->rup = QInputDialog::getInt(this, QString("右上"), QString("请输入0-255的整数："), this->rup, 0, 255, 1);
    this->ui->SetRU->setText(QString("右上：") + QString::number(this->rup));
}
void MidPointWidget::on_SetRD_clicked() {
    this->rdown = QInputDialog::getInt(this, QString("右下"), QString("请输入0-255的整数："), this->rdown, 0, 255, 1);
    this->ui->SetRD->setText(QString("右下：") + QString::number(this->rdown));
}

void MidPointWidget::on_SetSeed_clicked() {
    unsigned rseed = (unsigned)time(0);
    rseed = unsigned((rseed % 65536) * (rseed % 65536) * (rseed % 1024) + 1127 * rseed + 1898) / 2;
    int seedrec = QInputDialog::getInt(this, QString("Set seed"), QString("new seed :"), this->seed, -1, 2147483647, 1);
    if (seedrec == -1) this->seed = rseed;
    else this->seed = seedrec;
    this->ui->SetSeed->setText(QString("种子：" + QString::number(this->seed)));
}

void MidPointWidget::on_SetHeight_clicked() {
    this->height = QInputDialog::getInt(this, QString("高度"), QString("请输入4-10000的整数："), this->height, 4, 10000, 1);
    this->ui->SetHeight->setText(QString("高度：") + QString::number(this->height));
}
void MidPointWidget::on_SetWidth_clicked() {
    this->width = QInputDialog::getInt(this, QString("宽度"), QString("请输入4-10000的整数："), this->width, 4, 10000, 1);
    this->ui->SetWidth->setText(QString("宽度：") + QString::number(this->width));
}

void MidPointWidget::on_SetRange_clicked()
{
    this->range = QInputDialog::getDouble(this, QString("扰动范围"), QString("请输入1-64的整数"), this->range, 1,64);
    this->ui->SetRange->setText(QString("扰动范围：±" + QString::number(this->range)));
}

