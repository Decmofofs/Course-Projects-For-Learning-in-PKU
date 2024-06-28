#include "setcolor.h"
#include "ui_setcolor.h"

#include <QInputDialog>

void SetColor::reset(int i){
    if(i > 0 && i <= 6){
        --i;
        labels[i][0]->setText(QString::number(colors[i].RED));
        labels[i][1]->setText(QString::number(colors[i].GREEN));
        labels[i][2]->setText(QString::number(colors[i].BLUE));
        QString cqs = "color:#";
        QString r = QString::number(colors[i].RED, 16);
        if (r.length() == 1) r = '0' + r;
        QString g = QString::number(colors[i].GREEN, 16);
        if (g.length() == 1) g = '0' + g;
        QString b = QString::number(colors[i].BLUE, 16);
        if (b.length() == 1) b = '0' + b;
        cqs += r + g + b + ';';
        texts[i]->setStyleSheet(cqs);
        return;
    }
    for(int j = 1; j <= 6; ++j){
        reset(j);
    }
}

double SetColor::heights[5] = {50,100,150,200,245};
BGRpixel SetColor::colors[6] = {
    BGRpixel{130,180,135},
    BGRpixel{170,210,185},
    BGRpixel{190,255,255},
    BGRpixel{170,200,225},
    BGRpixel{125,150,200},
    BGRpixel{180,130,170}
};
SetColor::SetColor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetColor)
{
    ui->setupUi(this);
    setWindowTitle("Set Color");

    /*
    buttons[0][0] = ui->SetR1;
    buttons[0][1] = ui->SetG1;
    buttons[0][2] = ui->SetB1;
    buttons[1][0] = ui->SetR2;
    buttons[1][1] = ui->SetG2;
    buttons[1][2] = ui->SetB2;
    buttons[2][0] = ui->SetR3;
    buttons[2][1] = ui->SetG3;
    buttons[2][2] = ui->SetB3;
    buttons[3][0] = ui->SetR4;
    buttons[3][1] = ui->SetG4;
    buttons[3][2] = ui->SetB4;
    buttons[4][0] = ui->SetR5;
    buttons[4][1] = ui->SetG5;
    buttons[4][2] = ui->SetB5;
    */

    labels[0][0] = ui->R1;
    labels[0][1] = ui->G1;
    labels[0][2] = ui->B1;
    labels[1][0] = ui->R2;
    labels[1][1] = ui->G2;
    labels[1][2] = ui->B2;
    labels[2][0] = ui->R3;
    labels[2][1] = ui->G3;
    labels[2][2] = ui->B3;
    labels[3][0] = ui->R4;
    labels[3][1] = ui->G4;
    labels[3][2] = ui->B4;
    labels[4][0] = ui->R5;
    labels[4][1] = ui->G5;
    labels[4][2] = ui->B5;
    labels[5][0] = ui->R6;
    labels[5][1] = ui->G6;
    labels[5][2] = ui->B6;

    texts[0] = ui->C1;
    texts[1] = ui->C2;
    texts[2] = ui->C3;
    texts[3] = ui->C4;
    texts[4] = ui->C5;
    texts[5] = ui->C6;

    reset(0);
    //show();
}

SetColor::~SetColor()
{
    delete ui;
}

void SetColor::on_SetR1_clicked(){
    colors[0].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[0].RED, 0, 255, 1);
    reset(1);
}
void SetColor::on_SetG1_clicked(){
    colors[0].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[0].GREEN, 0, 255, 1);
    reset(1);
}
void SetColor::on_SetB1_clicked(){
    colors[0].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[0].BLUE, 0, 255, 1);
    reset(1);
}


void SetColor::on_SetR2_clicked(){
    colors[1].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[1].RED, 0, 255, 1);
    reset(2);
}
void SetColor::on_SetG2_clicked(){
    colors[1].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[1].GREEN, 0, 255, 1);
    reset(2);
}
void SetColor::on_SetB2_clicked(){
    colors[1].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[1].BLUE, 0, 255, 1);
    reset(2);
}


void SetColor::on_SetR3_clicked(){
    colors[2].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[2].RED, 0, 255, 1);
    reset(3);
}
void SetColor::on_SetG3_clicked(){
    colors[2].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[2].GREEN, 0, 255, 1);
    reset(3);
}
void SetColor::on_SetB3_clicked(){
    colors[2].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[2].BLUE, 0, 255, 1);
    reset(3);
}


void SetColor::on_SetR4_clicked(){
    colors[3].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[3].RED, 0, 255, 1);
    reset(4);
}
void SetColor::on_SetG4_clicked(){
    colors[3].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[3].GREEN, 0, 255, 1);
    reset(4);
}
void SetColor::on_SetB4_clicked(){
    colors[3].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[3].BLUE, 0, 255, 1);
    reset(4);
}


void SetColor::on_SetR5_clicked(){
    colors[4].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[4].RED, 0, 255, 1);
    reset(5);
}
void SetColor::on_SetG5_clicked(){
    colors[4].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[4].GREEN, 0, 255, 1);
    reset(5);
}
void SetColor::on_SetB5_clicked(){
    colors[4].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[4].BLUE, 0, 255, 1);
    reset(5);
}

void SetColor::on_SetR6_clicked(){
    colors[5].RED = QInputDialog::getInt(this, QString("Set RED"), QString("new RED :"), colors[5].RED, 0, 255, 1);
    reset(6);
}
void SetColor::on_SetG6_clicked(){
    colors[5].GREEN = QInputDialog::getInt(this, QString("Set GREEN"), QString("new GREEN :"), colors[5].GREEN, 0, 255, 1);
    reset(6);
}
void SetColor::on_SetB6_clicked(){
    colors[5].BLUE = QInputDialog::getInt(this, QString("Set BLUE"), QString("new BLUE :"), colors[5].BLUE, 0, 255, 1);
    reset(6);
}

