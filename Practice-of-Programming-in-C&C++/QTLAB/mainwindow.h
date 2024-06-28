#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "picturewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    PictureWidget* widget;
    QVideoWidget* videoWidget;
    QMediaPlayer* player;

private slots:
    void on_ValueNoiseStarter_clicked();

    void on_pushButton_clicked();

    void on_PerlinNoiseStarter_clicked();

public slots:
    //void onValueNoiseButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
