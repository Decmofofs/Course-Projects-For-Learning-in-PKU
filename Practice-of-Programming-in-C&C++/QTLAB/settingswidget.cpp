#include "settingswidget.h"
#include "ui_settingswidget.h"
#include "picturewidget.h"

const QString MeshStyle[2] = {"方块状网格", "平滑网格"};
const QString PrinterStyle[2] = {"等高线模式", "灰度模式"};

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    ui->SetMesh->setText(MeshStyle[PictureWidget::MeshStyle]);
    ui->SetPrinter->setText(PrinterStyle[PictureWidget::PrinterStyle]);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::on_SetMesh_clicked()
{
    ++PictureWidget::MeshStyle;
    PictureWidget::MeshStyle %= 2;
    this->ui->SetMesh->setText(MeshStyle[PictureWidget::MeshStyle]);
}


void SettingsWidget::on_SetPrinter_clicked()
{
    ++PictureWidget::PrinterStyle;
    PictureWidget::PrinterStyle %= 2;
    this->ui->SetPrinter->setText(PrinterStyle[PictureWidget::PrinterStyle]);
}

