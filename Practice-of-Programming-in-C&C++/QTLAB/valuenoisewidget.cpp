#include "valuenoisewidget.h"
#include "ui_valuenoisewidget.h"
#include "view3dwidget.h"


ValueNoiseWidget::ValueNoiseWidget(unsigned height, unsigned width, unsigned precision, unsigned seed,
                                   unsigned height_limit, smoothFunc useFunction,
                                   QWidget *parent) :
    PictureWidget(parent),
    height(height), width(width), precision(precision), seed(seed),
    height_limit(height_limit), useFunction(useFunction),
    ui(new Ui::ValueNoiseWidget)
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

    v2dcal = new ValueNoiseCal(this->height, this->width, this->precision, this->seed);
    v2dthread = new QThread;

    v2dcal->moveToThread(v2dthread);

    // QObject::connect(v2dcal, &ValueNoiseCal::ToDo, v2dcal, &ValueNoiseCal::work);

    v2dthread->start();
}

ValueNoiseWidget::~ValueNoiseWidget()
{
    delete ui;
    if(v2dcal) delete v2dcal;
    if(v2dthread) {
        v2dthread->exit();
        delete v2dthread;
    }
}

void ValueNoiseWidget::Paint() {
    // v2dcal->work();
    emit v2dcal->ToDo();
}

void ValueNoiseWidget::on_start_clicked()
{
    this->Paint();
}
void ValueNoiseWidget::on_Printer_clicked()
{
    this->Print("./ValueNoiseGraph.bmp");
}
void ValueNoiseWidget::on_reset_clicked()
{
    this->height = 3;
    this->width = 4;
    this->precision = 100;
    this->seed = 0;
    this->height_limit = 255;
    this->useFunction = C1Polynomial;

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

void ValueNoiseWidget::on_SetInterval_valueChanged(int value)
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
void ValueNoiseWidget::on_SetWidth_valueChanged(int value)
{

    this->width = value;
    QString str = "宽度 : ";
    char ch[5] = {};
    itoa(this->width * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lwidth->setText(str);
}
void ValueNoiseWidget::on_SetHeight_valueChanged(int value)
{
    this->height = value;
    QString str = "高度 : ";
    char ch[5] = {};
    itoa(this->height * this->precision + 1, ch, 10);
    str += ch;
    this->ui->Lheight->setText(str);
}
void ValueNoiseWidget::on_SetSeed_clicked()
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

void ValueNoiseWidget::on_Get3DView_clicked()
{
/*
    QQuickWidget* qqw = new QQuickWidget();
    qqw->setSource(QUrl("qrc:/main.qml"));
*/

    if (view3dwidget::View3DPlayer) delete view3dwidget::View3DPlayer;
    view3dwidget::View3DPlayer = new view3dwidget("valuenoisemesh");

    emit view3dwidget::View3DPlayer->ToDo();

}

