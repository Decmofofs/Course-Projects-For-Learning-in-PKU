#ifndef SETCOLOR_H
#define SETCOLOR_H

#include "qpushbutton.h"
#include <QWidget>
#include <QLabel>

#ifndef BGR_PIXEL
#define BGR_PIXEL
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef long                LONG;
typedef struct tagIMAGEINFO {
    BYTE BLUE;
    BYTE GREEN;
    BYTE RED;
} BGRpixel;
#endif

namespace Ui {
class SetColor;
}

class SetColor : public QWidget
{
    Q_OBJECT

public:
    static double heights[5];
    static BGRpixel colors[6];

    //QPushButton* buttons[6][3];
    QLabel* labels[6][3];
    QLabel* texts[6];

public:
    explicit SetColor(QWidget *parent = nullptr);
    ~SetColor();

    void reset(int i = 0);

private slots:
    void on_SetR1_clicked();
    void on_SetG1_clicked();
    void on_SetB1_clicked();

    void on_SetR2_clicked();
    void on_SetG2_clicked();
    void on_SetB2_clicked();

    void on_SetR3_clicked();
    void on_SetG3_clicked();
    void on_SetB3_clicked();

    void on_SetR4_clicked();
    void on_SetG4_clicked();
    void on_SetB4_clicked();

    void on_SetR5_clicked();
    void on_SetG5_clicked();
    void on_SetB5_clicked();

    void on_SetR6_clicked();
    void on_SetG6_clicked();
    void on_SetB6_clicked();

private:
    Ui::SetColor *ui;
};

#endif // SETCOLOR_H
