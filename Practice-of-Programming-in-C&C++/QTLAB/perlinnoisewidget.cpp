#include "perlinnoisewidget.h"
#include "ui_perlinnoisewidget.h"
#include "view3dwidget.h"


PerlinNoiseWidget::PerlinNoiseWidget(unsigned height, unsigned width, unsigned precision, unsigned seed,
                                   unsigned height_limit, interpolateFunc useFunction,
                                   QWidget *parent) :
    PictureWidget(parent),
    height(height), width(width), precision(precision), seed(seed),
    height_limit(height_limit), useFunction(useFunction),
    ui(new Ui::PerlinNoiseWidget)
{
    ui->setupUi(this);

    this->ui->SetInterval->setMinimum(1);
    this->ui->SetInterval->setMaximum(15);
    this->ui->SetInterval->setValue(10);

    this->ui->SetWidth->setMinimum(1);
    this->ui->SetWidth->setMaximum(15);
    this->ui->SetWidth->setValue(4);

    this->ui->SetHeight->setMinimum(1);
    this->ui->SetHeight->setMaximum(15);
    this->ui->SetHeight->setValue(3);

    p2dcal = new PerLinNoiseCal(this->height, this->width, this->precision, this->seed);
    p2dthread = new QThread;

    p2dcal->moveToThread(p2dthread);

    p2dthread->start();
}

PerlinNoiseWidget::~PerlinNoiseWidget()
{
    delete ui;
    if(p2dcal) delete p2dcal;
    if(p2dthread) {
        p2dthread->exit();
        delete p2dthread;
    }
}

void PerlinNoiseWidget::Paint() {
    // p2dcal->work();
    emit p2dcal->ToDo();
}

void PerlinNoiseWidget::on_start_clicked()
{
    this->Paint();
}
void PerlinNoiseWidget::on_Printer_clicked()
{
    this->Print("./PerlinNoiseGraph.bmp");
}
void PerlinNoiseWidget::on_reset_clicked()
{
    this->height = 3;
    this->width = 4;
    this->precision = 100;
    this->seed = 0;
    this->height_limit = 255;
    this->useFunction = CosineInterpolate;

    QString str;
    char ch[11] = {};

    this->ui->SetHeight->setValue(3);
    str = "高度 : ";
    itoa(this->height * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lheight->setText(str);

    this->ui->SetWidth->setValue(4);
    str = "宽度 : ";
    itoa(this->width * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lwidth->setText(str);

    this->ui->SetInterval->setValue(10);
    str = "采样点间隔 : ";
    itoa(this->precision, ch, 10);
    str += ch;
    this->ui->Linterval->setText(str);

    str = "种子 : ";
    itoa(this->seed, ch, 10);
    str += ch;
    this->ui->Lseed->setText(str);
}

void PerlinNoiseWidget::on_SetInterval_valueChanged(int value)
{
    this->precision = 10 * value;

    QString str = "采样点间隔 : ";
    char ch[5] = {};
    itoa(this->precision, ch, 10);
    str += ch;
    this->ui->Linterval->setText(str);

    str = "宽度 : ";
    itoa(this->width * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lwidth->setText(str);

    str = "高度 : ";
    itoa(this->height * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lheight->setText(str);
}
void PerlinNoiseWidget::on_SetWidth_valueChanged(int value)
{

    this->width = value;
    QString str = "宽度 : ";
    char ch[5] = {};
    itoa(this->width * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lwidth->setText(str);
}
void PerlinNoiseWidget::on_SetHeight_valueChanged(int value)
{
    this->height = value;
    QString str = "高度 : ";
    char ch[5] = {};
    itoa(this->height * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lheight->setText(str);
}
void PerlinNoiseWidget::on_SetSeed_clicked()
{
    unsigned rseed = (unsigned)time(0);
    rseed = unsigned((rseed % 65536) * (rseed % 65536) * (rseed % 1024) + 1127 * rseed + 1898) / 2;
    int seedrec = QInputDialog::getInt(this, QString("Set seed"), QString("new seed :"), this->seed, -1, 2147483647, 1);
    if (seedrec == -1) this->seed = rseed;
    else this->seed = seedrec;
    QString str = "种子 : ";
    char ch[11] = {};
    itoa(this->seed, ch, 10);
    str += ch;
    this->ui->Lseed->setText(str);
}

void PerlinNoiseWidget::on_Get3DView_clicked()
{

    if (view3dwidget::View3DPlayer) delete view3dwidget::View3DPlayer;
    view3dwidget::View3DPlayer = new view3dwidget("perlinnoisemesh");

    emit view3dwidget::View3DPlayer->ToDo();

}
