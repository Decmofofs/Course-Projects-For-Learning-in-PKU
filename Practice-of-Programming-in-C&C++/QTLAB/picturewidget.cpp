#include "picturewidget.h"
#include "ui_picturewidget.h"

PictureWidget::PictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureWidget)
{
    ui->setupUi(this);
    image = NULL;
    if(setcolorWidget) delete setcolorWidget;
    setcolorWidget = new SetColor();
}

QApplication* PictureWidget::filerootApplication = NULL;
QQmlApplicationEngine* PictureWidget::engine = NULL;
SetColor* PictureWidget::setcolorWidget = NULL;
int PictureWidget::MeshStyle = 0;
int PictureWidget::PrinterStyle = 0;

PictureWidget::~PictureWidget()
{
    delete ui;
    if (image != NULL) delete image;
    delete setcolorWidget;
}

void PictureWidget::Print(const char* file) {
    image = new QImage(file);
    int w = image->width();
    int h = image->height();
    if (w > 1080) w = 1080;
    if (h > 720) h = 720;
    this->ui->GraphPrinter->setGeometry(0, 0, w, h);
    this->ui->GraphPrinter->setPixmap(QPixmap::fromImage(*image));
}

void PictureWidget::on_pushButton_clicked()
{
    setcolorWidget->show();
}

