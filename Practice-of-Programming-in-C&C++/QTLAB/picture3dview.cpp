#include "picture3dview.h"
#include "ui_picture3dview.h"

Picture3DView::Picture3DView(QWidget* n3dWidget, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Picture3DView)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(n3dWidget);
}

Picture3DView::~Picture3DView()
{
    delete ui;
}
