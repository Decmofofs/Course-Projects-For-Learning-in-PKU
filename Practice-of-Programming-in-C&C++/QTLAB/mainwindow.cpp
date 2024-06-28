#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "valuenoisewidget.h"
#include "perlinnoisewidget.h"
#include <QVBoxLayout>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Qt大作业");
    widget = NULL;
    resize(2400,960);
    ui->label->setGeometry(QRect(700,20,ui->label->width(),ui->label->height()));
    ui->ValueNoiseStarter->setGeometry(QRect(760,100,ui->ValueNoiseStarter->width(),ui->ValueNoiseStarter->height()));
    ui->PerlinNoiseStarter->setGeometry(QRect(760,180,ui->PerlinNoiseStarter->width(),ui->PerlinNoiseStarter->height()));
    ui->wwdx->setGeometry(QRect(760,260,ui->wwdx->width(),ui->wwdx->height()));


    const QUrl url(QStringLiteral("qrc:/start.qml"));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->resize(2400,960);
    ui->quickWidget->setSource(url);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (widget != NULL) delete widget;
    if (player != NULL) delete player;
    if (videoWidget != NULL) delete videoWidget;
}

void MainWindow::on_ValueNoiseStarter_clicked()
{
    widget = new ValueNoiseWidget();
    widget->setWindowTitle(QString("Value Noise 展示"));
    widget->show();

    return;
}

void MainWindow::on_PerlinNoiseStarter_clicked()
{
    widget = new PerlinNoiseWidget();
    widget->setWindowTitle(QString("Perlin Noise 展示"));
    widget->show();

    return;
}

void MainWindow::on_pushButton_clicked()
{
    QDialog* dialog = new QDialog();
    dialog->setWindowTitle("帮助");
    QLabel* label = new QLabel(dialog);
    dialog->resize(600,300);
    QString text("");
    text += "算法：\n\t在主界面，你可以点击选择你想要的用来生成地形的算法\n\n";
    text += "参数：\n\t选择任一算法后，在相应窗口的右侧可以修改（拖动滑动条或点击按钮）对应的参数\n\t";
    text += "其中种子改为-1会随机生成种子\n\t";
    text += "参数可以影响生成的地形的具体样貌\n\n";
    text += "地形图：\n\t设置参数后，先点击\"生成地形\"，待按钮弹起后再点击\"绘制地形图\"\n\t";
    text += "同样地，按钮抬起后才能点击\"3D地形模式\"打开3D视窗\n\t";
    text += "当地图较大时，地形的生成与3D视窗的打开均需要耗费较长时间，请耐心等待\n\n";
    text += "3D视窗：\n\t在3D视窗中，你将会看到实际的地形样貌\n\t";
    text += "鼠标左键按下后可以控制视角，wasd键控制移动方向\n\n";
    label->setText(text);
    dialog->show();
}

